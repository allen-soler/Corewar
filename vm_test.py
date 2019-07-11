#!/usr/bin/env python3
import sys
import subprocess
import itertools
from typing import List

def get_all_files(extension= ".s", directory=".") -> List:
	try:
		completed = subprocess.run(
			"find {0} -type f -name '*{1}'".format(directory, extension),
			shell=True,
			check=True,
			stdout=subprocess.PIPE
		)
	except subprocess.CalledProcessError as err:
		print("FIND FAILED, ERROR: ", err)
	print("Find executed correctly, return code {}".format(completed.returncode))
	#print("Compiling the following files:\n", completed.stdout.decode('utf-8'))
	return completed.stdout.decode('utf-8').split('\n')

def unidiff_output(expected: str, actual: str) -> str:
	import difflib

	expected = expected.splitlines(1)
	actual = actual.splitlines(1)

	diff = difflib.unified_diff(expected, actual)

	return ''.join(diff)

def query_yes_no(question: str, default = "yes") -> bool:
	valid = {"yes": True, "y": True,
             "no": False, "n": False}

	prompt = "[Y/n] "

	while True:
		sys.stdout.write(question + prompt)
		choice = input().lower()
		if default is not None and choice == '':
			return valid[default]
		elif choice in valid:
			return valid[choice]
		else:
			sys.stdout.write("Please respond with 'yes' or 'no' "
			"(or 'y' or 'n').\n")


def compile_champions(compare = False, assemblers = None):
	files = get_all_files(".s", ".")
	failed = []

	for file in files:
		if not compare:
			subprocess.run("./asm {}".format(file), shell=True)
			continue
		print("File: ", file)
		cor_champ = file.replace(".s", ".cor")
		champ_name = cor_champ.split('/')[-1]
		print("========================================")
		print("FIRST ASM")
		print("========================================")
		completed1 = subprocess.run(
			"{} {}".format(assemblers[0], file),
			shell = True
		)
		print("\n")
		if completed1.returncode is 0:
			subprocess.run("mv {0} /tmp/{1}".format(cor_champ, champ_name), shell = True)
		print("========================================")
		print("SECOND ASM")
		print("========================================")
		completed2 = subprocess.run(
			"{} {}".format(assemblers[1], file),
			shell = True
		)
		print("\n")
		if completed1.returncode == 1 and completed1.returncode != completed2.returncode:
			failed.append(file)
			print("Exit codes are not equal, exiting (unless everything is activated)\n")
			if "--everything" not in sys.argv:
				exit(1)

		if completed1.returncode == 0:
			diff = subprocess.run(
				"diff {0} /tmp/{1}".format(cor_champ, champ_name),
				shell = True
			)
			if diff.returncode is not 0:
				failed.append(file)
				print("Found a difference!")
				if "--everything" not in sys.argv:
					exit(1)
	return failed


if len(sys.argv) == 1:
	print("Explanation of flags:\n"
		"\t--everything: it will keep doing test without stopping on diff | abnormal exit codes\n"
		"\t--compile: will compile the champions)\n"
		"\t--cmp_asm asm1 asm2: will compare the .cor files while compiling (specifie two asm afterwards)\n"
		"\t--cmp_vm: it will trigger the tests for the vm\n"
		"\t--dumps step_size: it will compare the dumps on all the champions while testing the VM")

compile_champ = False
cmp_asm = False
assemblers = []

if "--compile" in sys.argv:
    compile_champ = True

if "--cmp_asm" in sys.argv:
    cmp_asm = True
    assemblers.append(sys.argv[sys.argv.index("--cmp_asm") + 1])
    assemblers.append(sys.argv[sys.argv.index("--cmp_asm") + 2])

if compile_champ:
	fail = compile_champions(cmp_asm, assemblers)
	print("the following champions had some type of error with the asm: ", fail)


# VM part of the script

if "--cmp_vm" not in sys.argv:
    exit(0)

failed = []
diff_exit_code = []

test_everything = False
compare_dumps = False
dump_step_size = 1

files = get_all_files(".cor", ".")

if "--everything" in sys.argv:
	test_everything = True

if "--dumps" in sys.argv:
	compare_dumps = True
	dump_step_size = sys.argv[list(sys.argv).index("--dumps") + 1]
	print("Dump set, comparing every {} cycles".format(dump_step_size))


error = False

for i in range(1, 5):
	combinations = itertools.combinations(files, i)
	if error is True:
		break
	for comb in combinations:
		champs = " ".join(list(comb));
		print("champs: ", champs)
		timeout = 0
		try:
			completed1 = subprocess.run(
				"{} {}".format("./corewar -v 0", champs),
				stdout = subprocess.PIPE,
				timeout=10,
				shell = True
			)
		except subprocess.TimeoutExpired:
			print("Time out!")
			timeout += 1

		try:
			completed2 = subprocess.run(
				"{} {}".format("./resources/orig_vm -v 0", champs),
				stdout = subprocess.PIPE,
				timeout=10,
				shell = True
			)
		except subprocess.TimeoutExpired:
			print("Time out!")
			timeout += 1
		if timeout is 1 and test_everything is False:
			print("Only one of the VM's timed out, no bueno!")
			exit()
		if completed1.returncode != 0 and completed1.returncode != completed2.returncode:
			diff_exit_code.append(champs)
			print("Abnormal exit in first vm , with return code {0}, second {1}, with champions {2}".format(
			completed1.returncode, completed2.returncode, champs
			))
			if test_everything == False and not query_yes_no("Do you want to continue?"):
				print(unidiff_output(completed1.stdout.decode('utf-8'), completed2.stdout.decode('utf-8')))
				error = True
				break

		if completed1.stdout.decode('utf-8') != completed2.stdout.decode('utf-8'):
			failed.append(champs)
			print("Found a difference with champions: ", champs)
			if test_everything == False and not query_yes_no("Do you want to continue?, or stop and print difference"):
				print(unidiff_output(completed1.stdout.decode('utf-8'), completed2.stdout.decode('utf-8')))
				error = True
				break

		if compare_dumps is True:
			subprocess.run("./scripts/compare_vm.php --cycles 1 {0} './corewar -v 0' './cw/corewar -ve 0' {1}".format(dump_step_size, champs),
							shell=True,
							check=True)

print("Difference found on the following champions:")
print("\n".join(failed))
print("Different exit code with the next ones:")
print("\n".join(diff_exit_code))

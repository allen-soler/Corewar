#!/usr/bin/env python3
import sys
import subprocess
import itertools
from typing import List
import uuid

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
	print("Compiling the following files:\n", completed.stdout.decode('utf-8'))
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


def compile_champions():
	files = get_all_files(".s", ".")

	for file in files:
		subprocess.run("./asm {}".format(file), shell=True)

files = get_all_files(".cor", ".")


failed = []
diff_exit_code = []

test_everything = False
compare_dumps = False
dump_step_size = 1


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
		if timeout is 1:
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
			subprocess.run("./scripts/compare_vm.php --cycles 1 {0} './corewar -v 0' './resources/orig_vm -v 0' {1}".format(dump_step_size, champs),
							shell=True,
							check=True)

print("Difference found on the following champions:")
print("\n".join(failed))
print("Different exit code with the next ones:")
print("\n".join(diff_exit_code))

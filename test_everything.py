#!/usr/bin/env python3
import sys
import subprocess
from typing import List
import uuid

"""

This script will find all the .s files in the current directory and it's subdirectories,
compile it using the first ./asm passed as an argument, and compare the hexdump output
with the second assembler passed, saving to a temporary file the difference (if difference is
found the script will terminate), once this step is finished (or this step is skipped), it will
execute all the possible combinations of champions with both virtual machines (also passed as
an argument), following the same steps in case of difference, in this case, it will repeat the process
N times, augmenting each time the level of verbosity in the executions. 

"""

def usage():
	print ("Usage (no more options for the moment) (Python 3.x necessary):\n", 
		"./test_everything.py ./asm1 ./asm2 ./vm1 ./vm2 --dump step_size --verbosity start_level --dir [\"DIR\" | default = \".\" --extension [.cor]",
		"all the options default is set to false, if --extension is specified, the asm part will be skipped")


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

def execute_asm(files, asm1 = "./asm", asm2="./cw/asm"):
	for champion in files:
		unique_id = str(uuid.uuid4)
		cor_champ = champion.replace('.s', '.cor')
		a1 = subprocess.CompletedProcess.__class__
		a2 = subprocess.CompletedProcess.__class__
		try:
			a1 = subprocess.run(
				"{0} {1}".format(asm1, champion),
				shell=True,
			)
			cor1 = "/tmp/{1}{2}".format(cor_champ, "asm1" + cor_champ.split('/')[-1], unique_id)
			subprocess.run(
				"cp {0} {1}".format(cor_champ, cor1),
				shell= True
			)
			a2 = subprocess.run(
				"{0} {1}".format(asm2, champion),
				shell=True,
			)
			cor2 = "/tmp/{1}{2}".format(cor_champ, "asm2" + cor_champ.split('/')[-1], unique_id)
			subprocess.run(
				"cp {0} {1}".format(cor_champ, cor2),
				shell= True
			)
			if not a1.returncode == a2.returncode:
				raise subprocess.CalledProcessError
			if a1.returncode == 0 && a2.returncode == 0:
				completed = 
				pass
			
		except subprocess.CalledProcessError:
			print("Asembler {0} or {1}, exited with error code != 0, with file {2}".format(asm1, asm2, champion))
		else:
			print("Champion {0} is ok.".format(champion))

		print(a1, a2)
		



ASM = True
VM = True

files = get_all_files()

if ASM:
	execute_asm(files)
	pass
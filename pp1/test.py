#!/usr/bin/env python

from __future__ import print_function

import glob, os, sys, subprocess

def get_test_names():
	os.chdir("samples")
	test_names = [file[:-5] for file in glob.glob("*.frag")]
	os.chdir("..")
	return test_names


def run_test(name):
	did_pass = False
	print("TEST: " + name)
	with open('samples/' + name + '.frag', 'r') as compile_in:
		p = subprocess.Popen(['./dcc'], stdin=compile_in, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
		compiled = p.communicate()[0]
		return_code = p.returncode
		if return_code == 0:
			print("  Compile: SUCCESS")
		else:
			print("  Compile: FAIL!")
			print("    Return code: " + str(return_code))
		with open('samples/' + name + '.out', 'r') as given_out:
			given = given_out.read()
			if given == compiled:
				print("  Compare: SUCCESS")
				did_pass = True
			else:
				print("  Compare: FAIL!")
				print("    Given output:")
				print(given)
				print("    Compiler output:")
				print(compiled)
	print()
	return did_pass
		

def run_all():
	passed = 0
	for test_name in get_test_names():
		if run_test(test_name):
			passed += 1
	return passed


if __name__ == '__main__':
	passed = 0
	total = 0
	if len(sys.argv) > 1:
		for arg in sys.argv[1:]:
			total += 1
			if run_test(arg.split('.')[0]):
				passed += 1
	else:
		passed = run_all()
		total = len(get_test_names())
	print("TOTAL: " + str(passed) + "/" + str(total) + " passed")

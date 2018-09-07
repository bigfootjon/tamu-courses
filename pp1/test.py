#!/usr/bin/env python

from __future__ import print_function

import glob, os, sys, subprocess

TEST_DIR = "samples"

class TestCase:
    @staticmethod
    def get_all():
        os.chdir(TEST_DIR)
        tests = []
        for ext in ['frag', 'decaf']:
            tests.extend([TestCase(file) for file in glob.glob("*." + ext)])
        os.chdir("..")
        return tests

    @staticmethod
    def get_by_name(name):
        if os.path.isfile(os.path.join(TEST_DIR, name + '.frag')):
            return TestCase(name + '.frag')
        elif os.path.isfile(os.path.join(TEST_DIR, name + '.decaf')):
            return TestCase(name + '.decaf')
        else:
            raise Exception("No test case found in '" + TEST_DIR + "' with name '" + name + "' :(")

    def __init__(self, in_file):
        self.name = in_file.split(".")[0]
        self._in_file = in_file
        self._out_file = self.name + ".out"

    def run(self):
        did_pass = False
        print("TEST: " + self.name)
        with open(os.path.join(TEST_DIR, self._in_file), 'r') as compile_in:
            p = subprocess.Popen(['./dcc'], stdin=compile_in, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        compiled = p.communicate()[0].decode("utf-8").replace("\r", "")
        return_code = p.returncode
        if return_code == 0:
            print("  Compile: SUCCESS")
        else:
            print("  Compile: FAIL!")
            if return_code == 255:
                reason = "Compiler input error, if COMPARE passes below this is fine"
            elif return_code == 11:
                reason = "Segmentation fault! This is very bad"
            else:
                reason = "Unknown"
            print("    Return code: " + str(return_code) + " (" + reason + ")")
        if os.path.isfile(os.path.join(TEST_DIR, self._out_file)):
            with open(os.path.join(TEST_DIR, self._out_file), 'r') as given_out:
                given = given_out.read().replace("\r", "")
                if given == compiled:
                    print("  Compare: SUCCESS")
                    did_pass = True
                else:
                    print("  Compare: FAIL!")
                    print("    Expected output:")
                    print(given)
                    print("    Compiler output:")
                    print(compiled)
        else:
            print("  Compare: SKIPPED!")
            print("    Compiler output:")
            print(compiled)
            should_save = raw_input("    Save this output as correct output? [Y/n]: ")
            if len(should_save) == 0 or should_save[0] != 'n':
                did_pass = True
                with open(os.path.join(TEST_DIR, self._out_file), 'w') as out_file:
                    out_file.write(compiled)
                print("    Successfully saved " + self._out_file + "!")
        print()
        return did_pass



def run_list(tests):
    passed = 0
    failed_names = []
    for test in tests:
        if test.run():
            passed += 1
        else:
            failed_names.append(test.name)
    return passed, failed_names


if __name__ == '__main__':
    try:
        if not os.path.isfile('dcc'):
	    print("Compiler missing!")
            should_make = raw_input("Run `make`? [Y/n]: ")
	    if len(should_make) > 0 and should_make[0] == 'n':
                exit(1)
            p = subprocess.Popen(['make'])
            p.communicate()
            if p.returncode != 0:
                print("Make failed!")
                exit(1)

        if len(sys.argv) > 1:
            tests = [TestCase.get_by_name(name) for name in sys.argv[1:]]
        else:
            tests = TestCase.get_all()
        total = len(tests)
        passed, failed_names = run_list(tests)

        print("TOTAL: " + str(passed) + "/" + str(total) + " passed")
        if len(failed_names) > 0:
            print("  Failed tests: " + ", ".join(failed_names))
    except Exception as e:
        print(e.message)

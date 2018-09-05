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
    with open('samples/' + name + '.out', 'r') as given_out:
        given = given_out.read().replace("\r", "")
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

def run_list(test_names):
    passed = 0
    failed_names = []
    for test_name in test_names:
        if run_test(test_name):
            passed += 1
        else:
            failed_names.append(test_name)
    return passed, failed_names


if __name__ == '__main__':
    if len(sys.argv) > 1:
        test_names = sys.argv[1:]
    else:
        test_names = get_test_names()
    total = len(test_names)
    passed, failed_names = run_list(test_names)

    print("TOTAL: " + str(passed) + "/" + str(total) + " passed")
    if len(failed_names) > 0:
        print("  Failed tests: " + ", ".join(failed_names))

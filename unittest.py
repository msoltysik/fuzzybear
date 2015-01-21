import os
import sys
import sys
import subprocess

from glob import glob

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


actual = [y for x in os.walk("tests/unittests/actual/") for y in glob(os.path.join(x[0], '*.imp'))]
expected = [y for x in os.walk("tests/unittests/expected/") for y in glob(os.path.join(x[0], '*.imp'))]

fuzzybear = os.getcwd() + "/fuzzybear-cc"

for test in range(len(actual)):
	actual_test = "/".join([os.getcwd(), actual[test]])
	expected_test = "/".join([os.getcwd(), expected[test]])

	proc = subprocess.Popen([fuzzybear, actual_test], shell=False, stdout=subprocess.PIPE)
	actual_output = proc.stdout.read()
	expected_output = open(expected_test, 'r').read()
	if actual_output == expected_output:
		print(bcolors.OKGREEN + "[#.%d] Test \"%s\" passed." % (test+1, actual[test]) + bcolors.ENDC)
	else:
		print(bcolors.FAIL + "[#.%d] Test \"%s\" failed: \n" % (test+1, actual[test]) + bcolors.ENDC)
		print(bcolors.WARNING + "Actual:\n" + bcolors.ENDC + actual_output)
		print(bcolors.WARNING + "Expected:\n" + bcolors.ENDC + expected_output)
		print("")


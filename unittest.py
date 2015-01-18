import os
import sys
import sys
import subprocess

from glob import glob
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
		print("[#.%d] Test \"%s\" passed." % (test, actual[test]))
	else:
		print("[#.%d] Test \"%s\" failed." % (test, actual[test]))
		print("Actual:\n" + actual_output)
		print("Expected:\n" + expected_output)


import os
import sys
import sys
import subprocess

from glob import glob
actual = [y for x in os.walk("tests/unittests/actual/") for y in glob(os.path.join(x[0], '*.imp'))]
expected = [y for x in os.walk("tests/unittests/expected/") for y in glob(os.path.join(x[0], '*.imp'))]

fuzzybear = os.getcwd() + "/fuzzybear-cc"

for test in range(1):
	actual_test = "/".join([os.getcwd(), actual[test]])
	expected_test = "/".join([os.getcwd(), expected[test]])

	print(actual_test)
	print(expected_test)

	proc = subprocess.Popen([fuzzybear, actual_test], stderr=subprocess.PIPE)
	actual_output = proc.stderr.read()
	expected_output = open(expected_test, 'r').read()
	
	print(1)
	print(repr(actual_output))
	print(2)
	print(repr(expected_output))
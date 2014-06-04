#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
floating = integer + "?(\.\d+)?"
oneint = re.compile(integer + "\n")
twoint = re.compile(integer + " " + integer + "\n")
threeint = re.compile("(" + integer + " ){2}" + integer + "\n")
fourint = re.compile("(" + integer + " ){3}" + integer + "\n")
manyint = re.compile("(" + integer + " )*" + integer + "\n")
string = re.compile("[a-z]+\n")
twostrings = re.compile("[a-z]+ [a-z]+\n")

line = stdin.readline()
assert twostrings.match(line)
s1,s2 = line.split()
assert len(s1)==len(s2)


assert len(stdin.readline()) == 0
sys.exit(42)

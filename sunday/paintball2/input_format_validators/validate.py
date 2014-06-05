#!/usr/bin/env python3
from sys import stdin
import re
import sys

integer = "(0|-?[1-9]\d*)"
floating = integer + "?(\.\d+)?"
oneint = re.compile(integer + "\n")
threefloat = re.compile("(" + floating + " ){2}" + floating + "\n")
string = re.compile("[a-z]+\n")

line = stdin.readline()
assert oneint.match(line)
n = int(line)
assert 1 <= n <= 1000

for test in range(n):
    line = stdin.readline()
    assert threefloat.match(line)
    x, y, r = list(map(int, line.split()))
    assert 0 <= x <= 1000 and 0 <= y <= 1000 and 1 <= r <= 1000

assert len(stdin.readline()) == 0
sys.exit(42)

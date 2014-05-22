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

line = stdin.readline()
assert oneint.match(line)
k = int(line)

for test in range(k):
    line = stdin.readline()
    assert threeint.match(line)
    m,n,l = map(int, line.split())
    assert 1 <= m*n <= 10000
    line = stdin.readline()
    assert manyint.match(line)
    st = list(map(int, line.split()))
    assert len(st)==2*l
    assert all(1 <= x <= 2*(m+n) for x in st)
    assert len(set(st))==2*l

assert len(stdin.readline()) == 0
sys.exit(42)

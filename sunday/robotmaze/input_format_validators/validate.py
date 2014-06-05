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
    assert line == "\n"
    line = stdin.readline()
    assert twoint.match(line)
    a,b = map(int, line.split())
    assert 1 <= a <= 1000
    assert 1 <= b <= 1000
    expect = re.compile("[.BRD]{{{}}}\n".format(b))
    nrs = 0
    nds = 0
    for i in range(a):
        line = stdin.readline()
        assert expect.match(line)
        if line.find("R")!= -1 : nrs=nrs+1
        if line.find("D")!=-1 : nds=nds+1
    assert nrs==1
    assert nds==1

assert len(stdin.readline()) == 0
sys.exit(42)

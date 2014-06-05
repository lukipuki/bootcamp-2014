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
assert threeint.match(line)
n, s, r = list(map(int, line.split()))
assert 1 <= n <= 10 and 2 <= s <= n and 1 <= r <= n

line = stdin.readline()
assert manyint.match(line)
a = list(map(int, line.split()))
assert len(a) == s
seen = set()
for x in a:
    assert 1 <= x <= n
    assert x not in seen
    seen.add(x)

line = stdin.readline()
assert manyint.match(line)
a = list(map(int, line.split()))
assert len(a) == r
seen = set()
for x in a:
    assert 1 <= x <= n
    assert x not in seen
    seen.add(x)

assert len(stdin.readline()) == 0
sys.exit(42)

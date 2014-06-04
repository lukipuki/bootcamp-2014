from sys import stdin

stdin.readline()
for i in range(5):
    outfile = open("wordspin%d.in" % (i + 1), "w")
    line = stdin.readline()
    print(line, file=outfile)

import sys, os

if(len(sys.argv) <= 3):
	print("need additional commands")
	exit(1)

basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"

commands = {}
with open(basepath+"modules.txt", "r") as mods:
    for line in mods.readlines():
        x, y = line.split()
        x = x.strip()
        first, second = y.replace("$BASEPATH/", basepath).strip().rsplit("/",1)
        if '.' in second:
            second = second.split('.', 1)[0]
        sys.path.append(first)
        commands[x] = __import__(second)


if sys.argv[2] not in commands:
	print("command not found")
	exit(1);

commands[x].call(sys.argv[1], sys.argv[3:])

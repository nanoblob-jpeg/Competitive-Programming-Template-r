import sys, random

if(len(sys.argv) <= 3):
	print("need additional commands")
	exit(1)

"""
MODULES IMPORTED HERE
"""
sys.path.append('C:/Users/jerry/bin/dynamicTemplate')
sys.path.append('C:/Users/jerry/bin/staticTemplate')
import temp
import add

# also need to register in the modules file
commands = {}
modules = open("C:/Users/jerry/bin/modules.txt", "r")
for line in modules:
	x, y = line.split()
	x = x.strip()
	y = y.strip()
	commands[x] = y
modules.close()

if sys.argv[2] not in commands:
	print("command not found")
	exit(1);

# also need to add it to elif chain here
if sys.argv[2] == 'temp':
	temp.call(sys.argv[1], sys.argv[3:])
elif sys.argv[2] == 'add':
	add.call(sys.argv[1], sys.argv[3:])
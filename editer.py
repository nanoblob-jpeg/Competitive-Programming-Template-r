import sys, random

if(len(sys.argv) <= 1):
	print("need additional commands")
	exit(1)
#needs to read in dictionary for translation from function to textfile name
textFiles = {}
alias = open("C:/Users/jerry/bin/alias.txt", "r")
for line in alias:
	x, y = line.split()
	x = x.strip()
	y = y.strip()
	textFiles[x] = y
alias.close()

#there is one line at the top of each file, if this line starts with //! it lists
#the methods already inside of the file, just for resolving dependencies
# will look like:
# //! name:startline:endline name:startline:endline
# start and end line are inclusive, ie this comment blocks starts on 26, ends on 32
methods = {}
alreadyAdded = set()
start_print = 0
file = open(sys.argv[1], "r")
line = file.readline()
if(len(line) > 3 and line[:3] == "//!"):
	start_print = 1
	for method in line[3:].strip().split():
		parts = method.split(":")
		methods[parts[0]] = [int(parts[1])-1, int(parts[2])-1]
		alreadyAdded.add(parts[0])
file.close()

file = open(sys.argv[1], "r")
lines = None

if sys.argv[2] == 'add':
	lines = file.readlines()
	file.close()
	index = 0
	while lines[index].strip() != '//! function insert':
		index += 1
	#document the encodings for the functions
	#  might need quotes surrounding it in case of <> in bash
	#  //! name:param type:param type:param type:etc
	#  same for command line just space separated without the //! in front
	#  put 'global ' before param type if that is going to be a global variable
	#  decides which function to paste based on number of arguments given
	#  all dependencies are present in the text file being read
	#  files being read have a format
	#  first line is default parameter types separated by :
	#     ie int:int:long long:string
	#  second line is the name for every PARAM
	#     ie HERE:THERE:WHAT:ETC
	#  then before each function, there is a line with:
	#     //#start PARAM0:PARAM2:etc
	#  where each param is referencing the order for parameters in the function
	#  first value is the return type, so you need to be careful when making return parameters because you don't want
	#  someone using global on it or else it will die

	#  using global will search for where each of the names appears and replace with the global name given
	#  each param across all functions is referenced by same PARAM# must use the same name, must be unique and not
	#     appear as a substr anywhere else in the file
	#     name should also not be a PARAM# format


	for toAdd in sys.argv[3:]:
		name = toAdd
		args = []
		if ':' in toAdd:
			name, args = toAdd.split(':', 1)
		if name in alreadyAdded:
			for key, item in methods.items():
				if item[0] > methods[name][1]:
					methods[key][0] -= methods[name][1] - methods[name][0] + 1
					methods[key][1] -= methods[name][1] - methods[name][0] + 1
			index -= methods[name][1] - methods[name][0]+1
			del lines[methods[name][0]:methods[name][1]+1]
			del methods[name]

		toWriteFile = open(textFiles[name], "r")
		default_args = toWriteFile.readline().strip().split(':')
		param_names = toWriteFile.readline().strip().split(':')
		global_replace = {}
		arg_values = {}
		if args != []:
			args = args.split(':')
			for i in range(len(args)):
				if len(args[i]) >= 7 and args[i][0:6] == 'global':
					default_args[i] = ""
					global_replace[param_names[i]] = args[i][6:]
				else:
					arg_values["PARAM" + str(i)] = args[i] + ' '
		for i in range(len(args), len(default_args)):
			arg_values["PARAM" + str(i)] = default_args[i] + ' '

		method_lines = toWriteFile.readlines()
		for i in range(len(method_lines)):
			if(method_lines[i][:8] == '//#start'):
				param_line = ','.join([arg_values[key.strip()] + param_names[int(key.strip()[5:])] for key in method_lines[i][10:].split(':')[1:] if key.strip() in arg_values])
				return_type = arg_values[method_lines[i][9:].split(':',1)[0]]
				i += 1
				method_lines[i] = method_lines[i].replace("RETURN", return_type)
				method_lines[i] = method_lines[i].replace("PARAM_INSERT", param_line)
			else:
				for key, value in global_replace.items():
					method_lines[i] = method_lines[i].replace(key + '%s,', "")
					method_lines[i] = method_lines[i].replace(',%s' + key, "")
					method_lines[i] = method_lines[i].replace(key, value)
				for key, value in arg_values.items():
					method_lines[i] = method_lines[i].replace(key, value)
		size = len(method_lines)
		for x in method_lines:
			lines.insert(index, x)
			index += 1
		alreadyAdded.add(name)
		methods[name] = [index - size, index-1]
		toWriteFile.close()
elif sys.argv[2] == 'run':
#should add a run one that sweeps through the file looking for inline commands for pasted text
#so basically just this else statement
	lines = file.readlines()
	for i in range(len(lines)):
		if len(lines[i]) > 3 and lines[i].strip()[:3] == '//!':
			if len(lines[i]) >= 13 and lines[i].strip()[4:14] == 'read array':
				#//! read array n name
				temp = lines[i].strip().split()
				n = temp[3]
				name = temp[4]
				numtabs = lines[i].count('\t')
				lines.insert(i, '\t' * numtabs + f"for(int i{{}}; i < {n}; ++i)\n")
				i += 1
				lines.insert(i, '\t'*(numtabs+1) + f"cin >> {name}[i];\n")
				del lines[i+1]
else:
	exit(1)
file = open(sys.argv[1], "w")
first_line = "//! " + " ".join([str(key)+':'+str(item[0]+1+(1-start_print)) + ':'+str(item[1]+1+(1-start_print)) for key, item in methods.items()]) + '\n'
file.write(first_line)
for line in lines[start_print:]:
	file.write(line)
file.close()
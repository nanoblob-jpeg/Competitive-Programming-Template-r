def call(filename, templates):
	functions = dict()
	funcs = open("C:/Users/jerry/bin/staticTemplate/alias.txt", "r")
	for line in funcs:
		x, y = line.split()
		x = x.strip()
		y = y.strip()
		functions[x] = y
	funcs.close()

	file = open(filename, "r")
	lines = file.readlines()
	file.close()
	index = 0
	while lines[index].strip() != '//! function insert':
		index += 1
	for name in templates:
		if name not in functions:
			continue
		toWriteFile = open(functions[name], "r")
		for line in toWriteFile:
			lines.insert(index, line)
			index += 1
		toWriteFile.close()

	file = open(filename, "w")
	for line in lines:
		file.write(line)
	file.close()
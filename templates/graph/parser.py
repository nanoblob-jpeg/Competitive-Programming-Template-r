def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    files = dict()
    files['euler tour'] = basepath+'euler.txt'
    files['kuhn'] = basepath+'kuhn.txt'
    files['tarjan scc'] = basepath+'tarjan.txt'

    if name not in files:
        print("name not found here")
        exit()
    f = open(files[name], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

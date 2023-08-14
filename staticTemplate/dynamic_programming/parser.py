def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    files = dict()
    files['knapsack_optimization'] = basepath+'knapsack_opt.txt'

    if name not in files:
        print("name not found here")
        exit()
    f = open(files[name], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

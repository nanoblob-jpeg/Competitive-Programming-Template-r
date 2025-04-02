def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    files = dict()
    files['knapsack_optimization'] = basepath+'knapsack_opt.txt'
    files['knuth_array_partition'] = basepath+'knuth_array_partition.txt'
    files['knuth_array_merging'] = basepath+'knuth_array_merging.txt'
    if name not in files:
        print("name not found here")
        exit()
    f = open(files[name], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

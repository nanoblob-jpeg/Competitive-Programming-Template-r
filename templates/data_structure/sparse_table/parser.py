def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'min'
    files = dict()

    files['templated'] = basepath+'sparse_table_templated.txt'
    files['min'] = basepath+'sparse_table_min.txt'
    files['max'] = basepath+'sparse_table_max.txt'

    if 'default' in args:
        f = open(files['templated'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'min':
            default = 'min'
        elif arg == 'max':
            default = 'max'

    if default not in files:
        print("sparse table type not found here")
        exit()
    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

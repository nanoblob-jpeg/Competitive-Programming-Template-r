def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'path'
    files = dict()
    files['path'] = basepath+'uf.cpp'

    if 'default' in args:
        f = open(files['path'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'path':
            default = 'path'

    if default not in files:
        print("segtree type not found here")
        exit()

    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

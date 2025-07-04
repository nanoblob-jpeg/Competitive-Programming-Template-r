def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'templated'
    files = dict()
    files['templated'] = basepath+'seg_templated_rr.cpp'
    files['iter'] = basepath+'seg_iter_pr.cpp'

    if 'default' in args:
        f = open(files['templated'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'rr':
            default = 'templated'
        elif arg == 'pr':
            default = 'iter'

    if default not in files:
        print("segtree type not found here")
        exit()

    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

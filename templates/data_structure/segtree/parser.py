def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'templated'
    if name == 'mergetree':
        default = 'merge'
    files = dict()
    files['templated'] = basepath+'seg_templated_rr.cpp'
    files['iter'] = basepath+'seg_iter_pr.cpp'
    files['arith'] = basepath+'seg_arith_rr.cpp'
    files['merge'] = basepath+'seg_merge.cpp'

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
        elif arg == 'arith':
            default = 'arith'
        elif arg == 'merge':
            default = 'merge'

    if default not in files:
        print("segtree type not found here")
        exit()

    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

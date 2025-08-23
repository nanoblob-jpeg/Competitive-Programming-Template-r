def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'path'
    files = dict()
    files['path'] = basepath+'uf.cpp'
    files['pot'] = basepath+'uf_pot.cpp'
    files['mat'] = basepath+'uf_pot_mat.cpp'

    if 'default' in args:
        f = open(files['path'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'path':
            default = 'path'
        if arg == 'pot':
            default = 'pot'
        if arg == 'mat':
            default = 'mat'

    if default not in files:
        print("union find type not found here")
        exit()

    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

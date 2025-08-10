def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'bit'
    files = dict()

    files['bit'] = basepath+'bittrie.cpp'

    if 'default' in args:
        f = open(files['bit'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'bit':
            default = 'bit'

    if default not in files:
        print("bit type not found here")
        exit()
    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

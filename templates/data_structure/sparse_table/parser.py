def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'inline'
    files = dict()

    files['templated'] = basepath+'sparse_table_templated.cpp'
    files['inline'] = basepath+'sparse_table_inline.cpp'
    files['max'] = basepath+'sparse_table_max.cpp'

    if 'default' in args:
        f = open(files['templated'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'inline' or arg == 'min':
            default = 'inline'
        elif arg == 'max':
            default = 'max'

    if default not in files:
        print("sparse table type not found here")
        exit()
    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

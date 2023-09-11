def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = 'sum'
    files = dict()

    files['templated'] = basepath+'bit_templated.txt'
    files['sum'] = basepath+'bit_sum.txt'
    files['xor'] = basepath+'bit_xor.txt'

    if 'default' in args:
        f = open(files['templated'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()

    for arg in args:
        if arg == 'sum':
            default = 'sum'
        elif arg == 'xor':
            default = 'xor'

    if default not in files:
        print("bit type not found here")
        exit()
    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    files = dict()
    files['gcd'] = basepath+'gcd.txt'
    files['factor'] = basepath+'factor.txt'
    files['lcm'] = basepath+'lcm.txt'
    files['mod inverse'] = basepath+'modinv.txt'
    files['crt'] = basepath+'crt.txt'

    if name not in files:
        print("name not found here")
        exit()
    f = open(files[name], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

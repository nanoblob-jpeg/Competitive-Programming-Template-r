def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    files = dict()
    files['choose'] = basepath+'choose.txt'
    files['determinant'] = basepath+'determinant.txt'
    files['fft'] = basepath+'fft.txt'
    files['poly mult fft'] = basepath+'polyfft.txt'
    files['pascal'] = basepath+'pascal.txt'

    if name not in files:
        print("name not found here")
        exit()
    f = open(files[name], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

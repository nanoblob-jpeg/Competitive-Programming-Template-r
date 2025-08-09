def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    files = dict()
    files['avl tree'] = basepath+'avltree.txt'
    files['suffix array'] = basepath+'suffixarray.txt'
    files['block cut tree'] = basepath+'bctree.txt'
    files['wavelet tree'] = basepath+'wavelet.txt'
    files['prefix_sum'] = basepath+'psum.cpp'

    if name not in files:
        print("name not found here")
        exit()
    f = open(files[name], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

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
    files['funcpr'] = basepath+'seg_func_pr.cpp'
    files['freq'] = basepath+'seg_freq_path_update_pr.cpp'
    files['pr_path_update'] = basepath+'seg_freq_path_update_pr.cpp'
    files['rr_path_update'] = basepath+'seg_path_update_rr.cpp'

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
        elif arg == 'funcpr':
            default = 'funcpr'
        elif arg == 'freqpr':
            default = 'freq'
        elif arg == 'extendedpr':
            default = 'pr_path_update'
        elif arg == 'extendedrr':
            default = 'rr_path_update'

    if default not in files:
        print("segtree type not found here")
        exit()

    f = open(files[default], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

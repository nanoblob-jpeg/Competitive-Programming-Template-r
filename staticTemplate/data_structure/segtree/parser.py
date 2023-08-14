def parse(fw, name, args):
    basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
    default = ['sumu', 'sumq', 'ru', 'rq']
    files = dict()
    files[('sumu', 'sumq', 'ru', 'rq')] = basepath+'seg_sum_sum_rr.txt'
    files[('sumu', 'sumq', 'pu', 'rq')] = basepath+'seg_sum_sum_pr.txt'
    files[('sumu', 'sumq', 'ru', 'pq')] = basepath+'seg_sum_sum_rp.txt'
    files[('setu', 'sumq', 'ru', 'rq')] = basepath+'seg_set_sum_rr.txt'
    files[('setu', 'sumq', 'pu', 'rq')] = basepath+'seg_set_sum_pr.txt'
    files[('setu', 'sumq', 'ru', 'pq')] = basepath+'seg_set_sum_rp.txt'

    files[('minu', 'minq', 'ru', 'rq')] = basepath+'seg_min_min_rr.txt'
    files[('minu', 'minq', 'pu', 'rq')] = basepath+'seg_min_min_pr.txt'
    files[('minu', 'minq', 'ru', 'pq')] = basepath+'seg_min_min_rp.txt'
    files[('setu', 'minq', 'ru', 'rq')] = basepath+'seg_set_min_rr.txt'
    files[('setu', 'minq', 'pu', 'rq')] = basepath+'seg_set_min_pr.txt'
    files[('setu', 'minq', 'ru', 'pq')] = basepath+'seg_set_min_rp.txt'


    files[('maxu', 'maxq', 'ru', 'rq')] = basepath+'seg_max_max_rr.txt'
    files[('maxu', 'maxq', 'pu', 'rq')] = basepath+'seg_max_max_pr.txt'
    files[('maxu', 'maxq', 'ru', 'pq')] = basepath+'seg_max_max_rp.txt'
    files[('setu', 'maxq', 'ru', 'rq')] = basepath+'seg_set_max_rr.txt'
    files[('setu', 'maxq', 'pu', 'rq')] = basepath+'seg_set_max_pr.txt'
    files[('setu', 'maxq', 'ru', 'pq')] = basepath+'seg_set_max_rp.txt'

    files['templated'] = basepath+'seg_templated.txt'

    if 'default' in args:
        f = open(files['templated'], 'r')
        for line in f.readlines():
            fw.write(line)
        fw.flush()
        exit()


    for arg in args:
        if arg == 'ru' or arg == 'ur':
            default[2] = 'ru'
        elif arg == 'pu' or arg == 'up':
            default[2] = 'pu'
        elif arg == 'rq' or arg == 'qr':
            default[3] = 'rq'
        elif arg == 'pq' or arg == 'qp':
            default[3] = 'pq'
        elif arg in ('sumu', 'minu', 'maxu', 'setu'):
            default[0] = arg
        elif arg in ('sumq', 'minq', 'maxq'):
            default[1] = arg

    if tuple(default) not in files:
        print("segtree type not found here")
        exit()
    f = open(files[tuple(default)], 'r')
    for line in f.readlines():
        fw.write(line)
    fw.flush()

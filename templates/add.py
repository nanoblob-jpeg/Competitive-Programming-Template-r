import sys
from config import read_struct
basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"
class file_writer():
    def __init__(self, filename):
        self._filename = filename
        f = open(filename, 'r')
        self._lines = f.readlines()
        f.close()
        self._index = 0
        while self._index < len(self._lines) and self._lines[self._index].strip() != '//! function insert':
            self._index += 1
        self._towrite = []

    def write(self, ss):
        if(type(ss) is list):
            for s in ss:
                if type(s) is str:
                    if(len(s) == 0):
                        continue
                    if(s[-1] == '\n'):
                        self._towrite.append(s)
                    else:
                        self._towrite.append(s + '\n')
        elif type(ss) is str:
            if(len(ss) == 0):
                return
            if(ss[-1] == '\n'):
                self._towrite.append(ss)
            else:
                self._towrite.append(ss + '\n')

    def flush(self):
        f = open(self._filename, 'w')
        for i in range(self._index):
            f.write(self._lines[i])
        for line in self._towrite:
            f.write(line)
        for i in range(self._index, len(self._lines)):
            f.write(self._lines[i])
        f.close()

def parse_configs(filename):
    f = open(filename, 'r')
    lines = [x.strip() for x in f.readlines() if len(x.strip()) > 0]
    structs = []
    for line in lines:
        if line == "//!":
            structs.append([])
        else:
            assert len(structs) > 0
            structs[-1].append(line)

    ret = []
    names = set()
    for struct in structs:
        ret.append(read_struct("", struct, names, tostr = False))
    return ret

def add_to_hierarchy(config, hierarchy, name_to_path, alias_to_main):
    name_to_path[config['name']] = config['parser path']
    if 'alias' in config:
        for a in config['alias']:
            name_to_path[a] = config['parser path']
            alias_to_main[a] = config['name']
    alias_to_main[config['name']] = config['name']
    ref = hierarchy
    for i in range(len(config['types'])):
        if config['types'][i] not in ref:
            ref[config['types'][i]] = dict()
        ref = ref[config['types'][i]]
    if 'configs' in ref:
        ref['configs'].append(config)
    else:
        ref['configs'] = [config]

def build_hierarchy():
    hierarchy = dict()
    name_to_path = dict()
    alias_to_main = dict()
    configs = parse_configs(basepath+"master.conf")
    for config in configs:
        add_to_hierarchy(config, hierarchy, name_to_path, alias_to_main)
    return hierarchy, name_to_path, alias_to_main

def list_recurse(hierarchy, tt, indent, with_label = True):
    name_order = ['name', 'alias', 'desc']
    if tt != 'types':
        if 'configs' in hierarchy:
            for i in hierarchy['configs']:
                for j in name_order:
                    if j not in i:
                        if j == tt:
                            break
                        continue
                    if j == 'desc':
                        print('  '*(indent+int(j!='name')) + (j + ": " if with_label else ""))
                        vals = [x.strip() for x in i[j].split('|') if len(x.strip()) > 0]
                        for val in vals:
                            print('  '*(indent+int(j!='name')+1) + val)
                    else:
                        print('  '*(indent+int(j!='name')) + (j + ": " if with_label else "") + (i[j] if type(i[j]) is str else ','.join(i[j])))
                    if j == tt:
                        break
    for x, y in hierarchy.items():
        if x == 'configs':
            continue
        print('  '*indent + x)
        list_recurse(y, tt, indent+1, with_label)

def call(filename, args):
    if len(args) == 0:
        return
    hierarchy, name_to_path, alias_to_main = build_hierarchy()
    if args[0] == 'list':
        for i in range(2, len(args)):
            args[i] = args[i].upper()
        if len(args) == 1:
            list_recurse(hierarchy, 'name', 0, False)
        else:
            for i in range(2, len(args)):
                args[i] = args[i].upper()
                if args[i] not in hierarchy:
                    print("hierarchy path not found")
                    exit()
                hierarchy = hierarchy[args[i]]
            list_recurse(hierarchy, args[1] if args[1] != 'main' else 'name', 0)
    else:
        if args[0] not in name_to_path:
            print('template not found')
            return
        
        fw = file_writer(filename)

        first, second = name_to_path[alias_to_main[args[0]]].strip().replace("\\", '/').rsplit("/",1)
        if '.' in second:
            second = second.split('.', 1)[0]
        sys.path.append(basepath+first)
        r = __import__(second)
        r.parse(fw, alias_to_main[args[0]], args[1:])















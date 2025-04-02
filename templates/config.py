from pathlib import Path

basepath = Path('.')
def getlen(p):
    global basepath
    out = 0
    while p != basepath:
        out += 1
        p = p.parent
    return out

master_configs = open("master.conf", "w")
conf_files = list(basepath.glob("**/*.conf"))
lengths = {x:getlen(x) for x in conf_files}

type_confs = [x for x in conf_files if x.name == "type.conf"]
type_confs.sort(key=lambda x:lengths[x])

nested_types = {}
for t in type_confs:
    a = open(t, "r")
    lines = a.readlines()
    if len(lines) < 1:
        print(f"config error in {t}")
        exit()
    if len(lines[0]) < 1:
        print(f"config error in {t}")
        exit()
    a.close()

    temp = t
    while temp != basepath:
        if temp in nested_types:
            nested_types[t.parent] = nested_types[temp] + "," + lines[0].strip()
            break
        temp = temp.parent

    if t.parent not in nested_types:
        nested_types[t.parent] = lines[0].strip()

def gettype(p):
    global nested_types, basepath
    while p != basepath:
        if p in nested_types:
            return nested_types[p]
        p = p.parent
    return "ETC"

parser_confs = [x for x in conf_files if x.name == "parser.conf"]
names = set()
def read_struct(p, configs):
    global names
    assert len(configs) > 0
    ret = dict()

    for line in configs:
        tokens = [x.strip() for x in line.split(',') if len(x.strip()) > 0]
        assert len(tokens) == 2, p+" too many arguments on one line"
        if tokens[0] == "name":
            assert "name" not in ret, p+" multiple name configs"
            real_name = tokens[1].replace(' ', '_')
            assert real_name not in names, p+" duplicate on " + real_name
            names.add(real_name)
            ret["name"] = real_name
        elif tokens[0] == "desc":
            if "desc" in ret:
                ret["desc"] = ret["desc"] + ' ' + tokens[1]
            else:
                ret["desc"] = tokens[1]
        else:
            assert False, p+" unrecognized config option"

    assert "name" in ret, p+" config needs name option"
    return ret

for p in parser_confs:
    a = open(p, "r")
    lines = [x.strip() for x in a.readlines() if len(x.strip()) > 0]
    structs = []
    for line in lines:
        if line == "//!":
            structs.append([])
        else:
            assert len(structs) > 0
            structs[-1].append(line)

    for struct in structs:
        vals = read_struct(str(p), struct)
        master_configs.write("//!\n")
        master_configs.write("parser path," + str(p.parent/'parser.py')+"\n")
        master_configs.write("types," + gettype(p) + "\n")
        for x, y in vals.items():
            master_configs.write(x + "," + y + '\n')

    a.close()
master_configs.close()

from pathlib import Path

basepath = Path('.')
def getlen(p):
    global basepath
    out = 0
    while p != basepath:
        out += 1
        p = p.parent
    return out

configs = open("master.conf", "w")
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
alises = set()
for p in parser_confs:
    a = open(p, "r")
    temp_struct = None
    for line in a.readlines():
        if line.strip() == "//!":
            if temp_struct is not None and len(temp_struct) != 0:
                if 'main name' not in temp_struct:
                    print(f"invalid parser.conf. no main name property in {p}")
                    temp_struct = {}
                    continue
                configs.write("//!\n")
                configs.write("types " + gettype(p) + "\n")
                for x, y in temp_struct.items():
                    configs.write(x + "," + ','.join(y) + '\n')
            temp_struct = {}
        else:
            tokens = [x.strip() for x in line.split(',') if len(x.strip()) != 0]
            if len(tokens) <= 1:
                continue
            if tokens[0] == 'alias' or tokens[0] == 'main name':
                for i in tokens[1:]:
                    if i in alises:
                        print(f"duplicate alias: {i}")
                        exit()
                    alises.add(i)

            if tokens[0] == 'main name' and len(tokens) != 2:
                print("can only have one main name")
                exit()

            if tokens[0] in temp_struct:
                temp_struct[tokens[0]].extend(tokens[1:])
            else:
                temp_struct[tokens[0]] = tokens[1:]


    if temp_struct is not None and len(temp_struct) != 0:
        if 'main name' not in temp_struct:
            print(f"invalid parser.conf. no main name property in {p}")
            temp_struct = {}
            continue
        configs.write("//!\n")
        configs.write("types " + gettype(p) + "\n")
        for x, y in temp_struct.items():
            configs.write(x + "," + ','.join(y) + '\n')

    a.close()
configs.close()

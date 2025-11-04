class TemplateReader:
    def __init__(self):
        self.parts = dict()

    def get_part(self, name):
        if name not in self.parts:
            return []
        return self.parts[name]

    def parse_file(self, file):
        active = set()
        with open(file, 'r') as f:
            for line in f.readlines():
                if line.strip().startswith("//! test"):
                    _, _, ty, name = line.strip().split()
                    if ty == 'start':
                        assert name not in active
                        active.add(name)
                        if name not in self.parts:
                            self.parts[name] = []
                    elif ty == 'end':
                        assert name in active
                        active.remove(name)
                    else:
                        assert False, "improper test command"
                else:
                    for name in active:
                        self.parts[name].append(line)

        assert len(active) == 0

class TestTemplateWriter:
    def __init__(self, output_path):
        self.output_path = output_path

    def template_test(self, test_path, template_reader):
        with open(self.output_path, 'w') as out_f:
            with open(test_path, 'r') as in_f:
                for line in in_f.readlines():
                    if line.strip().startswith("//! test"):
                        _, _, arg = line.strip().split()
                        for part in template_reader.get_part(arg):
                            if part.endswith('\n'):
                                out_f.write(part)
                            else:
                                out_f.write(part + '\n')
                    else:
                        if line.endswith('\n'):
                            out_f.write(line)
                        else:
                            out_f.write(line + '\n')

def add_stats_to_file(file, stats):
    lines = []
    with open(file, 'r') as f:
        lines = f.readlines()
    assert len(lines) > 0

    try:
        newlines = [x for x in lines]
        for i in range(len(lines)):
            if '//! stats end' in lines[i]:
                newlines = [x for x in lines[i+1:]]
                break
        with open(file, 'w') as f:
            if stats.endswith('\n'):
                f.write(stats)
            else:
                f.write(stats + '\n')
            f.write("//! stats end\n")
            for line in newlines:
                if line.endswith('\n'):
                    f.write(line)
                else:
                    f.write(line + '\n')
    except:
        with open(file, 'w') as f:
            for line in lines:
                if line.endswith('\n'):
                    f.write(line)
                else:
                    f.write(line + '\n')
        raise
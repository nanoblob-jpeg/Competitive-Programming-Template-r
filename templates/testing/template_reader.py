import json

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

    def template_test(self, test_path, template_reader, alias_mapping = dict()):
        with open(self.output_path, 'w') as out_f:
            with open(test_path, 'r') as in_f:
                for line in in_f.readlines():
                    if line.strip().startswith("//! test"):
                        _, _, arg = line.strip().split()
                        if arg in alias_mapping:
                            arg = alias_mapping[arg]
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

class ConfigReader:
    def __init__(self):
        self.configs = dict()

    def parse_file(self, file):
        with open(file, 'r') as f:
            data = json.load(f)

            for key, item in data.items():
                self.configs[key] = item

class StatsConfigReader:
    def __init__(self):
        self.configs = dict()

    def parse_file(self, file):
        with open(file, 'r') as f:
            name = ""
            text = []
            nameline = False
            for line in f.readlines():
                if line.strip() == "//!":
                    if name != "":
                        self.configs[name] = ''.join(text)
                    nameline = True
                    name = ""
                    text = []
                elif nameline:
                    name = line.strip()
                    nameline = False
                else:
                    if line.strip() != "":
                        text.append(line.strip() + '\n')
            if name != "":
                self.configs[name] = ''.join(text)

    def get(self, val):
        if val in self.configs:
            return self.configs[val]
        else:
            return "%.0fms, %0.2fMb"

# TODO: create a temp database with file hash
# minus comments so that we can get averaged
# more consistent timings
def add_stats_to_file(file, stats, append = False):
    lines = []
    with open(file, 'r') as f:
        lines = f.readlines()
    assert len(lines) > 0

    try:
        stat_lines = []
        newlines = [x for x in lines]
        for i in range(len(lines)):
            if '//! stats end' in lines[i]:
                newlines = [x for x in lines[i+1:]]
                stat_lines = [x for x in lines[:i]]
                break
        with open(file, 'w') as f:
            if append:
                for line in stat_lines:
                    if line.endswith('\n'):
                        f.write(line)
                    else:
                        f.write(line + '\n')
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

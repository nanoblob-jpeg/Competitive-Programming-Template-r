from template_reader import TemplateReader, TestTemplateWriter, ConfigReader, StatsConfigReader, add_stats_to_file
from oj_wrapper import run_wrapper_wrapper
import subprocess, os, shutil, sys
basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"

# returns true if the subprocess executed successfully
def generate_tests(test):
    ret = subprocess.run(f"python {basepath}/library-checker-problems/generate.py --silent -p {test}")
    return ret.returncode == 0

def cleanup_tests(test):
    print("cleaning")
    path = test if type(test) is str else '/'.join(test)
    possible = "abcdefghijklmnopqrstuvwxyz-_/"
    for c in path:
        assert c in possible
    if os.path.isdir(f"{basepath}/library-checker-problems/{path}/in"):
        shutil.rmtree(f"{basepath}/library-checker-problems/{path}/in")
    if os.path.isdir(f"{basepath}/library-checker-problems/{path}/out"):
        shutil.rmtree(f"{basepath}/library-checker-problems/{path}/out")

test_configs = ConfigReader()
test_configs.parse_file(f"{basepath}/tests.conf")

stats_configs = StatsConfigReader()
stats_configs.parse_file(f"{basepath}/stats.conf")

just_template = False
just_compile = False

def run_test(template_name, test_options, write_stats = False):
    # make sure we have all of the options we need
    if "library-checker-path" not in test_options or "library-checker-name" not in test_options or "test-template-file" not in test_options:
        print("%s has incorrect test options" % template_name)
        print(test_options)
        return

    # attempt to generate the test files
    if not generate_tests(test_options["library-checker-name"]):
        print("%s : failed in generation of test cases" % test_options["library-checker-name"])
        return

    # parse the template files
    tr = TemplateReader()
    tr.parse_file(f"{basepath}../{template_name}")
    if "additional-template-files-to-parse" in test_options:
        for file in test_options["additional-template-files-to-parse"]:
            tr.parse_file(f"{basepath}{file}")

    # write a temp file
    ofile = f"{basepath}temp.cpp"
    tw = TestTemplateWriter(ofile)
    alias_mapping = dict() if "test-replace-alias-mapping" not in test_options else test_options["test-replace-alias-mapping"]
    tw.template_test(test_options["test-template-file"], tr, alias_mapping)

    if just_template:
        return

    try:
        # compile with O2
        ret = subprocess.run(f"g++ -static -Wl,--stack=268435456 -O2 temp.cpp")
        if ret.returncode != 0:
            print("%s was unable to compile" % template_name)
            print(ret.stdout)
            print(ret.stderr)
            return

        if just_compile:
            return


        ac_count, total_tests, slowest, heaviest, hist = run_wrapper_wrapper(test_options['library-checker-path'])
        if ac_count != total_tests:
            print("%s failed on %s with %i/%i correct" % (template_name, test_options['library-checker-name'], ac_count, total_tests))
        else:
            if write_stats:
                # TODO: add writing stats code
                pass
            print("%s passed on %s" % (template_name, test_options['library-checker-name']))
            if "stats-format-string" in test_options:
                print(stats_configs.get(test_options['stats-format-string']) % (slowest*1000, heaviest), end='')
            else:
                print("slowest %fms" % (slowest*1000))
                print("heaviest %fMb" % heaviest)
    finally:
        if os.path.exists(ofile):
            os.remove(ofile)


def run_all_test(template_name):
    if template_name in test_configs.configs:
        if "tests" not in test_configs.configs[template_name]:
            print("no tests configured for %s" % template_name)
        else:
            print("running tests for exact template match %s" % template_name)
            for test in test_configs.configs[template_name]["tests"]:
                run_test(template_name, test)

    for temp_name, conf in test_configs.configs.items():
        if "categories" in conf and template_name in conf["categories"]:
            if "tests" not in conf:
                print("no tests configured for %s" % temp_name)
            else:
                print("running test for category match %s" % temp_name)
                for test in conf["tests"]:
                    run_test(temp_name, test)

    for temp_name, conf in test_configs.configs.items():
        if "aliases" in conf and template_name in conf["aliases"]:
            if "tests" not in conf:
                print("no tests configured for %s" % temp_name)
            else:
                print("running test for alias match %s" % temp_name)
                for test in conf["tests"]:
                    run_test(temp_name, test)



# TODO: delete this and add actual test parsing
# need to add parsing for passing silent to test generation also - off by default
run_all_test("uf_base")

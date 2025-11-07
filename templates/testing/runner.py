from template_reader import TemplateReader, TestTemplateWriter, ConfigReader, add_stats_to_file
import subprocess, os, shutil, sys
basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"

# returns true if the subprocess executed successfully
def generate_tests(test):
    ret = subprocess.run(f"python {basepath}/library-checker-problems/generate.py -p {test}")
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

def run_test(template_name, test_options):
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
    tr.parse_file(template_name)
    if "additional-template-files-to-parse" in test_options:
        for file in test_options["additional-template-files-to-parse"]:
            tr.parse_file(file)

    # write a temp file
    ofile = "temp.cpp"
    tw = TestTemplateWriter(ofile)
    alias_mapping = dict() if "test-replace-alias-mapping" not in test_options else test_options["test-replace-alias-mapping"]
    tw.template_test(test_options["test-template-file"], tr, alias_mapping)

    # TODO: compile solution with -O2, then run wrapper


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
if not generate_tests("unionfind"):
    print("failed in generation of test cases")
    exit(0)

#cleanup_tests(["data_structure", "unionfind"])



import subprocess, os, shutil
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


if not generate_tests("unionfind"):
    print("failed in generation of test cases")
    exit(0)

cleanup_tests(["data_structure", "unionfind"])

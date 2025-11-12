import subprocess, os, shutil, sys, argparse, glob
from logging import DEBUG, INFO, CRITICAL, StreamHandler, basicConfig, getLogger
logger = getLogger(__name__)
basepath = __file__.replace("\\", "/").rsplit("/", 1)[0] + "/"

oj_module_dir = os.path.abspath(os.path.join(basepath, 'oj'))
sys.path.insert(0, oj_module_dir)

from onlinejudge_command.subcommand.test import add_subparser, run
from onlinejudge_command import log_formatter

def get_parser():
    parser = argparse.ArgumentParser(
        description='Tools for online judge services',
        formatter_class=argparse.RawTextHelpFormatter,
        epilog='''\
tips:
  The official tutorial exists on the web: https://github.com/online-judge-tools/oj/blob/master/docs/getting-started.md
''',
    )
    parser.add_argument('-v', '--verbose', action='store_true')
    parser.add_argument('--version', action='store_true', help='print the online-judge-tools version number')

    subparsers = parser.add_subparsers(dest='subcommand', help='for details, see "{} COMMAND --help"'.format(sys.argv[0]))
    add_subparser(subparsers)

    return parser

def run_wrapper(args):
    parser = get_parser()
    parsed = parser.parse_args(args=args)

    level = INFO
    if parsed.verbose:
        level = DEBUG
    if parsed.silent:
        level = CRITICAL
    handler = StreamHandler(sys.stdout)
    handler.setFormatter(log_formatter.LogFormatter())
    basicConfig(level=level, handlers=[handler])

    # (ac_count, slowest, heaviest(memory), list of history)
    # example history thing: 
    """
    {
        'status': 'AC', 
        'testcase': {'name': 'example_00', 'input': 'file path', 'output': 'file path'}, 
        'output': '0\r\n1\r\n0\r\n1\r\n', 
        'exitcode': 0, 
        'elapsed': 0.008006799966096878, 
        'memory': None
    }
    """
    return run(parsed)

def run_wrapper_wrapper(test_path, silent = True):
    in_files = glob.glob(f'./library-checker-problems/{test_path}/in/*')
    out_files = glob.glob(f'./library-checker-problems/{test_path}/out/*')
    args = ['t']
    if silent:
        args.append('--silent')
    args.append(f'--format=library-checker-problems/{test_path}/%f/%s.%e')
    args.append('--directory=./')
    args.extend(in_files)
    args.extend(out_files)
    ac_count, slowest, heaviest, hist = run_wrapper(args)
    return (ac_count, len(in_files), slowest, heaviest, hist)

if __name__ == '__main__':
    in_files = glob.glob('./library-checker-problems/data_structure/unionfind/in/*')
    out_files = glob.glob('./library-checker-problems/data_structure/unionfind/out/*')
    args = ['t', '--silent', '--format=library-checker-problems/data_structure/unionfind/%f/%s.%e', '--directory=./']
    args.extend(in_files)
    args.extend(out_files)
    a, b, c, d = run_wrapper(args)
    print(a, b, c, len(in_files))

'''
TODO:
    write parser for the test files which increases stack size using the stsize thing we have
    make this configurable to run the different tests
    figure out how to parse the output from it
    write config file for stats logging messages
'''

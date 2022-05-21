# Checking with stdin/stdout
# TODO: rework for input.txt and output.txt

import argparse
import subprocess
import sys
from contextlib import contextmanager
import os
import re


class TestCase:
    def __init__(self, input_path, output_path):
        self.input_path = input_path
        self.output_path = output_path


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("exe")
    parser.add_argument("tests_dir")
    args = parser.parse_args()
    return args


def try_get_file_index(file_name, prefix):
    m = re.search("^" + prefix + "(\d+).txt$", file_name)
    if m:
        return m.group(1)
    return None


def run_program(exe, args, stdin) -> str:
    cmd_args = [exe] + args
    p = subprocess.Popen(cmd_args, stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.PIPE)
    stdout = p.communicate(input=bytes(stdin, encoding="utf-8"))[0]
    return str(stdout, encoding="utf-8")


def get_test_cases_from_dir(tests_dir):
    all_files = os.listdir(tests_dir)
    test_cases = dict()
    for file_name in all_files:
        file_path = os.path.join(tests_dir, file_name)
        file_index = try_get_file_index(file_name, "input")
        if file_index != None:
            if not file_index in test_cases:
                test_cases[file_index] = TestCase(file_path, None)
            else:
                test_cases[file_index].input_path = file_path
        file_index = try_get_file_index(file_name, "output")
        if file_index != None:
            if not file_index in test_cases:
                test_cases[file_index] = TestCase(None, file_path)
            else:
                test_cases[file_index].output_path = file_path

    valid_test_cases = []
    for key, value in test_cases.items():
        if value.input_path != None and value.output_path != None:
            valid_test_cases.append(value)
    return valid_test_cases


def read_file(path):
    with open(path, "r") as f:
        content = f.read()
        return content


def test_correct_program(exe_path, test_cases):
    passed_tests = []
    for test_case in test_cases:
        input_content = read_file(test_case.input_path)
        expected_output = read_file(test_case.output_path).replace("\r\n", "\n")
        actual_output = run_program(exe_path, [], input_content).replace("\r\n", "\n")
        if strings_are_similar(expected_output, actual_output):
            passed_tests.append(test_case)
            print(test_case.input_path, test_case.output_path, "passed")
        else:
            print(test_case.input_path, test_case.output_path, "failed")
    return passed_tests


def remove_trailing_eols(s):
    lines = s.split("\n")
    result = []
    skip_empty_items = True
    for line in reversed(lines):
        if len(line) or not skip_empty_items:
            result.append(line)
            skip_empty_items = False
    result.reverse()
    return result


def strings_are_similar(lhs, rhs):
    return remove_trailing_eols(lhs) == remove_trailing_eols(rhs)


def test(tests_dir, exe_path):
    test_cases = get_test_cases_from_dir(tests_dir)
    passed_tests = test_correct_program(exe_path, test_cases)
    print("passed tests:", len(passed_tests), "/", len(test_cases))


def main():
    args = parse_args()
    test(args.tests_dir, args.exe)


sys.exit(main())

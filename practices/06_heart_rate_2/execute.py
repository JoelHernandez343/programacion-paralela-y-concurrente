#!/usr/bin/env python3

import pexpect, sys


def check_args():
    length = len(sys.argv)

    if length != 2:
        print("\033[40;31mERR!\033[0m Argument is missing or there is more than one.\n")
        exit(0)

    method = sys.argv[1].lower()

    if method != "thread" and method != "process":
        print('\033[40;31mERR!\033[0m Argument must be "thread" or "process".\n')

    return method


def get_output(raw_output):
    lines = raw_output.decode("UTF-8").replace("\r", "").split("\n")
    lines.pop()
    lines.pop(0)

    return "\n".join(lines)


commands = ["make clean", "make", "./main " + check_args()]
# graphs = ["PulseSensor.dat", "hann.data", "windowed.data", "rxx.data"]
graphs = ["rxx.data"]

child = pexpect.spawn("bash")
child.expect(r"\$")

for command in commands:
    print("[Executed] " + command)
    child.sendline(command)
    child.expect(r"\$")
    print(get_output(child.before))

for graph in graphs:
    child = pexpect.spawn("gnuplot -persistent")
    child.expect(">")
    child.sendline(f'plot "{graph}" with lines')
    child.expect(">")

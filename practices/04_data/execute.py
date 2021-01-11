#!/usr/bin/env python3

import pexpect, sys

def check_args():
    length = len(sys.argv)

    if (length != 2):
        print('\033[40;31mERR!\033[0m Argument is missing or there is more than one.\n')
        exit(0)
    
    method = sys.argv[1].lower();

    if (method != 'thread' and method != 'process'):
        print('\033[40;31mERR!\033[0m Argument must be "thread" or "process".\n')

    return method

def get_output(raw_output):
    lines = raw_output.decode('UTF-8').replace('\r', '').split('\n')
    lines.pop()
    lines.pop(0)

    return '\n'.join(lines)

commands = [
    'make clean', 'make', './main ' + check_args()
]
gnuplot_commands = [
    'plot "PulseSensor.dat" with lines',
    'replot "hann.data" with lines',
    'replot "result.data" with lines'
]

child = pexpect.spawn('bash')
child.expect(r'\$')

for command in commands:
    print('[Executed] ' + command)
    child.sendline(command)
    child.expect(r'\$')
    print(get_output(child.before))

child = pexpect.spawn('gnuplot -persistent')
child.expect('>')
for command in gnuplot_commands:
    print('[Executed] ' + command)
    child.sendline(command)
    child.expect('>')
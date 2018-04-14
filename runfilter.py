#!/usr/bin/env python3
import sys
import subprocess
filter_statement = sys.argv[1]
shell_statement = 'gtpp.py ./runner --gtest_filter=' + filter_statement + ' --gtest_shuffle'
subprocess.call(shell_statement, shell=True)

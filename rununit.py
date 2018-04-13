#!/usr/bin/env python3
import subprocess
subprocess.call('gtpp.py ./runner --gtest_filter=Unit* --gtest_shuffle', shell=True)

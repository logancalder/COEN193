#  Copyright 2020 HPS/SAFARI Research Groups
#
#  Permission is hereby granted, free of charge, to any person obtaining a copy of
#  this software and associated documentation files (the "Software"), to deal in
#  the Software without restriction, including without limitation the rights to
#  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
#  of the Software, and to permit persons to whom the Software is furnished to do
#  so, subject to the following conditions:
#
#  The above copyright notice and this permission notice shall be included in all
#  copies or substantial portions of the Software.
#
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
#  SOFTWARE.

"""
# Sanity Check Using QSORT Example

./utils/qsort includes a small test program for running libc's qsort() on
random data that we use for sanity checks. To run it, use:

> python ./bin/scarab_test_qsort.py path_to_results_directory

./utils/qsort/ref_stats includes sample stats that you can use for sanity
checks. The exact statistics are unlikely to match with the reference stats
because the produced binary is compiler-dependent.

"""

from __future__ import print_function

import argparse
import os
import shutil
import subprocess
import sys

scarab_root_path = '/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/scarab'
sys.path.append(scarab_root_path + '/bin')

def build_test_loop():
  print('Building the test qsort static binary')
  curr_dir = os.getcwd()
  os.chdir('/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/scarab/test/matmul/')
  os.chdir(curr_dir)

def switch_to_sim_dir():
  print ('Simulation Directory:', os.path.abspath(args.sim_dir))
  os.chdir(args.sim_dir)

def run_scarab():
  scarab_cmd_argv = [sys.executable,
                     '/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/scarab/bin/scarab_launch.py',
                     '--program',
                     '/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/scarab/test/matmul/loop',
                     '--param',
                     '/WAVE/users/unix/lcalder/ycho_lab/logan_calder/workspace/scarab/test/matmul/PARAMS.in']# --power_intf_on 1']
  print ('Scarab cmd:', ' '.join(scarab_cmd_argv))
  subprocess.check_call(scarab_cmd_argv)

def __main():
  global args

  parser = argparse.ArgumentParser(description='Testing Scarab w/ Matmul')
  parser.add_argument('sim_dir', help='Path to the simulation directory.')
  args = parser.parse_args()

  os.makedirs(args.sim_dir, exist_ok=True)
  build_test_loop()
  switch_to_sim_dir()
  run_scarab()

if __name__ == "__main__":
  __main()
# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import sys
from framework import Framework

def run_t():

   def parse(output):
      #return {framework.outputHeaders[0]: float(output)}
      return {}

   framework = Framework()
   framework.isClient = False
   framework.outputParser = parse
   framework.waitTime = 0.5
   
   framework.command = "fio"
   framework.numRuns = 1
   framework.headerNames = ['Duration in Seconds (-D)', \
                            'TxDepth (-t)', \
                            'Report GBits (--report_gbits)']
   framework.outputHeaders = ['Bandwidth in Gb/s']
   framework.params = [
      ('--rw=', ['read']),
      ('--bs=', ['1k']),
      ('--filename=', [Framework.ramDiskPath])
   ]
   framework.runBenchmarks()


def run_s():

   def parse(output):
      #return {framework.outputHeaders[0]: float(output)}
      return {}

   framework = Framework()
   framework.isClient = False
   framework.outputParser = parse
   framework.waitTime = 0.5
   
   framework.command = "/usr/local/bin/fio"
   framework.numRuns = 1
   #framework.headerNames = ['Duration in Seconds (-D)', \
   #                         'TxDepth (-t)', \
   #                         'Report GBits (--report_gbits)']
   framework.outputHeaders = ['Bandwidth in Gb/s']
   # REMOVE BELOW
   Framework.ramDiskPath = '/mnt/local_ramdisk'
   framework.params = [
      ('--rw=', ['read']),
      ('--bs=', ['1k']),
      ('--numjobs=', ['1']),
      ('--iodepth=', ['128']),
      ('--runtime=', ['10']),
      ('--time_based', ['']),
      ('--loops=', ['1']),
      ('--ioengine=', ['libaio']),
      #('--direct=', ['1']),
      #('--invalidate=', ['1']),
      ('--minimal', ['']),
      ('--fsync_on_close=', ['1']),
      ('--randrepeat=', ['1']),
      ('--norandommap', ['']),
      ('--exitall', ['']),
      ('--name=', ['task1']),
      ('--size=', ['10M']),
      ('--directory=', [Framework.ramDiskPath])
   ]
   framework.headerNames = [ x[0] for x in \
                             framework.params]
   framework.runBenchmarks()


if __name__ == "__main__":
   if sys.argv[1] == '-t':
      run_t()
   elif sys.argv[1] == '-s':
      run_s()
   else:
      print("Please specify -t or -s")

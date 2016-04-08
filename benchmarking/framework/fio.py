# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import sys
from framework import Framework

def run_t(diskPath):

   def parse(output):
      return {framework.outputHeaders[0]: float(output)}

   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.isClient = False
   framework.outputParser = parse
   framework.waitTime = 0.5
   framework.headerNames = ['Duration in Seconds (-D)', \
                            'TxDepth (-t)', \
                            'Report GBits (--report_gbits)']
   framework.outputHeaders = ['Bandwidth in Gb/s']
   framework.params = [
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('--report_gbits', ['']),
      ('--output=', ['bandwidth'])
   ]
   framework.runBenchmarks()


def run_s(diskPath):

   def parse(output):
      return {framework.outputHeaders[0]: float(output)}

   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.isClient = True
   framework.outputParser = parse
   framework.headerNames = ['Port (tnvme40Gp1)', \
                            'Duration in Seconds (-D)', \
                            'TxDepth (-t)', \
                            'Report GBits (--report_gbits)']
   framework.outputHeaders = ['Bandwidth in Gb/s']
   framework.params = [
      ('tnvme40Gp1', ['']),
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('--report_gbits', ['']),
      ('--output=', ['bandwidth'])
   ]
   framework.runBenchmarks() 


if __name__ == "__main__":
   if sys.argv[1] == '-t':
      run_t()
   elif sys.argv[1] == '-s':
      run_s()
   else:
      print("Please specify -t or -s")
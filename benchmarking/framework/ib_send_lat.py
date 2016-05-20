# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import sys
from framework import Framework, setDirectory

def run_t():

   def parse(output, headers):
      return {framework.outputHeaders[0]: float(output)}

   framework = Framework()
   
   framework.command = "ib_send_lat"
   framework.numRuns = 3
   framework.isClient = False
   framework.outputParser = parse
   framework.waitTime = 0.5
   framework.headerNames = ['Duration in Seconds (-D)', 
                            'TxDepth (-t)']
   framework.outputHeaders = ['Latency in ms']
   framework.params = [
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('-R', ['']),
      ('--report_gbits', ['']),
      ('--output=', ['latency'])
   ]
   framework.runBenchmarks()


def run_s():

   def parse(output, headers):
      return {framework.outputHeaders[0]: float(output)}

   framework = Framework()
   
   framework.command = "ib_send_lat"
   framework.numRuns = 3
   framework.isClient = True
   framework.outputParser = parse
   framework.headerNames = ['Duration in Seconds (-D)', 
                            'TxDepth (-t)']
   framework.outputHeaders = ['Latency in ms']
   framework.params = [
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('-R', ['']),
      ('tnvme40Gp1', ['']),
      ('--report_gbits', ['']),
      ('--output=', ['latency'])
   ]
   framework.runBenchmarks() 


if __name__ == "__main__":

   if not (sys.argv[1] == '-t' or sys.argv[1] == '-s'):
      print("Please specify -t or -s")
      exit(1)

   setDirectory()

   if sys.argv[1] == '-t':
      run_t()
   elif sys.argv[1] == '-s':
      run_s()

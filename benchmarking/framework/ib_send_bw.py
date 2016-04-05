import sys
from framework import Framework

outputHeaders_t = ['Gb/s']
outputHeaders_s = ['Gb/s']

def run_t():
   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.isClient = False
   framework.outputParser = parse
   framework.waitTime = 0.5
   framework.headerNames = ['Duration (-D)', 'TxDepth (-t)', 'Report GBits (--report_gbits)']
   framework.outputHeaders = outputHeaders_t
   framework.params = [
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('--report_gbits', ['']),
      ('--output=', ['bandwidth'])
   ]
   framework.runBenchmarks()

def run_s():
   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.isClient = True
   framework.params = [
      ('tnvme40Gp1', ['']),
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('--report_gbits', [''])
   ]
   framework.runBenchmarks() 

def parse_t(output):
   return {outputHeader_t[0]: output}

def parse_s(output):
   return {}

if __name__ == "__main__":
   if sys.argv[1] == '-t':
      run_t()
   elif sys.argv[1] == '-s':
      run_s()
   else:
      print("Please specify -s or -t")

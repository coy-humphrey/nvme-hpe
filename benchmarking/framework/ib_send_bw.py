import sys
from framework import Framework

def run_t():
   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.params = [
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('--report_gbits', [''])
   ]
   framework.runBenchmarks()
   framework.ppOutput()

def run_s():
   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.params = [
      ('tnvme40Gp1', ['']),
      ('-D', ['1', '3', '5']),
      ('-t', ['256', '512']),
      ('--report_gbits', [''])
   ]
   framework.runBenchmarks()
   framework.ppOutput()

if __name__ == "__main__":
   if sys.argv[1] == '-t':
      run_t()
   elif sys.argv[1] == '-s':
      run_s()
   else:
      print("Please specify -s or -t")

from framework import Framework

def run():
   framework = Framework()
   
   framework.command = "ib_send_bw"
   framework.numRuns = 3
   framework.params = [
      ('-t', ['60', '120', '240']),
      ('-bs', ['256', '512']),
      ('--interface', ['tnvme40Gb1'])
   ]
   framework.runBenchmarks()
   framework.ppOutput()

if __name__ == "__main__":
   run()

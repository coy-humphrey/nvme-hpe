from framework import Framework

def run():
   framework = Framework()
   
   framework.command = "ls"
   framework.numRuns = 3
   framework.params = [
      ('-l', ['']),
      ('-a', [''])
   ]
   framework.runBenchmarks()
   framework.ppOutput()

if __name__ == "__main__":
   run()

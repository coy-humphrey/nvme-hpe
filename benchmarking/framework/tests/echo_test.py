from framework import Framework

def run():
   framework = Framework()
   
   framework.command = "echo"
   framework.params = [
      ('-r', ['1']),
      ('-t', ['A']),
      ('-m', ['X','Y','Z']),
      ('-p', [''])
   ]
   framework.runBenchmarks()
   framework.ppOutput()

if __name__ == "__main__":
   run()

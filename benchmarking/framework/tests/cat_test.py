from framework import Framework

def run():
   framework = Framework()
   
   framework.command = "cat"
   framework.numRuns = 3
   framework.params = [
      ('', ['ls_test.py','cat_test.py','framework.py'])
   ]
   framework.runBenchmarks()
   framework.ppOutput()

if __name__ == "__main__":
   run()

import subprocess
import itertools
import time

class Framework:
   def __init__(self):
      self.outputParser = None
      self.command = None
      self.numRuns = 1
      self.params = None
      self.isClient = True
      
      self.output = {}
      self.allParams = None
        
   def runBenchmarks(self):
      self.generateParams()
      for paramList in self.allParams:
         paramString = self.getParamString(paramList)
         self.output[paramString] = []
         for numRun in range(self.numRuns):
            if self.isClient:
               time.sleep(0.5)
            self.output[paramString].append(
               subprocess.check_output(paramList))

   def getParamString(self, paramList):
      return ' '.join(paramList)

   # Pretty Print the Output
   def ppOutput(self):
      for paramString, paramOutputs in \
          self.output.iteritems():
         print("\nCOMMAND: " + paramString + "\n")
         for index, paramOutput in enumerate(paramOutputs):
            print("ITERATION " + str(index+1) + ":")
            print(paramOutput)
         
   def generateParams(self):
      param_list = [[[x[0] + y] for y in x[1]] \
                    for x in self.params]
      self.allParams = [[self.command] + \
                        [z for y in x for z in y if z] \
                        for x in \
                        itertools.product(*param_list)]

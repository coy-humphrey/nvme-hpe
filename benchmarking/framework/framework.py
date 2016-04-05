import subprocess
import itertools
import time
import csv

class Framework:
   def __init__(self):
      self.outputParser = None
      self.command = None
      self.numRuns = 1
      self.params = None
      self.headerNames = None
      self.isClient = True
      
      self.allParams = None
        
   def runBenchmarks(self):
      self.generateParams()
      self.generateArgValues()
      with open(self.command + '.csv', 'w') as csvfile:
         writer = csv.DictWriter(csvfile, fieldnames=self.headerNames)
         writer.writeheader()
         for paramList, argValuesList in \
             zip(self.allParams, self.allArgValues):
            for numRun in range(self.numRuns):
               if self.isClient:
                  time.sleep(0.5)
               output = subprocess.check_output(paramList)
               outputDict = self.outputParser(output)
               commandDict = self.generateCommandDict(argValuesList)
               combinedDict = outputDict.copy()
               combinedDict.update(commandDict)
               writer.writerow(combinedDict)

   # Pretty Print the Output
   def ppOutput(self):
      for paramString, paramOutputs in \
          self.output.iteritems():
         print("\nCOMMAND: " + paramString + "\n")
         for index, paramOutput in enumerate(paramOutputs):
            print("ITERATION " + str(index+1) + ":")
            print(paramOutput)
      
   # Create list of list commands: ex. [['echo','-t','hello']]
   def generateParams(self):
      param_list = [[[x[0] + y] for y in x[1]] \
                    for x in self.params]
      self.allParams = [[self.command] + \
                        [z for y in x for z in y if z] \
                        for x in \
                        itertools.product(*param_list)]
      
   # Create list of commands with flag and value in a tuple,
   # ex. [['echo',('-t','hello')]]
   def generateStructuredParams(self):
      pass

   # Using the user defined CSV parser, output the command and 
   # subprocess output in CSV format
   def outputCSV(self):
      pass

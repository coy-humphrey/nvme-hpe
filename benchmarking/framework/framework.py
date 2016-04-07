import subprocess
import itertools
import time
import csv
import os

class Framework:
   directory = None

   def __init__(self):
      self.outputParser = None
      self.command = None
      self.numRuns = 1
      self.params = None
      self.headerNames = None
      self.outputHeaders = None
      self.isClient = True
      self.waitTime = 0.5
      
      self.allParams = None
        
   def runBenchmarks(self):
      self.generateParams()
      self.generateArgValues()
      with open('CSVs/' + self.command + ('-s' if self.isClient else '-t') \
                + '.csv', 'w') as csvfile:
         writer = csv.DictWriter(csvfile, fieldnames=\
                                 (self.headerNames + self.outputHeaders))
         writer.writeheader()
         for paramList, argValuesList in \
             zip(self.allParams, self.allArgValues):
            for numRun in range(self.numRuns):
               if self.isClient:
                  time.sleep(self.waitTime)
               print('Running: ' + ' '.join(paramList))
               output = subprocess.check_output(paramList)
               outputDict = self.outputParser(output)
               commandDict = self.generateCommandDict(argValuesList)
               combinedDict = outputDict.copy()
               combinedDict.update(commandDict)
               writer.writerow(combinedDict)

   # Header names map to their command values for easy CSV output
   def generateCommandDict(self, argValuesList):
      return dict(zip(self.headerNames, argValuesList))
   
   # Create list of list commands: ex. [['echo','-t','hello']]
   def generateParams(self):
      param_list = [[[x[0] + y] for y in x[1]] \
                    for x in self.params]
      self.allParams = [[self.command] + \
                        [z for y in x for z in y if z] \
                        for x in \
                        itertools.product(*param_list)]

   def generateArgValues(self):
      param_list = [[[x[0], y] for y in x[1]] \
                    for x in self.params]
      self.allArgValues =  [ [y[1] for y in x ] \
                        for x in itertools.product(*param_list)]
      
def setDirectory():
   base_path = os.getcwd()
   t = time.localtime(time.time())
   time_str = time.strftime("%Y-%m-%d-%Hh-%Mm-%Ss", t)
   extended_path = os.path.join(base_path, "CSVs/" + time_str)

   if not os.path.exists(extended_path):
      os.makedirs(extended_path)

   Framework.directory = extended_path

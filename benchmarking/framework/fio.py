# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import sys
from framework import Framework, setDirectory, \
   setupLocalRamDisk, teardownLocalRamDisk, \
   setupRemoteRamDisk, teardownRemoteRamDisk

def run():

   def parse(output, headers):
      pOutput = output.split(';')
      outputIndices = [
         7, 48,
      ]
      outputResults = [pOutput[index] for index in 
                       outputIndices]
      return dict(zip(headers, outputResults))

   framework = Framework()

   framework.isClient = False
   framework.outputParser = parse
   framework.waitTime = 0.5
   
   framework.command = "/usr/local/bin/fio"
   framework.numRuns = 1
   framework.headerNames= [
      'IO Type',
      'Blocksize',
      'Number of Jobs',
      'IO Depth',
      'Data size',
      'Duration',
      'IO Engine',
      # 'Time Based',
      # 'Number of Iterations',
      # 'Minimal output',
      # 'Fsync on close',
      # 'Seed RNG for predictable runs',
      # 'No Random Map',
      # 'Exit all jobs after first finishes',
      # 'Task name',
      # 'Data Directory',
   ]
   framework.params = [
      ('--rw=', ['read', 'write', 'randread', 'randwrite', 'rw', 'randrw']),
      ('--bs=', ['1k', '4k', '8k', '1M', '10M']),
      ('--numjobs=', ['40']),
      ('--iodepth=', ['1', '4', '16', '64', '128']),
      ('--size=', ['1G']),
      ('--runtime=', ['10']),    
      ('--ioengine=', ['libaio']),
      # Lines below will not be output
      ('--time_based', ['']),
      ('--loops=', ['1']),
      ('--minimal', ['']),
      ('--fsync_on_close=', ['1']),
      ('--randrepeat=', ['1']),
      ('--norandommap', ['']),
      ('--exitall', ['']),
      ('--name=', ['task1']),
      ('--directory=', [Framework.ramDiskPath]),
   ]
   framework.outputHeaders = [
      'Read IOPS',
      'Write IOPS',
   ]
   framework.runBenchmarks()



if __name__ == "__main__":

   if sys.argv[1] == '-l':
      setup = setupLocalRamDisk
      teardown = teardownLocalRamDisk
   elif sys.argv[1] == '-r':
      setup = setupRemoteRamDisk
      teardown = teardownRemoteRamDisk
   else:
      print("Please specify -l or -r")
      exit(1)

   setDirectory()
   setup()
   run()
   teardown()
   

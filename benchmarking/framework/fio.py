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
         # Read Bandwidth
         6, 
         # Read IOPS
         7, 
         # Read Latency
         37, 38, 39, 40, 

         # Write Bandwidth
         47, 
         # Write IOPS
         48, 
         # Write Latency
         78, 79, 80, 81,

         # User CPU
         87,
         # System CPU
         88,
      ]
      outputResults = [pOutput[index] for index in 
                       outputIndices]
      return dict(zip(headers, outputResults))

   framework = Framework()

   if Framework.ramDiskPath == Framework.localRamDiskPath:
      framework.isClient = True
   else:
      framework.isClient = False

   framework.outputParser = parse
   framework.waitTime = 3
   
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
      ('--rw=', ['read', 'write', 'randread', 'randwrite', 
                 'rw', 'randrw']),
      #('--bs=', ['1k', '4k', '8k', '1M', '10M', '100M', '1G']),
      ('--bs=', ['1k', '4k', '8k', '16k']),
      ('--numjobs=', ['1']),
      ('--iodepth=', ['1']),
      ('--size=', ['80G']),
      ('--runtime=', ['300']),    
      ('--ioengine=', ['libaio']),
      # Lines below will not be outputted
      ('--time_based', ['']),
      ('--loops=', ['1']),
      ('--minimal', ['']),
      ('--fsync_on_close=', ['0']),
      ('--randrepeat=', ['1']),
      ('--norandommap', ['']),
      ('--exitall', ['']),
      ('--name=', ['task1']),
      ('--directory=', [Framework.ramDiskPath]),
   ]
   framework.outputHeaders = [
      'Read Bandwidth (KB/s)',
      'Read IOPS',
      'Read Latency Min (ms)',
      'Read Latency Max (ms)',
      'Read Latency Avg (ms)',
      'Read Latency Dev (ms)',

      'Write Bandwidth (KB/s)',
      'Write IOPS',
      'Write Latency Min (ms)',
      'Write Latency Max (ms)',
      'Write Latency Avg (ms)',
      'Write Latency Dev (ms)',

      'CPU Usage: User',
      'CPU Usage: System',
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

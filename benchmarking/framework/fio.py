# Authors: Coy Humphrey, Jayden Navarro
# Project: HPE UCSC Senior Design 2016
# Date: 4-7-2016

import sys
from framework import Framework, setDirectory, \
   setupLocalRamDisk, teardownLocalRamDisk, \
   setupRemoteRamDisk, teardownRemoteRamDisk

def run_local():

   def parse(output):
      #return {framework.outputHeaders[0]: float(output)}
      print "here!"
      print output
      return {}

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
      'Duration',
      'Time Based',
      'Number of Iterations',
      'IO Engine',
      'Minimal output',
      'Fsync on close',
      'Seed RNG for predictable runs',
      'Exit all jobs after first finishes',
      'Task name',
      'Data size',
      'Data Directory',
   ]
   framework.params = [
      ('--rw=', ['read']),
      ('--bs=', ['1k', '4k', '8k', '1M', '10M']),
      ('--numjobs=', ['1']),
      ('--iodepth=', ['1', '4', '16', '64','128']),
      ('--runtime=', ['10']),
      ('--time_based', ['']),
      ('--loops=', ['1']),
      ('--ioengine=', ['libaio']),
      ('--minimal', ['']),
      ('--fsync_on_close=', ['1']),
      ('--randrepeat=', ['1']),
      ('--norandommap', ['']),
      ('--exitall', ['']),
      ('--name=', ['task1']),
      ('--size=', ['10M', '100M', '5G', '10G', '50G']),
      ('--directory=', [Framework.ramDiskPath])
   ]
   framework.outputHeaders = []
   framework.runBenchmarks()

def run_remote():

   def parse(output):
      #return {framework.outputHeaders[0]: float(output)}
      return {}

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
      'Duration',
      'Time Based',
      'Number of Iterations',
      'IO Engine',
      'Minimal output',
      'Fsync on close',
      'Seed RNG for predictable runs',
      'Exit all jobs after first finishes',
      'Task name',
      'Data size',
      'Data Directory',
   ]
   framework.outputHeaders = []
   # REMOVE BELOW
   Framework.ramDiskPath = '/mnt/local_ramdisk'
   framework.params = [
      ('--rw=', ['read']),
      ('--bs=', ['1k']),
      ('--numjobs=', ['1']),
      ('--iodepth=', ['128']),
      ('--runtime=', ['10']),
      ('--time_based', ['']),
      ('--loops=', ['1']),
      ('--ioengine=', ['libaio']),
      #('--direct=', ['1']),
      #('--invalidate=', ['1']),
      ('--minimal', ['']),
      ('--fsync_on_close=', ['1']),
      ('--randrepeat=', ['1']),
      ('--norandommap', ['']),
      ('--exitall', ['']),
      ('--name=', ['task1']),
      ('--size=', ['10M']),
      ('--directory=', [Framework.ramDiskPath])
   ]
   # framework.headerNames = [ x[0] for x in \
   #                          framework.params]
   framework.runBenchmarks()

if __name__ == "__main__":
   
   if not (sys.argv[1] in ['-l', '-r']):
      print("Please specify -l or -r")
      exit(1)

   setDirectory()

   if sys.argv[1] == '-l':
      setupLocalRamDisk()
      run_local()
      teardownLocalRamDisk()

   if sys.argv[1] == '-r':
      setupRemoteRamDisk()
      run_remote()
      teardownRemoteRamDisk()

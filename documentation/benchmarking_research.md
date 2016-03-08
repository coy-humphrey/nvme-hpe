# Benchmarking Test and Framework Design Doc

## What we need to do next in this doc...REMOVE

* Work on details of framework (csv parser inheritance superclass blah)
* In Framework Outline separate the individual scripts from the framework
* Figure out how bonnie++ and other complex tools can be integrated into framework, if necessary.

## High Level Goals

* Benchmark IOPS using our protocol stack.

* Automate the process of running static benchmarks such as the "ib_*_*" commands with varying parameters, and then output the results visually (graphs).

* Run hard drive tests and block device tests. Compare the two.

* Properly setup/teardown the block device on server/client sides to create environment to run tests on the block devices.

## Use Cases



## Existing Frameworks

While there are many test automation frameworks out there, I haven't found any that deal specifically with benchmarking automation. I found one article that described how to automate one benchmarking tool (fio which we're actually going to use), but it didn't lay out an extensible framework.

By looking at generic automation frameworks and articles about building automated frameworks, I have identified the following key components:

* Have light tests, and a complex framework (rather than the other way around)
* 

### Resources

[javigon: automating fio tests with python](http://javigon.com/2015/04/28/automating-fio-tests-with-python/)
[simpleprogrammer.com: test automation framework architecture](http://simpleprogrammer.com/2014/04/14/test-automation-framework-architecture/)

## Framework Outline

1. Setup Environment

  * Setting up the raio_server and the block device, etc. (Mlnx, DOC-1528) (not necessary for ib_*_*, but is for fio, bonnie++, etc.)

2. Specify Command

  * "ib_send_bw"

3. Specify Set of Parameters (iterate over all combinations)

  * Number of runs = {3}, Timeout (sec) = {10,20,30,60}, Interface = {'tnvme40Gb1'}, Block Size (KB) = {256, 512, 1024}, etc.

4. Capture Output

  * Store output in a buffer

5. Environment Teardown

  * Unmount block device client, stop raio_server, etc. (Mlnx, DOC-1528)

5. Parse Output

  * Generate CSV

  * Each test needs to implement output parsing, so that it can be fed to the driver which then can create CSVs from the data and stuff...


## Framework Details

### Example

File: `ib_send_bw.py`

```python
framework = new Framework()

framework.setupRaioEnv()
framework.csvParser = new IbSendBwCsv()

framework.command = "ib_send_bw"
framework.numRuns = 3
framework.params = [
   ('-t', ['60', '120', '240']),
   ('-bs', ['256', '512']),
   ('--interface', ['tnvme40Gb1'])
]
framework.runBenchmarks()

framework.teardownRaioEnv()

framework.outputCSV()

class IbSendBwCsv(CsvParser):
   def parse():
       ...
```

File: `ib_send_bw.csv`

```
Run Number,Command,-t,-bs,|,IOPS
1,ib_send_bw,10,256,300
2,ib_send_bw,10,256,302
1,ib_send_bw,10,512,412
...
```

* cpu jobs (-j utilizing cores), 

## Benchmarking Tests

fio, bonnie++, ... (add parameters as well)

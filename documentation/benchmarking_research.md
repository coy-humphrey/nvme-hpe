# Benchmarking Test and Framework Design Doc

## High Level Goals

* Benchmark card-to-card throughput.
* Benchmark IOPS using our protocol stack.
* Benchmark sequential reads and writes, as well as random reads and writes.
* Run hard drive tests and block device tests. Compare the two.

* Automate the process of running static benchmarks such as the "ib_\*_\*" commands with varying parameters, and then output the results as CSVs (or JSON) for easy graph generation in excel (or programmatically in Python).
* Properly setup/teardown the block device on server/client sides to create environment to run tests on the block devices.
* Framework should handle exceptions cleanly, so that other tests can continue if one fails, but it is noted in a log.
* Create wrapper for more complex tools such as bonnie++ to properly handle its output and monitor the IOPS.
* Gracefully handle synchronization between Client/Server.

## Use Cases

### Use Case 1: Benchmark different metrics (IOPS, bandwidth, latency,...)

* **ACTOR:** Project Sponsor.

* **Requirements:**
  1. Use one or multiple tools to acquire results on the different metrics.
  2. Vary parameters to gather a range of data on the different metrics.

#### Use Case 2: View benchmark results visually

* **Actor:** Project Sponsor.

* **Requirements:**
  1. View graphs from the benchmarking data.
  2. Comment describing significance of each graph.

#### Use Case 3: Create static benchmarks

* **Actor:** Developer.

* **Requirements:**
  1. Be able to specify command.
  2. Be able to specify range of parameters.
  3. Be able to specify number of iterations per command.
  4. Be able to provide way to parse the command output.

* **Basic Flow:**
  1. Create file using the name of the static benchmark and the extension '.py'; implement the below in the file.
  2. Following the framework format, specify the command, parameters, and number of runs.
  3. Setup the proper environment required for the command (ex. Raio Server - Block Devices setup).
  4. Create the output parser.
  5. Run the test.
  6. Teardown the environment.
  7. Add the generated script into the "run-all" script.

#### Use Case 4: Run static benchmarks

* **Actor:** Developer.

* **Requirements:**
  1. Be able to run the benchmarks.
  2. View the output in a nicely formatted CSV file.

* **Basic Flow:**
  1. Execut the "run-all" script.

<!---
#### Use Case 5: Create complex benchmarks

* **Actor:** Developer.

* **Basic Flow:**
  1. TODO

#### Use Case 6: Run complex benchmarks

* **Actor:** Developer.

* **Requirements:**
  1. Be able to run the benchmarks.
  2. View the output in a nicely formatted file (probably CSV).

* **Basic Flow:**
  1. Execut the "run-all" script.
-->

## Benchmarking Tests

#### ib_*_*

* **Purpose:** Establish card-to-card bandwidth and latency.

* **Parameters:**
  * **timeout (secs):** [5, 30, 60]
  * **rx-depth (KB):** [256, 512, 1024]
  * **tx-depth (KB):** [64, 128, 256]
  * **size of message (B):** [32768, 65536, 131072]
  * **iters:** [100, 500, 1000, 5000, 10000]

#### FIO

* **Purpose:** Establish bandwidth during block device reads/writes.

* **Parameters:**
  * **runtime (secs):** [600]
  * **size (%):** [1%, 5%, 20%, 50%, 100%]
  * **blocksize_range (B):** [1k-4k, 2k-8k]
  * **numjobs:** [1, 20, 40]

#### Bonnie++

* **Purpose:** Test IO performance (metric unclear).

* **Parameters:**
  * **file size (default MB):** [512, 1G, 5G]
  * **num tests:** [1, 3, 5]

#### IOzone

* **Purpose:** Benchmark IOPS during block device reads/writes.

* **Parameters:**
  * TODO

## Existing Frameworks

While there are many test automation frameworks out there, I haven't found any that deal specifically with benchmarking automation. I found one article that described how to automate one benchmarking tool (fio which we're actually going to use), but it didn't lay out an extensible framework.

By looking at generic automation frameworks and articles about building automated frameworks, I have identified the key component to building a good automation framework: **have light tests, and a complex framework (rather than the other way around)**.

### Resources

[javigon: automating fio tests with python](http://javigon.com/2015/04/28/automating-fio-tests-with-python/)

[simpleprogrammer.com: test automation framework architecture](http://simpleprogrammer.com/2014/04/14/test-automation-framework-architecture/)

## Framework Outline

### General Framework

* Provide environment setup/teardown (multiple environment types)
* Networking between the Server/Client to synchronize start times and environment setups
* Include variable for command and parameters
* Include variable for number of times to execute each unique command
* Include parser variable to parse the command output

### Complex Tools Wrappers

* Provide a specific wrapper for each complex tool (bonnie++, IOZone)

### Run-All Benchmarks Script

* Runs all benchmarking scripts (including complex tools)
* Easily extensible for adding in new benchmarks quickly

## Framework Usage Outline

1. **Setup Environment**

  * Setting up the raio_server and the block device, etc. (Mlnx, DOC-1528) (not necessary for ib_\*_\*, but is for fio, bonnie++, etc.)

2. **Specify Command**

  * "ib_send_bw"

3. **Specify Set of Parameters (iterate over all combinations)**

  * Number of runs = {3}, Timeout (sec) = {10,20,30,60}, Interface = {'tnvme40Gb1'}, Block Size (KB) = {256, 512, 1024}, etc.
  * cpu jobs (-j utilizing cores), 

4. **Capture Output**

  * Store output in a buffer

5. **Teardown Environment**

  * Unmount block device client, stop raio_server, etc. (Mlnx, DOC-1528)

5. **Parse Output**

  * Generate CSV

  * Each test needs to implement output parsing, so that it can be fed to the driver which then can create CSVs from the data and stuff...


## Framework Details

### Example

File: `ib_send_bw.py`

```python
def run():
  framework = Framework()
  
  framework.setupRaioEnv()
  framework.outputParser = parse
  
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

def parse():
   ...
```

File: `run_all.py`, setup as a cron job for overnight runs.

```python
import ib_send_bw

ib_send_bw.run()
...
```

File: `ib_send_bw.csv`

```
Run Number,Command,-t,-bs,|,IOPS
1,ib_send_bw,10,256,|,300
2,ib_send_bw,10,256,|,302
1,ib_send_bw,10,512,|,412
...
```

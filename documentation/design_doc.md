
# Design Document for I/O Test Program

**Project:** NVMe over Fabrics

**Project Sponsor:** Sam Fineberg, HPE

**Authors:** John Gemignani, Eric Litvinsky, Alice Yu

## Goals
* Create a program that will write various amounts of data to a file.
* Calculate checksum on the block of data being written to file.
* Transfer file to target server.
* Read the file and compare calculated checksum block by block.
* Generate metrics for successful file transfer.

## Design
### Name of Command
  * nft (nbdX file test)

### Parameters
  * block size (-b)
  * file size (-f)
  * type of test (-t)
  * nbdX device (-d)
  * semaphore (-s) [Pick between binary and text file]
  * checksum off (-c)

## Testing
  * Allocate a write and read buffer
  * Fill buffer with random numbers [Different depending on writing to binary or text file]
  * Calculate number of blocks to write
  * Calculate checksum of write buffer

## Generating Metrics
  * Total time for opening and closing file for write/read
  * Calculate minimum, maximum, and average for block transfers

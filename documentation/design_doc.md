
# Design Document for I/O Test Program

**Project:** NVMe over Fabrics

**Project Sponsor:** Sam Fineberg, HPE

**Authors:** John Gemignani, Eric Litvinsky, Alice Yu

## Goals
* Create a program that will read and write various amounts of data to a file.
* Calculate a checksum on the block of data being written to a file.
* Write the file to target server.
* Read the file and compare calculated checksum block by block.
* Generate metrics for successful file transfers.

## Design
### Name of Command
  * nft (nbdX file test)

### Parameters (Note: we may need to use long names)
  * help (-h)
  * checksum off (-c)
  * directory (-d)
    * Must specify the directory
  * block size (-b)
    * User must specify size greater than zero in terms of bytes (b), kilabytes (k), megabytes (m), or gigabytes (g).
    * Not case sensitive
  * file size (-f)
    * Same requirements as block size
  * random reads and writes (-r)
    * Sequential reads and writes (default)
  * text file (-t) [Pick between binary and text file]
    * Binary file by default

## Testing
  * Allocate a buffer
  * Fill buffer with random numbers [Different depending on writing to binary or text file]
  * Calculate number of blocks to write
  * Calculate checksum of buffer
  * Write the calculated number of blocks to file

## Generating Metrics
  * Total time for opening and closing file for write/read
  * Calculate minimum, maximum, and average for block transfers


# Design Document for I/O Test Program

**Project:** NVMe over Fabrics

**Project Sponsor:** Sam Fineberg, HPE

**Authors:** John Gemignani, Eric Litvinsky

## Goals
* Create a module that will write various amounts of data to a file.
* Create another module that will verify the contents of the file after it has been transferred. 

## Available Resources

## Design
* Generate random numbers and write them to file
  * Can write to text or binary file
* Generate checksum 
  * Decide on how to do this

## Testing
* Read in the generated file and verify the checksum

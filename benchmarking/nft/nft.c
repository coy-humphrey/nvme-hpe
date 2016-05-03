/********************************************************************* 
 * Alice Yu (aljyu@ucsc.edu)
 * Eric Litvinsky (elitvins@ucsc.edu)
 * John Gemignani (jgemigna@ucsc.edu)
 * 
 * CMPS117: Senior Design II
 * Teacher: Linda Werner
 * TA:      Daniel Fava
 * Sponsor: Samuel Fineberg (HPE)
 * Spring 2016
 *
 * 
 *
 ********************************************************************/

#include <unistd.h>                    //getopt
#include <libgen.h>                    //basename
#include <string.h>                    //strtok_r
#include <errno.h>                     //error stuff
#include <stdio.h>                     //*printf
#include <stdlib.h>                    //exit
#include <ctype.h>                     //toupper
#include <stdint.h>		       //uint64_t
#include <sys/types.h>		       //file opening
#include <sys/stat.h>		       //file opening
#include <fcntl.h>		       //file opening
#include <sys/param.h>		       //crc32 (table version)
#include <dirent.h>		       //opendir()

// global status defines
#define SUCCESS 0
#define FAILURE 1 
#define FALSE 0
#define TRUE 1
#define ASCII_LOW 0x20
#define ASCII_HIGH 0x7E
#define BINARY_LOW 0x00
#define BINARY_HIGH 0xFF
#define BINARY 0
#define TEXT 1
#define SEQUENTIAL 0
#define RANDOM 1


static uint32_t crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

/* void usage()
 * Print usage and exit with a failure
 */
void usage(){
   fprintf(stdout, "Invalid command \n");
   fprintf(stdout, "Usage: \n");
   fprintf(stdout, "       nft -h \n");
   exit(FAILURE);
}

/* void help()
 * Print the available commands and how to use them.
 */
void help() {
  fprintf(stdout, "-d: Specify directory path of where you want to save the file. \n");
  fprintf(stdout, "-b: Specify block size greater than 0 followed by B, K, M, or G to create a buffer of a size in bytes, kilabytes, megabytes, or gigabytes respestively. Not case sensative. \n");
  fprintf(stdout, "-f: Specify file size greater than 0 followed by B, K, M, or G to create a buffer of a size in bytes, kilabytes, megabytes, or gigabytes respestively. Not case sensative. \n");
  exit(SUCCESS);
}

/* void checkDir(char* dirPath)
 * Checks to see if directory exists.
 */
void checkDir(char* dirPath) {
  DIR* dir = opendir(dirPath);

  if(dir) { //directory exists
    closedir(dir);
    return;
  }
  else if(ENOENT == errno) { //directory does not exist
    fprintf(stdout, "Directory does not exist\n");
    exit(FAILURE);
  }
  else if(EACCES == errno) { //permission denied to directory
    fprintf(stdout, "Permission denied to directory\n");
    exit(FAILURE);
  }
  else { //Couldn't open directory for some other reason
    fprintf(stdout, "Unable to open directory for some other reason\n");
    exit(FAILURE);
  }
}

/* int write_all(int fd, char *buffer, uint64_t buffersize)
 * Allows for writing to files using buffer size larger than SSIZE_MAX (2G)
 */
int write_all (int fd, char *buffer, uint64_t buffersize)
{
  uint64_t totalWrit = 0;
  while (totalWrit < buffersize)
  {
    uint64_t toWrite = SSIZE_MAX < (buffersize-totalWrit) ? SSIZE_MAX : buffersize - totalWrit;
    int rc = write(fd, buffer + totalWrit, toWrite);
    if (rc < 0)
    {
      perror("nft");
      return 1;
    }
    totalWrit += rc;
  }
  return 0;
}

/* uint32_t checkSum32(uint32_t crc, const void *buf, size_t size)
 * Calculate the checksum of the buffer contents.
 * Returns the checksum.
 */
uint32_t checkSum32(uint32_t crc, const void *buf, size_t size)
{
  const uint8_t *p;

  p = buf;
  crc = crc ^ ~0U;

  while (size--)
    crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

  return crc ^ ~0U;
}

/* uint32_t readCheckSum(uint64_t bufferSize, int type, char* dirPath)
 * Reads in a block of data and returns the checksum on it.
 * It is expected that the computed check sum of the block used to
 * write to a file matches the check sum generated from reading in
 * that same block from the file.
 *
 * The contents of the buffer continue to be written to the file
 * according to the given size. Therefore, only necessary to verify
 * that both buffer check sums match.
 */
uint32_t readCheckSum(uint64_t bufferSize, int type, char* dirPath) {
  int openFile = 0;
  int fileRead = 0;
  uint64_t count = 0;
  uint32_t checkSum = 0;
  
  char* path;
  char* textFile = "/test.txt";
  char* binFile = "/test.bin";

  char* buffer = malloc(bufferSize);

  if(type == TEXT) {
    asprintf(&path, "%s%s", dirPath, textFile);
    openFile = open(path, O_RDONLY);
  }
  else {
    asprintf(&path, "%s%s", dirPath, binFile);
    openFile = open(path, O_RDONLY);
  }  

  if (openFile == -1) {
    fprintf(stdout, "Unable to open file.\n");
    return 0;
  }

  fileRead = read(openFile, buffer, bufferSize);
  checkSum = checkSum32(0, buffer, bufferSize);
 
  free(buffer);
  free(path);
  close(openFile);

  return checkSum;
}

/* int fillFile(char* buffer, int bufferSize. int fileSize, int type)
 * Fill binary or text file with data from buffer.
 * Returns a 0 if file cannot be opened and 1 if successful.
 */
int fillFile(char* buffer, uint64_t bufferSize, uint64_t fileSize, int type, char* dirPath) {
  int openFile = 0;
  uint64_t count = 0;

  char* path;
  char* textFile = "/test.txt";
  char* binFile = "/test.bin";

  if(type == TEXT) {
    asprintf(&path, "%s%s", dirPath, textFile);
    openFile = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
  }
  else {
    asprintf(&path, "%s%s", dirPath, binFile);
    openFile = open(path, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
  }

  fprintf(stdout, "path to directory: %s\n", dirPath);
  fprintf(stdout, "path to file: %s\n", path);

  if (openFile == -1) {
    fprintf(stdout, "Unable to create file.\n");
    return 0;
  }

  for(count = 0; count < (fileSize / bufferSize); count++) {
    write_all(openFile, buffer, bufferSize);
  }
  
  if((fileSize % bufferSize) != 0)
    write_all(openFile, buffer, (fileSize % bufferSize));

  close(openFile);
  free(path);

  return 1;
}

/* uint64_t convertStringToSize(char* size)
 * Converts the parsed file size or buffer size from
 * the command line.
 * Returns the size as an integer in bytes.
 */
uint64_t convertStringToSize(char* size) {
  char * ptr = NULL;
  uint64_t value = strtol(size, &ptr, 10);
  if (strlen(ptr) != 1){
    return 0;
  }
  
  switch (toupper(*ptr)){
    case 'B':
      return value;
    case 'K':
      return 1024 * value;
    case 'M':
      return 1024*1024*value;
    case 'G':
      return 1024*1024*1024*value;  
    default:
      return 0;
  }
}

/* char* createRandFill(int bufferSize, int type)
 * Creates a buffer specificed by user and fills it
 * with random values depending on file type.
 * Returns the buffer.
 */
char* createRandFill(uint64_t bufferSize, int type) {
  int randVal;
  uint64_t i;
  char* buffer = malloc(bufferSize);

  if (bufferSize == 0) {
    fprintf(stderr, "Failed to allocate memory or bufferSize is 0\n");
    free(buffer);
    exit(FAILURE);
  }

 // printf("buffer size: %lu\n", bufferSize);
  // default for type is a binary file
  for (i = 0; i < bufferSize; i++) {
    if (type == BINARY) {
      randVal = (random() & BINARY_HIGH);
    }
    else {
      randVal = ASCII_LOW + (random() % (ASCII_HIGH - ASCII_LOW));
    }
    buffer[i] = randVal;
  }

  return buffer;
}

/* int main(int argc, char * argv[])
 * Main entry point to program nft.
 *
 * All error output goes to stderr
 *
 */
int main(int argc, char * argv[]){
   // set up some variables and flags for getopt
   int currentOption;
   char* programName;
   char* buff;

   int checkSumFlag = TRUE; 
   int debugFlag = FALSE;
   int fileTypeFlag = BINARY;
   int readWriteFlag = SEQUENTIAL;
   uint64_t buffersize = 0;
   uint64_t filesize = 0;
   char* path = NULL;
   uint32_t writeCheckSum;

   // set program name
   programName = basename(argv[0]);

   // loop through command line options. Set the appropriate flags
   // as needed. On exit of the loop, the optind will point to the
   // file passed, if there was one passed.
   //while ((currentOption = getopt(argc, argv, "ly@:D:"))!= -1){
   while ((currentOption = getopt(argc, argv, "hcrtb:f:d:"))!= -1){
      switch(currentOption){
         case 'h':
            help();
            break;
         case 'c':
            fprintf(stdout, "option -c passed \n");
            checkSumFlag = FALSE;
            break;
	 case 'r':
	    fprintf(stdout, "option -r passed \n");
	    readWriteFlag = RANDOM;
	    break;
         case 't':
            fprintf(stdout, "option -t passed \n");
            fileTypeFlag = TEXT;
            break;

         case 'b':
            fprintf(stdout, "option -b passed with flag [%s]\n", optarg);
            fprintf(stdout, "buffer size: %lu\n", convertStringToSize(optarg));
	    buffersize = convertStringToSize(optarg);
            break;
         case 'f':
            fprintf(stdout, "option -f passed with flag [%s]\n", optarg);
	    fprintf(stdout, "file size: %lu\n", convertStringToSize(optarg));
            filesize = convertStringToSize(optarg);
            break;
         case 'd':
            fprintf(stdout, "option -d passed with flag [%s]\n", optarg);
	    fprintf(stdout, "file path: %s\n", optarg);
	    path = optarg;
            break;

         case ':':
            fprintf(stdout, "option case tripped [:]\n");
            break;
         case '?':
            fprintf(stdout, "option case tripped [?]\n");
            usage();
            break;
         default:
            fprintf(stdout, "option case tripped [default]\n");
            break;
      }
   }

/*
   // simple usage check, verify there is at least a file passed.
   // if not, exit on failure.
   if (argc == optind){
      usage();
   }
*/

   if(!buffersize || !filesize || (path == NULL))
     usage();

   checkDir(path);

   // Testing randFill()
   buff = createRandFill(buffersize, fileTypeFlag);

   if(checkSumFlag) {
     writeCheckSum = checkSum32(0, buff, buffersize);
     printf("write checksum value: %lu\n", writeCheckSum);
   }

   int valid = fillFile(buff, buffersize, filesize, fileTypeFlag, path);
   printf("valid: %d\n", valid);
   free(buff);

   uint32_t readchecksum = readCheckSum(buffersize, fileTypeFlag, path);
   printf("read checksum value: %lu\n", readchecksum);

   // exit with success
   return SUCCESS;
}

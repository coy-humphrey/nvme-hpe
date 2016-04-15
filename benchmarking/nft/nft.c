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

/* void usage()
 * Print usage and exit with a failure
 */
void usage(){
   fprintf(stdout, "Usage: \n");
   fprintf(stdout, "       nft -h \n");
   exit(FAILURE);
}

/* int fillFile(char* buffer, int bufferSize. int fileSize, int type)
 * Fill binary or text file with data from buffer.
 * Returns a 0 if file cannot be opened and 1 if successful.
 */
int fillFile(char* buffer, int bufferSize, int fileSize, int type) {
  int openFile = 0;
  int count = 0;

  if(type == TEXT) {
    openFile = open("test.txt", O_CREAT | O_WRONLY);
  }
  else {
    openFile = open("test.bin", O_CREAT | O_WRONLY);
  }

  if (openFile == -1) {
    fprintf(stdout, "Unable to create file.");
    return 0;
  }

  for(count = 0; count < (fileSize / bufferSize); count++) {
    write(openFile, buffer, bufferSize);
  }

  if((fileSize % bufferSize) != 0)
    write(openFile, buffer, (fileSize % bufferSize));

  close(openFile);
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

/* int checkSum(char* buffer, int bufferSize)
 * Calculate the checksum of the buffer contents.
 * Returns the checksum.
 */
int checkSum(char* buffer, int bufferSize) {
  int i;
  int checksum = 0;
  for(i = 0; i < bufferSize; i++) {
    checksum ^= buffer[i];
  }

  return checksum;
}

/* char* createRandFill(int bufferSize, int type)
 * Creates a buffer specificed by user and fills it
 * with random values depending on file type.
 * Returns the buffer.
 */
char* createRandFill(int bufferSize, int type) {
  int randVal, i;
  char* buffer = malloc(bufferSize);
  if (buffer == NULL) {
    fprintf(stderr, "Failed to allocate memory or bufferSize is 0");
    return NULL;
  }
  // default for type is a binary file
  for (i = 0; i < bufferSize; i++) {
    if (type == BINARY) {
      randVal = (random() & BINARY_HIGH);
    }
    else {
      randVal = ASCII_LOW + (random() % (ASCII_HIGH - ASCII_LOW));
    }
    buffer[i] = randVal;
    //printf("%c", buffer[i]);
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
   int verboseFlag = FALSE;
   int debugFlag = FALSE;
   int fileTypeFlag = BINARY;
   int buffersize = 0;
   int filesize = 0;
   char* device = NULL;

   // set program name
   programName = basename(argv[0]);

   // loop through command line options. Set the appropriate flags
   // as needed. On exit of the loop, the optind will point to the
   // file passed, if there was one passed.
   //while ((currentOption = getopt(argc, argv, "ly@:D:"))!= -1){
   while ((currentOption = getopt(argc, argv, "hcvds:b:f:t:n:"))!= -1){
      switch(currentOption){
         case 'h':
            usage();
            break;
         case 'c':
            fprintf(stdout, "option -c passed \n");
            checkSumFlag = FALSE;
            break;
         case 'v':
            fprintf(stdout, "option -v passed \n");
            verboseFlag = TRUE;
            break;
         case 'd':
            fprintf(stdout, "option -d passed \n");
            debugFlag = TRUE;
            break;
         case 's':
            fprintf(stdout, "option -s passed with flag [%s]\n");
            fileTypeFlag = TEXT;
            break;

         case 'b':
            fprintf(stdout, "option -b passed with flag [%s]\n", optarg);
            fprintf(stdout, "%lu\n", convertStringToSize(optarg));
	    buffersize = convertStringToSize(optarg);
            break;
         case 'f':
            fprintf(stdout, "option -f passed with flag [%s]\n", optarg);
            filesize = convertStringToSize(optarg);
            break;
         case 't':
            fprintf(stdout, "option -t passed with flag [%s]\n", optarg);
            break;
         case 'n':
            fprintf(stdout, "option -n passed with flag [%s]\n", optarg);
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

   // Testing randFill()
   buff = createRandFill(256, TEXT);
   printf("[%s]\n", buff);
   int checksum = checkSum(buff, 256);
   printf("checksum value: %d\n", checksum);
   int valid = fillFile(buff, buffersize, filesize, TEXT);
   printf("valid: %d\n", valid);
   free(buff);


   // exit with success
   return SUCCESS;
}

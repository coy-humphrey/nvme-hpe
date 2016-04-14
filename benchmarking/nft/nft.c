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
   int bufferSize = 0;
   int fileSize = 0;
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
            break;
         case 'f':
            fprintf(stdout, "option -f passed with flag [%s]\n", optarg);
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
   free(buff);

   buff = createRandFill(256, TEXT);
   printf("[%s]\n", buff);
   checksum = checkSum(buff, 256);
   printf("checksum value: %d\n", checksum);
   free(buff);

   // exit with success
   return SUCCESS;
}

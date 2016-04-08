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

/* 
 *
 *
 */
void randFill(char * buffer, int bufferSize, int type) {
  int randVal, i;
  buffer = malloc(bufferSize);
  if (buffer == NULL) {
    fprintf(stderr, "Failed to allocate memory or bufferSize is 0");
    exit(FAILURE);
  }
  // default for type is a binary file
  for (i = 0; i < bufferSize; i++) {
    if (type) {
      randVal = (random() & BINARY_HIGH);
    }
    else {
      randVal = ASCII_LOW + (random() % (ASCII_HIGH - ASCII_LOW));
    }
    buffer[i] = randVal;
  }
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
   char * programName;

   int checkSumFlag = TRUE; 
   int verboseFlag = FALSE;
   int debugFlag = FALSE;
   int fileTypeFlag = BINARY;

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

   // simple usage check, verify there is at least a file passed.
   // if not, exit on failure.
   if (argc == optind){
      usage();
   }

   // exit with success
   return SUCCESS;
}

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

/* void usage()
 * Print usage and exit with a failure
 */
void usage(){
   fprintf(stdout, "Usage: \n");
   fprintf(stdout, "       nft -h \n");
   exit(FAILURE);
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

   // set program name
   programName = basename(argv[0]);

   // loop through command line options. Set the appropriate flags
   // as needed. On exit of the loop, the optind will point to the
   // file passed, if there was one passed.
   //while ((currentOption = getopt(argc, argv, "ly@:D:"))!= -1){
   while ((currentOption = getopt(argc, argv, "hcvdb:f:t:n:s:"))!= -1){
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
         case 's':
            fprintf(stdout, "option -s passed with flag [%s]\n", optarg);
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

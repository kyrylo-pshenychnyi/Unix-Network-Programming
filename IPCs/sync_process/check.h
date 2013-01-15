#ifndef _CHECK_H
#define _CHECK_H
/* headers used by a majority of the example program */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

/* Simple function to check the return code and exit the program
   if the function call failed
   */
static void checkResults(char *string, int rc) {
  if (rc) {
    printf("Error on : %s, rc=%d",
           string, rc);
    exit(EXIT_FAILURE);
  }
  return;
}

#endif



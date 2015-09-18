#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <errno.h>

#include "patch.h"

int main(int argc, char** argv) {
  argc--; argv++;

  if(argc < 2) {
    fprintf(stderr, "Usage: fastboot <infile> <outfile>\n");
    return EXIT_FAILURE;
  }

  char *infile = argv[0];
  char *outfile = argv[1];

  uint8_t kernal[8192];
  
  FILE* in;
  FILE* out;

  int i;

  if((in = fopen(infile, "rb")) == NULL) {
    perror(infile);
    return EXIT_FAILURE;
  };
  
  fread(kernal, sizeof(uint8_t), sizeof(kernal), in);
  fclose(in);

  for(i=0; i<sizeof(code); i++) {
    kernal[0x1d6c+i] = code[i];
  }

  if((out = fopen(outfile, "wb")) == NULL) {
    perror(outfile);
    return EXIT_FAILURE;
  };

  fwrite(kernal, sizeof(uint8_t), sizeof(kernal), out);
  fclose(out);

  return EXIT_SUCCESS;
}

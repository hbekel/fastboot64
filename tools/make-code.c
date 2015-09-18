#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {

  char *filename = argv[1];
  int size, i;
  FILE* f;

#if __MINGW32__  
  struct __stat64 st;  
  __stat64(filename, &st);
#else
  struct stat st;
    stat(filename, &st);
#endif
  size = st.st_size;

 
  if((f = fopen(filename, "rb")) == NULL) {
    fprintf(stderr, "%s: error opening %s\n", argv[0], filename);
    return EXIT_FAILURE;
  }

  printf("unsigned char code[%d] = {\n", size);
  for(i=0; i<size; i++) {
    printf("%d, ", fgetc(f));
  }
  printf("};\n\n");

  fclose(f);
  
  return EXIT_SUCCESS;
  
}

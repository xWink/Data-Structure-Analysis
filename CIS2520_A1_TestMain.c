#include "ds_memory.c"

int main(){

  char* filename = "test.bin";
  printf("%d\n", ds_create(filename, 0));
  return 0;
}

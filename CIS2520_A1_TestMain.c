#include "ds_memory.c"

int main(){

  char* filename = "test.bin";
  ds_create(filename, 1234);
  ds_test_init();
  return 0;
}

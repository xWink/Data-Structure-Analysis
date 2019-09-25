#include "ds_memory.h"
#include "ds_array.h"

int main(int argc, char **argv) {
  /*
  ds_create("array.bin", 1234);
  ds_create_array();
  ds_init_array();
  ds_finish();
  ds_test_init();
  */

  int value;
  long index;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s value index\n", argv[0]);
    return -1;
  }

  value = atoi(argv[1]);
  index = atoi(argv[2]);

  /*ds_create_array();*/
  ds_init_array();
  ds_insert(value, index);
  ds_test_init();
  ds_finish_array();
  return 0;
}

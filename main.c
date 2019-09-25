#include "ds_memory.h"
#include "ds_array.h"

int main(int argc, char **argv) {

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
  return 0;
}

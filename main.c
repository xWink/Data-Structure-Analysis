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

  /*ds_create("array.bin", 2048);
  ds_create_array();*/
  ds_init_array();
  /*ds_insert(value, index);
  ds_read_elements("textfile");
  ds_delete(8);
  ds_swap(9, 0);
  ds_insert(value, index);*/
  printf("find value: %ld\n", ds_find(0));
  show_array();
  ds_finish_array();
  return 0;
}

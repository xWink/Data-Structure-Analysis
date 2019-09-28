#include "ds_memory.h"
#include "ds_list.h"

int main(int argc, char **argv) {

  /*ds_create("list.bin", 2048);
  ds_create_list();*/

  printf("init: %d\n",ds_init_list());
  printf("find: %ld\n", ds_find(33));
  /*ds_read_elements("textfile");*/
  /*printf("swap: %d\n", ds_swap(0,1));*/

  /*printf("replace: %d\n",ds_replace(111, 3));*/
/*  printf("insert: %d\n",ds_insert(10,0));
  printf("insert: %d\n",ds_insert(1,1));
  printf("insert: %d\n",ds_insert(1,2));
  printf("insert: %d\n",ds_insert(-1,0));
  printf("insert: %d\n",ds_insert(-3,0));*/
  show_list();
  printf("finish: %d\n",ds_finish_list());


/*  int value;
  long index;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s value index\n", argv[0]);
    return -1;
  }

  value = atoi(argv[1]);
  index = atoi(argv[2]);

  ds_create("array.bin", 2048);
  ds_create_array();
  ds_init_array();
  ds_insert(value, index);
  ds_read_elements("textfile");
  ds_delete(8);
  ds_swap(9, 0);
  ds_insert(value, index);
  printf("find value: %ld\n", ds_find(0));
  show_array();
  ds_finish_array();*/


  return 0;
}

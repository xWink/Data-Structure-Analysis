#include "ds_memory.h"
#include "ds_array.h"
#include <time.h>

int main(int argc, char **argv) {

  int i, j;
  srand(time(0));
  for (j = 1; j <= 10; j++) {
    printf("deleteme:");
    ds_create("array.bin", 2048);
    ds_create_array();
    ds_init_array();
    for (i = 0; i < (j*10); i++) {
      ds_insert(i+1,i);
    }
    ds_finish_array();
    for (i = 0; i < 30; i++) {
      ds_init_array();
      ds_swap((rand() % (j*10)), (rand() % (j*10)));
      printf("%d, ", j*10);
      ds_finish_array();
    }
  }

  /*ds_read_elements("textfile");*/
  /*printf("swap: %d\n", ds_swap(0,1));*/

  /*printf("replace: %d\n",ds_replace(111, 3));*/
/*  printf("insert: %d\n",ds_insert(10,0));
  printf("insert: %d\n",ds_insert(1,1));
  printf("insert: %d\n",ds_insert(1,2));
  printf("insert: %d\n",ds_insert(-1,0));
  printf("insert: %d\n",ds_insert(-3,0));*/
  /*show_list();
  printf("finish: %d\n",ds_finish_list());*/


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

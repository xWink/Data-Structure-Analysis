#include "ds_memory.h"
#include "ds_list.h"

void ds_create_list() {

    long value = -1;
    long start;

    ds_init("list.bin");
    start = ds_malloc(sizeof(value));
    ds_write(start, &value, sizeof(value));
    ds_finish();
}


int ds_init_list() {

  return ds_init("list.bin");
}


int ds_replace(int value, long index);


int ds_insert(int value, long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct new;
  long previousLoc = 0;
  int i;

  ds_read(&previous.next, 0, sizeof(previous.next));

  for (i = index; i > 0; i--) {
    if (previous.next == -1) {
      return -1;
    }
    previousLoc = previous.next;
    ds_read(&previous, previous.next, sizeof(previous));
  }

  new.item = value;
  new.next = previous.next;

  previous.next = ds_malloc(sizeof(new));
  ds_write(previous.next, &new, sizeof(new));
  if (index == 0) {
    ds_write(0, &previous.next, sizeof(previous.next));
  }

  if (previousLoc == 0 && new.next != -1) {
    return -2;
  }

  ds_write(previousLoc, &previous, sizeof(previous));

  return 0;
}


int ds_delete(long index);
int ds_swap(long index1, long index2);
long ds_find(int target);
int ds_read_elements(char *filename);

void show_list() {

  struct ds_list_item_struct li;
  long loc;
  int i;

  ds_test_init();
  ds_read(&loc, 0, sizeof(loc));

  for (i = 0; i < 10; i++) {
    ds_read(&li, loc, sizeof(li));
    if ((loc = li.next) != -1) {
      printf("Next: %ld, Item: %d\n", li.next, li.item);
    }
  }
}


int ds_finish_list() {

  return ds_finish();
}

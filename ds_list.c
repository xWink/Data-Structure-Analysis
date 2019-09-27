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


int ds_replace(int value, long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct new;
  int i;

  ds_read(&(previous.next), 0, sizeof(previous.next));

  for (i = index; i > 0; i--) {
    if (previous.next == -1) {
      return -1;
    }
    ds_read(&previous, previous.next, sizeof(previous));
  }

  ds_read(&new, previous.next, sizeof(new));
  new.item = value;

  if (ds_write(previous.next, &new, sizeof(new)) == -1) {
    return 2;
  }
  return 0;
}


int ds_insert(int value, long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct new;
  long previousLoc = 0;
  int i;

  ds_read(&(previous.next), 0, sizeof(previous.next));

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

  if (previousLoc == 0) {
    ds_write(previousLoc, &(previous.next), sizeof(previous.next));
  } else {
    ds_write(previousLoc, &previous, sizeof(previous));
  }

  return 0;
}


int ds_delete(long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct target;
  long previousLoc;
  int i;

  ds_read(&(previous.next), 0, sizeof(previous.next));

  for (i = index; i > 0; i--) {
    if (previous.next == -1) {
      return -1;
    }
    previousLoc = previous.next;
    ds_read(&previous, previous.next, sizeof(previous));
  }

  ds_read(&target, previous.next, sizeof(target));
  ds_free(previous.next);
  previous.next = target.next;

  if (ds_write(previousLoc, &previous, sizeof(previous)) == -1) {
    return 2;
  }
  return 0;
}


int ds_swap(long index1, long index2);
long ds_find(int target);


/*ASSUMING THIS IS THE CORRECT ORDER FOR INSERT*/
int ds_read_elements(char *filename) {

  int val;
  FILE *fp = fopen(filename, "r");

  while (fscanf(fp, "%d", &val) != EOF) {
    if (ds_insert(val, 0) != 0) {
      return 1;
    }
  }

  return 0;
}

void show_list() {

  struct ds_list_item_struct li;
  long loc;

  ds_test_init();
  ds_read(&loc, 0, sizeof(loc));

  do {
    ds_read(&li, loc, sizeof(li));
    printf("Next: %ld, Item: %d\n", li.next, li.item);
    loc = li.next;
  } while (loc != -1);
}


int ds_finish_list() {

  return ds_finish();
}

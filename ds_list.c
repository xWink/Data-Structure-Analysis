#include "ds_memory.h"
#include "ds_list.h"

int ds_create_list() {

    long value = -1;
    long start;

    if (ds_init("list.bin") != 0) {
      return 1;
    }

    if ((start = ds_malloc(sizeof(value))) == -1) {
      return 2;
    }

    if (ds_write(start, &value, sizeof(value)) == -1) {
      return 3;
    }

    if (ds_finish() != 0) {
      return 4;
    }

    return 0;
}


int ds_init_list() {

  return ds_init("list.bin");
}


int ds_replace(int value, long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct new;
  int i;

  if (ds_read(&(previous.next), 0, sizeof(previous.next)) == NULL) {
    return 1;
  }

  for (i = index; i > 0; i--) {
    if (previous.next == -1) {
      return 2;
    }

    if (ds_read(&previous, previous.next, sizeof(previous)) == NULL) {
      return 3;
    }
  }

  if (ds_read(&new, previous.next, sizeof(new)) == NULL) {
    return 4;
  }

  new.item = value;

  if (ds_write(previous.next, &new, sizeof(new)) == -1) {
    return 5;
  }

  return 0;
}


int ds_insert(int value, long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct new;
  long previousLoc = 0;
  int i;

  if (index < 0) {
    return 1;
  }

  if (ds_read(&(previous.next), 0, sizeof(previous.next)) == NULL) {
    return 2;
  }

  for (i = index; i > 0; i--) {
    if (previous.next == -1) {
      return 3;
    }
    previousLoc = previous.next;
    if (ds_read(&previous, previous.next, sizeof(previous)) == NULL) {
      return 4;
    }
  }

  new.item = value;
  new.next = previous.next;

  if ((previous.next = ds_malloc(sizeof(new))) == -1) {
    return 5;
  }

  if (ds_write(previous.next, &new, sizeof(new)) == -1) {
    return 6;
  }

  if (previousLoc == 0) {
    if (ds_write(previousLoc, &(previous.next), sizeof(previous.next)) == -1) {
      return 7;
    }
  } else {
    if (ds_write(previousLoc, &previous, sizeof(previous)) == -1) {
      return 8;
    }
  }

  return 0;
}


int ds_delete(long index) {

  struct ds_list_item_struct previous;
  struct ds_list_item_struct target;
  long previousLoc;
  int i;

  if (index < 0) {
    return 1;
  }

  if (ds_read(&(previous.next), 0, sizeof(previous.next)) == NULL) {
    return 2;
  }

  if (index == 0) {
    if (ds_read(&target, previous.next, sizeof(target)) == NULL) {
      return 3;
    }

    ds_free(previous.next);

    if (ds_write(0, &target.next, sizeof(target.next)) == -1) {
      return 4;
    }

    return 0;
  }

  for (i = index; i > 0; i--) {
    if (previous.next == -1) {
      return 5;
    }
    previousLoc = previous.next;
    if (ds_read(&previous, previous.next, sizeof(previous)) == NULL) {
      return 6;
    }
  }

  if (ds_read(&target, previous.next, sizeof(target)) == NULL) {
    return 7;
  }

  ds_free(previous.next);

  previous.next = target.next;

  if (ds_write(previousLoc, &previous, sizeof(previous)) == -1) {
    return 8;
  }
  
  return 0;
}


int ds_swap(long index1, long index2);
long ds_find(int target);


/*TODO: SAY ASSUMING THIS IS THE CORRECT ORDER FOR INSERT*/
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

/**
* Author: Shawn Kaplan (0966499)
* Date: September 29, 2019
*
* An assumption is made for the specific order in which
* ds_insert places new nodes and for the order in which
* ds_read_elements reads new nodes into the file
*/

#include "ds_memory.h"
#include "ds_list.h"

void ds_create_list() {

    long value = -1;
    long start;

    if (ds_init("list.bin") != 0) {
      return;
    }

    if ((start = ds_malloc(sizeof(value))) == -1) {
      return;
    }

    if (ds_write(start, &value, sizeof(value)) == -1) {
      return;
    }

    if (ds_finish() != 0) {
      return;
    }

    return;
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
  }
  
  else {
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


int ds_swap(long index1, long index2) {

  struct ds_list_item_struct first;
  struct ds_list_item_struct second;
  long firstLoc = 0;
  long secondLoc = 0;
  long temp;
  int i;

  if (index1 < 0 || index2 < 0) {
    return 1;
  }

  if (index1 == index2) {
    return 0;
  }

  if (index1 > index2) {
    int holder = index1;
    index1 = index2;
    index2 = holder;
  }

  if (ds_read(&(first.next), 0, sizeof(first.next)) == NULL) {
    return 2;
  }

  /*Find index1's address and save the struct to previous*/
  for (i = index1; i >= 0; i--) {
    if (first.next == -1) {
      return 3;
    }
	
    firstLoc = first.next;
	
    if (ds_read(&first, first.next, sizeof(first)) == NULL) {
      return 4;
    }
  }

  second.next = first.next;

  /*Find index2's address, save the struct to new*/
  for (i = index2 - index1; i > 0; i--) {
    if (second.next == -1) {
      return 6;
    }
	
    secondLoc = second.next;
	
    if (ds_read(&second, second.next, sizeof(second)) == NULL) {
      return 7;
    }
  }

  /*Swap next values*/
  temp = first.next;
  first.next = second.next;
  second.next = temp;

  if (ds_write(firstLoc, &second, sizeof(second)) == -1) {
    return 8;
  }

  if (ds_write(secondLoc, &first, sizeof(first)) == -1) {
    return 9;
  }

  return 0;
}


long ds_find(int target) {

  struct ds_list_item_struct targetStruct;
  long targetLoc;

  if (target < 0) {
    return -1;
  }

  if (ds_read(&(targetStruct.next), 0, sizeof(targetStruct.next)) == NULL) {
    return -1;
  }

  while (targetStruct.next != -1) {
    targetLoc = targetStruct.next;
	
    if (ds_read(&targetStruct, targetStruct.next, sizeof(targetStruct)) == NULL) {
      return -1;
    }
	
    if (targetStruct.item == target) {
      return targetLoc;
    }
  }

  return -1;
}


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


int ds_finish_list() {

  return ds_finish();
}

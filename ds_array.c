#include "ds_memory.h"
#include "ds_array.h"

long elements;

int ds_create_array() {
  long start;

  if (ds_init("array.bin") != 0) {
    return 1;
  }
  elements = 0;
  if ((start = ds_malloc(sizeof(long))) == -1) {
    return 2;
  }
  if (ds_write(start, &elements, sizeof(elements)) == -1) {
    return 3;
  }
  if (ds_malloc(sizeof(int)*MAX_ELEMENTS) == -1) {
    return 4;
  }
  if (ds_finish() != 0) {
    return 5;
  }
  return 0;
}

int ds_init_array() {

  if (ds_init("array.bin") != 0) {
    return 1;
  }
  if (ds_read(&elements, 0, sizeof(long)) == NULL) {
    return 2;
  }
  return 0;
}

int ds_replace(int value, long index) {
  return 0;
}

int ds_insert(int value, long index) {
  int old;
  int new;
  int i;

  if (index > MAX_ELEMENTS) {
    return 1;
  }
  
  new = value;

  for (i = index; i <= elements; i++) {
    if (ds_read(&old, i * sizeof(int) + sizeof(elements), sizeof(int)) == NULL) {
      return 2;
    }
    if (ds_write(i * sizeof(int) + sizeof(elements), &new, sizeof(int)) == -1) {
      return 3;
    }
    new = old;
  }

  elements++;
  return 0;
}
int ds_delete() {
  return 0;
}
int ds_swap() {
  return 0;
}
long ds_find(int target) {
  return 0;
}
int ds_read_elements(char *filename) {
  return 0;
}

void create_array() {
  ds_create("array.bin", 2048);
  ds_create_array();
}

void show_array() {
  ds_test_init();
  printf("elements = %ld\n", elements);
}

int ds_finish_array() {
  if (ds_write(0, &elements, sizeof(elements)) == -1) {
    return 1;
  }
  if (ds_finish() != 0) {
    return 2;
  }
  return 0;
}

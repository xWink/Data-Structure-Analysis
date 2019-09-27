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

  if (index >= elements) {
    return 1;
  }

  if (ds_write(index * sizeof(int) + sizeof(elements), &value, sizeof(int)) == -1) {
    return 2;
  }
  return 0;
}


int ds_insert(int value, long index) {

  int old;
  int new;
  int i;

  if (index < 0 || index > elements) {
    return 1;
  }

  if (elements == MAX_ELEMENTS) {
    return 2;
  }

  new = value;

  for (i = index; i <= elements; i++) {
    if (ds_read(&old, i * sizeof(int) + sizeof(elements), sizeof(int)) == NULL) {
      return 2;
    }
    if (ds_write(i * sizeof(int) + sizeof(elements), &new, sizeof(int)) == -1) {
      return 3;
    }
    printf("Element %d: %d\n", i, new);
    new = old;
  }

  elements++;
  return 0;
}

int ds_delete(long index) {
  int old;
  int new;
  int i;

  if (index < 0 || index >= elements) {
    return 1;
  }

  if (ds_read(&old, (elements-1) * sizeof(int) + sizeof(elements), sizeof(int)) == NULL) {
    return 2;
  }

  for (i = elements-1; i >= index; i--) {
    if (ds_read(&new, i * sizeof(int) + sizeof(elements), sizeof(int)) == NULL) {
      return 3;
    }
    if (ds_write(i * sizeof(int) + sizeof(elements), &old, sizeof(int)) == -1) {
      return 4;
    }
    printf("Element %d: %d\n", i, new);
    old = new;
  }

  elements--;
  return 0;
}

int ds_swap(long index1, long index2) {

  int var1;
  int var2;

  if (index1 >= elements || index1 < 0
    || index2 >= elements || index2 < 0) {

    return 1;
  }

  ds_read(&var1, index1 * sizeof(int) + sizeof(elements), sizeof(int));
  ds_read(&var2, index2 * sizeof(int) + sizeof(elements), sizeof(int));

  ds_write(index2 * sizeof(int) + sizeof(elements), &var1, sizeof(int));
  ds_write(index1 * sizeof(int) + sizeof(elements), &var2, sizeof(int));

  return 0;
}


long ds_find(int target) {

  long i;
  int value;

  for (i = sizeof(elements); i < elements; i = i + sizeof(int)) {
    ds_read(&value, i, sizeof(int));
    if (i == target) {
      return i;
    }
  }

  return -1;
}

/*ASSUMING THIS IS THE CORRECT ORDER AND LOCATION FOR INSERT*/
int ds_read_elements(char *filename) {

  int val;
  FILE *fp = fopen(filename, "r");

  while (fscanf(fp, "%d", &val) != EOF) {
    if (ds_insert(val, elements) != 0) {
      return 1;
    }
  }

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

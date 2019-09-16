#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char* filename, long size) {

  int i;

  /* Create file*/
  if ((ds_file.fp = fopen(filename, "wb")) == NULL) {
    return 1;
  }

  /* Populate block array*/
  ds_file.block[0].start = 0;
  ds_file.block[0].length = size;
  ds_file.block[0].alloced = 0;

  for (i = 1; i < MAX_BLOCKS; i++) {
    ds_file.block[i].start = 0;
    ds_file.block[i].length = 0;
    ds_file.block[i].alloced = 0;
  }

  /* Write block array to file*/
  if (fwrite(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) != 1) {
    return 2;
  }

  /* Write additional bytes set into file*/
  char c = 0;
  if (fwrite(&c, sizeof(c), size, ds_file.fp) != size) {
    return 3;
  }

  if (fclose(ds_file.fp) != 0) {
    return 4;
  }

  return 0;
}

int ds_init (char* filename) {

  if ((ds_file.fp = fopen(filename, "rb+")) == NULL) {
    return 5;
  }

  if (fread(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) < 1) {
    return 6;
  }

  /*
  for (i = 0; i < MAX_BLOCKS; i++) {
    if (fread(&ds_file.block[i].start, sizeof(ds_file.block[i].start), 1, ds_file.fp) < 1) {
      return 6;
    }
    if (fread(&ds_file.block[i].length, sizeof(ds_file.block[i].length), 1, ds_file.fp) < 1) {
      return 7;
    }
    if (fread(&ds_file.block[i].alloced, sizeof(ds_file.block[i].alloced), 1, ds_file.fp) < 1){
      return 8;
    }
  }
*/
  ds_counts.reads = 0;
  ds_counts.writes = 0;

  return 0;
}

void ds_test_init() {

  int i;
  for (i = 0; i < MAX_BLOCKS; i++) {
    printf("%d: %lu, %lu, %d ", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
  }
  printf("\nReads: %d\nWrites: %d\n", ds_counts.reads, ds_counts.writes);
}

long ds_malloc(long amount) {

  long originalStart;
  long originalLength;
  long startOfBlock = -1;
  int i;

  for (i = 0; i < MAX_BLOCKS; i++) {
    if (ds_file.block[i].length >= amount && ds_file.block[i].alloced == 0) {
      originalLength = ds_file.block[i].length;
      originalStart = ds_file.block[i].start;
      ds_file.block[i].length = amount;
      ds_file.block[i].alloced = 1;
      startOfBlock = ds_file.block[i].start;
      break;
    }
  }

  if (startOfBlock < 0) {
    return -1;
  }

  for (i = 0; i < MAX_BLOCKS; i++) {
    if (ds_file.block[i].length == 0) {
      ds_file.block[i].start = originalStart + amount;
      ds_file.block[i].length = originalLength - amount;
      ds_file.block[i].alloced = 0;
      break;
    }
  }

  return startOfBlock;
}

void ds_free(long start) {

  int i;

  for (i = 0; i < MAX_BLOCKS; i++) {
    if (ds_file.block[i].start == start) {
      ds_file.block[i].alloced = 0;
      return;
    }
  }
}

void *ds_read(void *ptr, long start, long bytes);

long ds_write(long start, void* ptr, long bytes);

int ds_finish();

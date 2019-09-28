#include "ds_memory.h"

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;

int ds_create(char* filename, long size) {

  int i;
  char c = 0;

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
    return 1;
  }

  if (fread(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) < 1) {
    return 2;
  }

  ds_counts.reads = 0;
  ds_counts.writes = 0;

  return 0;
}


void ds_test_init() {

  int i;
  for (i = 0; i < 100; i++) {
    printf("%d: %lu, %lu, %d      ", i, ds_file.block[i].start, ds_file.block[i].length, ds_file.block[i].alloced);
    if (i % 3 == 0 && i != 0) {
      printf("\n");
    }
  }
  printf("\nreads: %d\nwrites: %d\n", ds_counts.reads, ds_counts.writes);
}


long ds_malloc(long amount) {

  long originalStart = -1;
  long originalLength = -1;
  long startOfBlock = -1;
  int i;

  for (i = 0; i < MAX_BLOCKS; i++) {
    if ((ds_file.block[i].length >= amount) && (ds_file.block[i].alloced == 0)) {
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


void *ds_read(void *ptr, long start, long bytes) {

  if (fseek(ds_file.fp, sizeof(ds_file.block) + start, SEEK_SET) != 0) {
    return NULL;
  }
  if (fread(ptr, bytes, 1, ds_file.fp) < 1) {
    return NULL;
  }
  ds_counts.reads++;
  return ptr;
}


long ds_write(long start, void* ptr, long bytes) {

  if (fseek(ds_file.fp, sizeof(ds_file.block) + start, SEEK_SET) != 0) {
    return -1;
  }
  if (fwrite(ptr, bytes, 1, ds_file.fp) < 1) {
    return -1;
  }
  ds_counts.writes++;

  return start;
}

/*TODO: REPLACE OUTPUT TO BE CORRECT*/
int ds_finish() {

  if (fseek(ds_file.fp, 0, SEEK_SET) != 0) {
    return 1;
  }

  if (fwrite(&ds_file.block, sizeof(ds_file.block), 1, ds_file.fp) != 1) {
    return 2;
  }

  if (fclose(ds_file.fp) != 0) {
    return 3;
  }

  printf("reads: %d\n",ds_counts.reads);
  printf("writes: %d\n", ds_counts.writes);

  return 0;
}

#include "ds_memory.h"
#include "ds_array.h"

int main() {
  ds_create("array.bin", 2048);
  ds_create_array();
  ds_init_array();
  ds_test_init();
  ds_finish();
  return 0;
}

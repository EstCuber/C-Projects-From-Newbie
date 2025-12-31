#include "../../libs/allocators/allocator_with_list/allocator.h"
#define COUNT 10000
int main(void) {
  char *obj[COUNT];
  printf("-----ЗАПУСК АЛЛОКАЦИИ %d БЛОКОВ!-----\n", COUNT);
  for (int i = 0; i < COUNT; i++) {
    obj[i] = (char *)malloc(64);
  }
  info_alloc(DBG_ALLOC_NOT_FREE);
  printf("-----ОСВОБОЖДЕНИЕ %d ОБЪЕКТОВ!-----\n", COUNT);
  for (int i = 0; i < COUNT; i++) {
    free(obj[i]);
  }
  info_alloc(DBG_ALLOC_FREE);

  obj[0] = (char *)malloc(60000);
  printf("-----ВЫДЕЛИЛ ОДИН ПОЛНОЦЕННЫЙ БЛОК В 60000!\n");
  info_alloc(DBG_ALLOC_ALL);
  free(obj[0]);
  printf("-----ОСВОБОДИЛ ЗАСРАНЦА!-----\n");
  info_alloc(DBG_ALLOC_ALL);

  return 0;
}

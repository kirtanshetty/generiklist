#include <stdint.h>

#include "../src/gklist.h"
#include "./demo_classes/foo.h"

#define LIST_LENGTH 10
#define DIVIDER_LINE "\n-------------------------------------------------------------------------------\n"

int main(int argc, char const *argv[])
{
  generiklist<foo, uint16_t> *kl = new generiklist<foo, uint16_t>();

  for(uint16_t i = 1; i <= LIST_LENGTH; i++){
    kl->push(new foo(i));
  }

  gkn_iterator<foo> foo_itr_1;
  kl->iterator_head(&foo_itr_1);

  int count = 1;
  printf("Printing in while loop from head\n");
  do{
    printf(" -> %d", foo_itr_1.obj->x);
    kl->get_next(&foo_itr_1);
    count += 1;
  } while(foo_itr_1.obj && count < 10);
  printf(DIVIDER_LINE);

  // foo_itr_1 = kl->iterator_tail();
  printf("Printing in while loop from tail\n");
  do{
    printf(" -> %d", foo_itr_1.obj->x);
    kl->get_prev(&foo_itr_1);
  } while(foo_itr_1.obj);
  printf(DIVIDER_LINE);

  // foo* foo_itr_2;
  printf("Printing in for loop from head\n");
  gkn_iterator<foo> foo_itr_2;
  kl->iterator_head(&foo_itr_2);
  count = 1;
  for(kl->iterator_head(&foo_itr_2); foo_itr_2.obj != nullptr; kl->get_next(&foo_itr_2)){
    if(count > 9)
      break;
    printf(" -> %d", foo_itr_2.obj->x);
    count  += 1;
  }
  printf(DIVIDER_LINE);

  printf("Printing in for loop from tail\n");
  for(; foo_itr_2.obj != nullptr; kl->get_prev(&foo_itr_2)){
    printf(" -> %d", foo_itr_2.obj->x);
    count  += 1;
  }
  printf(DIVIDER_LINE);
}
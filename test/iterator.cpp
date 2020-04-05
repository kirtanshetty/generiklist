#include <iostream>
#include <stdint.h>

#include "../src/gklist.h"
#include "./demo_classes/foo.h"

#define LIST_LENGTH 10
// #DIVIDER_LINE;\n--------------------------------------------------------\n"

int main(int argc, char const *argv[])
{
  gk_list<foo, uint16_t> *kl = new gk_list<foo, uint16_t>();

  for(uint16_t i = 1; i <= LIST_LENGTH; i++){
    kl->push_back(new foo(i));
  }

  gkl_iterator<foo> foo_itr_1;
  kl->begin(&foo_itr_1);

  int count = 1;
  DIVIDER_LINE;
  printf("Printing in while loop from head\n");
  do{
    printf(" -> %d", foo_itr_1.obj->x);
    kl->get_next(&foo_itr_1);
    count += 1;
  } while(foo_itr_1.obj && count < 10);
  DIVIDER_LINE;

  // foo_itr_1 = kl->iterator_tail();
  printf("Printing in while loop from tail\n");
  do{
    printf(" -> %d", foo_itr_1.obj->x);
    kl->get_prev(&foo_itr_1);
  } while(foo_itr_1.obj);
  DIVIDER_LINE;

  // foo* foo_itr_2;
  printf("Printing in for loop from head\n");
  gkl_iterator<foo> foo_itr_2;
  count = 1;
  for(kl->begin(&foo_itr_2); foo_itr_2.obj != nullptr; kl->get_next(&foo_itr_2)){
    if(count > 9)
      break;
    printf(" -> %d", foo_itr_2.obj->x);
    count  += 1;
  }
  DIVIDER_LINE;

  printf("Printing in for loop from tail\n");
  for(; foo_itr_2.obj != nullptr; kl->get_prev(&foo_itr_2)){
    printf(" -> %d", foo_itr_2.obj->x);
    count  += 1;
  }
  DIVIDER_LINE;
}

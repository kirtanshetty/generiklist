#include <stdint.h>

#include "../src/klist.h"

class foo{
public:
  int x;
  foo(int val){
    x = val;
  }
};

int main(int argc, char const *argv[])
{
  generiklist<foo, uint16_t> *kl = new generiklist<foo, uint16_t>();

  foo a(10);
  foo b(20);
  foo c(30);

  kl->remove_tail();
  kl->pop();

  kl->push(&a);
  // kl->print_klist();

  kl->exists(&a);
  kl->push(&a);
  // kl->print_klist();

  kl->push(&a);
  // kl->print_klist();

  kl->pop();
  // kl->print_klist();

  kl->push(&b);
  // kl->print_klist();

  kl->push(&c);
  // kl->print_klist();

  kl->add_to_head(&c);
  // kl->print_klist();

  kl->add_to_index(&c, 3);
  // kl->print_klist();

  kl->add_to_index(&b, 0);
  // kl->print_klist();

  kl->add_to_index(&b, kl->get_length());
  // kl->print_klist();

  kl->remove_from_index(0);
  // kl->print_klist();

  kl->remove_from_index(kl->get_length());
  // kl->print_klist();

  kl->remove_from_index(3);
  // kl->print_klist();


  // kl->remove_tail();
  // kl->pop();


  printf("length %u\n", kl->get_length());

  return 0;
}
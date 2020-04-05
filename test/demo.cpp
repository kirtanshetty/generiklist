#include <stdint.h>

#include "../src/gklist.h"
#include "./demo_classes/foo.h"

int main(int argc, char const *argv[])
{
  gk_list<foo, uint16_t> *kl = new gk_list<foo, uint16_t>();

  foo a(10);
  foo b(20);
  foo c(30);

  kl->pop_front();

  kl->push_back(&a);
  // kl->print_klist();

  kl->exists(&a);
  kl->push_back(&a);
  // kl->print_klist();

  kl->push_back(&a);
  // kl->print_klist();

  kl->pop_front();
  // kl->print_klist();

  kl->push_back(&b);
  // kl->print_klist();

  kl->push_back(&c);
  // kl->print_klist();

  kl->push_front(&c);
  // kl->print_klist();

  kl->add_to_index(&c, 3);
  // kl->print_klist();

  kl->add_to_index(&b, 0);
  // kl->print_klist();

  kl->add_to_index(&b, kl->length());
  // kl->print_klist();

  kl->remove_from_index(0);
  // kl->print_klist();

  kl->remove_from_index(kl->length());
  // kl->print_klist();

  kl->remove_from_index(3);
  // kl->print_klist();


  // kl->remove_tail();
  // kl->pop_front();


  printf("length %u\n", kl->length());

  return 0;
}
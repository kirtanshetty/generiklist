#include <time.h>
#include <sys/time.h>
#include <list>

#include <stdint.h>

#include "../../src/gklist.h"
#include "../demo_classes/foo.h"

#define SMALL_TEST 1000
#define MEDIUM_TEST 10000
#define LARGE_TEST 100000

typedef uint32_t listlen_t;

void gkpush_test(gk_list<foo, listlen_t>* kl, listlen_t size){
  for(listlen_t i = 1; i <= size; i++){
    // printf("i=%d\n", i);
    kl->push(new foo(i));
  }
}

void stlpush_test(std::list<foo>* sl, listlen_t size){
  for(listlen_t i = 1; i <= size; i++){
    sl->push_back(foo(i));
  }
}

gk_list<foo, listlen_t>* init_list(){
  return new gk_list<foo, listlen_t>();
}

long long getTimeStamp() {
  struct timeval time;
  gettimeofday(&time, NULL);
  long long milliseconds = time.tv_sec*1000LL + time.tv_usec/1000;
  return milliseconds;
}

// unsigned long getTimeStamp(){
//   return (unsigned long)time(NULL);
// }

void deinit_list(gk_list<foo, listlen_t>* _kl){
  delete _kl;
}

void run_test(uint8_t test_no, listlen_t test_size){
  DIVIDER_LINE;
  printf("Test %u: List size %u", test_no, test_size);
  DIVIDER_LINE;

  gk_list<foo, listlen_t> kl;
  long long gkstartTime = getTimeStamp();
  gkpush_test(&kl, test_size);
  long long gkendTime = getTimeStamp();
  printf("Operation started: %llu\n", gkstartTime);
  printf("Operation ended: %llu\n", gkendTime);
  printf("Time required: %llu\n", gkendTime - gkstartTime);
  // deinit_list(kl);

  std::list<foo> stl_list;
  long long stlstartTime = getTimeStamp();
  stlpush_test(&stl_list, test_size);
  long long stlendTime = getTimeStamp();
  printf("Operation started: %llu\n", stlstartTime);
  printf("Operation ended: %llu\n", stlendTime);
  printf("Time required: %llu\n", stlendTime - stlstartTime);


  DIVIDER_LINE;
  LINE_DOUBLE_BREAK;
}

int main(int argc, char const *argv[])
{
  run_test(1, SMALL_TEST);
  run_test(1, MEDIUM_TEST);
  run_test(1, LARGE_TEST);
}

#ifndef __GKL_OBJECTS_H__
#define __GKL_OBJECTS_H__

#define EMPTY_NODE nullptr

template<class T>
class gkl_node {
public:
  T* obj;
  gkl_node<T>* next;
  gkl_node<T>* prev;

  gkl_node(){
    obj = EMPTY_NODE;
    next = EMPTY_NODE;
    prev = EMPTY_NODE;
  }

  gkl_node(T* _obj){
    obj = _obj;
    next = EMPTY_NODE;
    prev = EMPTY_NODE;
  }
};

template<class T>
class gkl_iterator {
public:
  gkl_node<T>* this_node;
  T* obj;

  gkl_iterator(){
    this_node = EMPTY_NODE;
    obj = EMPTY_NODE;
  }

  void init(gkl_node<T>* _gkn, T* _obj){
    this_node = _gkn;
    obj = _obj;
  }
};

#endif

#ifndef __GKL_OBJECTS_H__
#define __GKL_OBJECTS_H__

#define EMPTY_NODE nullptr

template<class T>
class gknode {
public:
  T* obj;
  gknode<T>* next;
  gknode<T>* prev;

  gknode(){
    obj = EMPTY_NODE;
    next = EMPTY_NODE;
    prev = EMPTY_NODE;
  }

  gknode(T* _obj){
    obj = _obj;
    next = EMPTY_NODE;
    prev = EMPTY_NODE;
  }
};

template<class T>
class gkn_iterator {
public:
  gknode<T>* this_node;
  T* obj;

  gkn_iterator(){
    this_node = EMPTY_NODE;
    obj = EMPTY_NODE;
  }

  void init(gknode<T>* _gkn, T* _obj){
    this_node = _gkn;
    obj = _obj;
  }
};

#endif

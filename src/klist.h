#include <cstddef>
#include <stdio.h>

#define EMPTY_NODE nullptr

// Change the loggers when you add it to your repository
#define LOG_ERR printf
#define LOG_WARN printf
#define LOG_DEBUG printf

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

template<class T, class U>
class generiklist {
private:
  bool acceptDuplicate;
  gknode<T>* list_head;
  U length;

  bool isDuplicate(T* node_obj, bool log_msg = true){
    if(acceptDuplicate) return false;

    gknode<T>* itr = list_head;

    if(!itr) return false;

    do{
      if(itr->obj == node_obj){
        if(log_msg){
          LOG_WARN("Cannot add duplicate object. Change the generiklist initialization to accept duplicate objects.\n");
        }
        return true;
      }
      itr = itr->next;
    } while(itr);

    return false;
  }

public:

  generiklist(bool _acceptDuplicate = false){
    acceptDuplicate = _acceptDuplicate;
    list_head = EMPTY_NODE;
    length = 0;
  }

  void push(T* node_obj){
    if(isDuplicate(node_obj)){
      return;
    }

    gknode<T>* new_node = new gknode<T>(node_obj);

    if(!list_head){
      list_head = new_node;
      length += 1;
      return;
    }

    gknode<T>* itr = list_head;
    while(itr->next)
      itr = itr->next;

    itr->next = new_node;
    new_node->prev = itr;
    length += 1;
  }

  T* pop(){
    if(!list_head){
      length = 0;
      return EMPTY_NODE;
    }

    gknode<T>* itr = list_head;
    T* obj = itr->obj;

    if(!itr->next){
      list_head = EMPTY_NODE;
      length -= 1;
    }
    else{
      list_head = itr->next;
      if(length != 1)
        list_head->prev = EMPTY_NODE;
      length -= 1;
    }

    delete itr;

    return obj;
  }

  void add_to_head(T* node_obj){
    if(isDuplicate(node_obj)){
      return;
    }

    gknode<T>* new_node = new gknode<T>(node_obj);

    if(!list_head){
      list_head = new_node;
      length += 1;
      return;
    }

    new_node->next = list_head;
    list_head->prev = new_node;
    list_head = new_node;
    length += 1;
  }

  T* remove_head(){
    return pop();
  }

  void add_to_tail(T* node_obj){
    push(node_obj);
  }

  T* remove_tail(){
    if(!list_head){
      length = 0;
      LOG_DEBUG("List is already empty.\n");
      return EMPTY_NODE;
    }

    T* obj = EMPTY_NODE;

    gknode<T>* itr = list_head;
    while(itr->next)
      itr = itr->next;

    obj = itr->obj;

    if(length != 1)
      itr->prev->next = EMPTY_NODE;

    delete itr;

    length -= 1;

    return obj;

  }

  void add_to_index(T* node_obj, U index){
    if(isDuplicate(node_obj)){
      return;
    }

    if(index > length){
      LOG_ERR("Index %u is greater than the length %u\n", index, length);
      return;
    }

    if(index == 0){
      add_to_head(node_obj);
      return;
    }

    if(index == length){
      add_to_tail(node_obj);
      return;
    }

    gknode<T>* new_node = new gknode<T>(node_obj);
    U counter = 0;
    gknode<T>* itr = list_head;
    while(counter != index){
      itr = itr->next;
      counter += 1;
    }

    new_node->next = itr;
    new_node->prev = itr->prev;

    itr->prev->next = new_node;
    itr->prev = new_node;
    length += 1;
  }

  T* remove_from_index(U index){
    if(index >= length){
      LOG_ERR("add_to_index: index is greater than the length\n");
      return EMPTY_NODE;
    }

    if(index == 0)
      return pop();

    if(index == length - 1)
      return remove_tail();

    U counter = 0;
    gknode<T>* itr = list_head;
    T* obj = EMPTY_NODE;
    while(counter != index){
      itr = itr->next;
      counter += 1;
    }

    obj = itr->obj;
    itr->next->prev = itr->prev;
    itr->prev->next = itr->next;
    length -= 1;

    delete itr;

    return obj;
  }

  bool exists(T* node_obj){
    return isDuplicate(node_obj, false);
  }

  U get_length(){
    return length;
  }

  // uncomment only to test the demo file in test directory
  // void gprint_klist(){
  //   if(!list_head){
  //     LOG_DEBUG("Linked list is empty\n");
  //     return;
  //   }

  //   gknode<T>* itr = list_head;
  //   LOG_ERR("%d : ", length);
  //   do{
  //     LOG_ERR("->%d", itr->obj->x);
  //     itr = itr->next;
  //   } while(itr);
  //   LOG_ERR("\n");
  // }
};




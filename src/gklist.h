#ifndef __GK_LIST_H__
#define __GK_LIST_H__

#include <cstddef>
#include <stdio.h>

#include "gklobjects.h"

// Change the loggers when you add it to your repository
#define LOG_ERR printf
#define LOG_WARN printf
#define LOG_DEBUG printf

template<class T, class U>
class gk_list {
private:
  bool acceptDuplicate;
  gkl_node<T>* list_head;
  U len;

  gkl_node<T>* find_obj_node(T* node_obj){
    gkl_node<T>* itr = list_head;

    if(!itr) return EMPTY_NODE;

    do{
      if(itr->obj == node_obj){
        return itr;
      }
      itr = itr->next;
    } while(itr);

    return EMPTY_NODE;
  }

  bool isDuplicate(T* node_obj, bool log_msg = true){
    if(find_obj_node(node_obj)){
      if(log_msg){
        LOG_ERR("Cannot add duplicate object. Change the gk_list initialization to accept duplicate objects.");
      }

      return true;
    }

    return false;
  }

  void free_memory(gkl_node<T>* fnode){
    delete fnode;
  }

public:

  gk_list(bool _acceptDuplicate = false){
    acceptDuplicate = _acceptDuplicate;
    list_head = EMPTY_NODE;
    len = 0;
  }

  void push(T* node_obj){
    if(!acceptDuplicate && isDuplicate(node_obj)){
      return;
    }

    gkl_node<T>* new_node = new gkl_node<T>(node_obj);

    if(!list_head){
      list_head = new_node;
      len += 1;
      return;
    }

    gkl_node<T>* itr = list_head;
    while(itr->next)
      itr = itr->next;

    itr->next = new_node;
    new_node->prev = itr;
    len += 1;
  }

  T* pop(){
    if(!list_head){
      len = 0;
      return EMPTY_NODE;
    }

    gkl_node<T>* itr = list_head;
    T* obj = itr->obj;

    if(!itr->next){
      list_head = EMPTY_NODE;
      len -= 1;
    }
    else{
      list_head = itr->next;
      if(len != 1)
        list_head->prev = EMPTY_NODE;
      len -= 1;
    }

    delete itr;

    return obj;
  }

  void add_to_head(T* node_obj){
    if(!acceptDuplicate && isDuplicate(node_obj)){
      return;
    }

    gkl_node<T>* new_node = new gkl_node<T>(node_obj);

    if(!list_head){
      list_head = new_node;
      len += 1;
      return;
    }

    new_node->next = list_head;
    list_head->prev = new_node;
    list_head = new_node;
    len += 1;
  }

  T* remove_head(){
    return pop();
  }

  void add_to_tail(T* node_obj){
    push(node_obj);
  }

  T* remove_tail(){
    if(!list_head){
      len = 0;
      LOG_DEBUG("List is already empty.\n");
      return EMPTY_NODE;
    }

    T* obj = EMPTY_NODE;

    gkl_node<T>* itr = list_head;
    while(itr->next)
      itr = itr->next;

    obj = itr->obj;

    if(len != 1)
      itr->prev->next = EMPTY_NODE;

    delete itr;

    len -= 1;

    return obj;

  }

  void add_to_index(T* node_obj, U index){
    if(!acceptDuplicate && isDuplicate(node_obj)){
      return;
    }

    if(index > len){
      LOG_ERR("Index %u is greater than the len %u\n", index, len);
      return;
    }

    if(index == 0){
      add_to_head(node_obj);
      return;
    }

    if(index == len){
      add_to_tail(node_obj);
      return;
    }

    gkl_node<T>* new_node = new gkl_node<T>(node_obj);
    U counter = 0;
    gkl_node<T>* itr = list_head;
    while(counter != index){
      itr = itr->next;
      counter += 1;
    }

    new_node->next = itr;
    new_node->prev = itr->prev;

    itr->prev->next = new_node;
    itr->prev = new_node;
    len += 1;
  }

  void remove(T* node_obj){
    gkl_node<T>* temp_node = find_obj_node(node_obj);

    if(!temp_node) return;

    if(list_head == temp_node) list_head = temp_node->next;
    if(temp_node->prev) temp_node->prev->next = temp_node->next;
    if(temp_node->next) temp_node->next->prev = temp_node->prev;

    len -= 1;

    if(!len) list_head = EMPTY_NODE;

    free_memory(temp_node);
  }

  T* remove_from_index(U index){
    if(index >= len){
      LOG_ERR("add_to_index: index is greater than the len\n");
      return EMPTY_NODE;
    }

    if(index == 0)
      return pop();

    if(index == len - 1)
      return remove_tail();

    U counter = 0;
    gkl_node<T>* itr = list_head;
    T* obj = EMPTY_NODE;
    while(counter != index){
      itr = itr->next;
      counter += 1;
    }

    obj = itr->obj;
    itr->next->prev = itr->prev;
    itr->prev->next = itr->next;
    len -= 1;

    if(!len) list_head = EMPTY_NODE;

    delete itr;

    return obj;
  }

  T* truncate(){
    T* count = 0;
    while(pop()){
      count += 1;
    }

    return count;
  }

  void begin(gkl_iterator<T>* itr){
    itr->init(list_head, list_head ? list_head->obj : EMPTY_NODE);
  }

  void get_next(gkl_iterator<T>* itr_obj){
    if(!itr_obj->this_node || !itr_obj->this_node->next) {
      itr_obj->init(EMPTY_NODE, EMPTY_NODE);
      return;
    }

    itr_obj->init(itr_obj->this_node->next, itr_obj->this_node->next->obj);
  }

  void get_prev(gkl_iterator<T>* itr_obj){
    if(!itr_obj->this_node || !itr_obj->this_node->prev) {
      itr_obj->init(EMPTY_NODE, EMPTY_NODE);
      return;
    }

    if(!itr_obj->this_node->prev){
      itr_obj->init(itr_obj->this_node, EMPTY_NODE);
      return;
    }

    itr_obj->init(itr_obj->this_node->prev, itr_obj->this_node->prev->obj);
  }

  bool exists(T* node_obj){
    return isDuplicate(node_obj, false);
  }

  U length(){
    return len;
  }

  // uncomment only to test the demo file in test directory
  // void gprint_klist(){
  //   if(!list_head){
  //     LOG_DEBUG("Linked list is empty\n");
  //     return;
  //   }

  //   gkl_node<T>* itr = list_head;
  //   LOG_ERR("%d : ", len);
  //   do{
  //     LOG_ERR("->%d", itr->obj->x);
  //     itr = itr->next;
  //   } while(itr);
  //   LOG_ERR("\n");
  // }
};

#endif

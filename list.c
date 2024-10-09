#include "list.h"
int length(struct Node* head){
  int count = 0;
  while(head){
    count++;
    head = head->next;
  }
  return count;
}

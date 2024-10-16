#include <assert.h>
#include <stdlib.h>
#include "list.h"
int length(struct Node* head){
  int count = 0;
  while(head){
    count++;
    head = head->next;
  }
  return count;
}
struct Node* buildOneTwoThree(){
  struct Node* head = malloc(sizeof(struct Node));
  head->data = 1;
  head->next = malloc(sizeof(struct Node));
  
  head->next->data = 2;
  head->next->next = malloc(sizeof(struct Node));

  head->next->next->data = 3;
  head->next->next->next = NULL;

  return head;
}

int count(struct Node* curr, int n){
  int c = 0;
  while(curr){
    int cn = curr->data;
    if(cn == n)
      c++;
    curr = curr->next;
  }
  return c;
}

int getNth(struct Node* head, int index){
  assert(head != NULL);
  assert(0 <= index);
  assert(index < length(head));
  while(head && index){
    index--;
    head = head->next;
  }
  return head->data;
}

#ifndef LIST_H
#define LIST_H

struct node {
  int data;
  struct node* next;
};

int length(struct node* head);


#endif

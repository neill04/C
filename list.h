#ifndef LIST_H
#define LIST_H
struct Node {
  int data;
  struct Node* next;
};
int length(struct Node* head);
#endif

#ifndef NODE_H
#define NODE_H


class Node {
public:
  char data;
  int frequency;
  Node *left, *right;

  Node(char data, int frequency);
};


#endif // NODE_H

#ifndef COMPARE_H
#define COMPARE_H
#include "Node.h"

class Compare {
public:
  bool operator()(Node *left, Node *right);
};
#endif // COMPARE_H

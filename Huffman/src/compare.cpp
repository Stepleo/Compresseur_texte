#include "compare.h"
#include "Node.h"

bool Compare::operator()(Node *left, Node *right)
 {
    return left->frequency > right->frequency;
}


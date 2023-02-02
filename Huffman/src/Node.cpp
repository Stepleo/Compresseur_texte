#include "Node.h"

Node::Node(char data, int frequency)
{
    this->data=data;
    this->frequency=frequency;
    this->right=nullptr;
    this->left=nullptr;
}


#ifndef HUFFMANENCODER_H
#define HUFFMANENCODER_H
#include "Node.h"
#include <iostream>
#include <string>
#include <vector>

const int NUM_CHARS = 256;

class HuffmanEncoder {
private:
  int char_frequency[NUM_CHARS];
  Node *root;
  std::string char_code[NUM_CHARS];
  std::vector<Node *> nodes;
  std::string text;

public:
  HuffmanEncoder(const std::string &text);

  void build_huffman_code(Node *root, std::string code);
  std::string encode();

  void save_to_file(const std::string &encoded_text, int char_count[NUM_CHARS], const std::string &file_name);


  std::string* get_code(){return char_code; }

  int* get_freq(){return char_frequency; }
};


#endif // HUFFMANENCODER_H

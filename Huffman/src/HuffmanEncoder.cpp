#include "HuffmanEncoder.h"
#include "Node.h"
#include "compare.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

HuffmanEncoder::HuffmanEncoder(const std::string &text): text(text) {
    for (int i = 0; i < NUM_CHARS; i++) {
      char_frequency[i] = 0;
    }

    for (char ch : text) {
      char_frequency[ch]++;
    }

    for (int i = 0; i < NUM_CHARS; i++) {
      if (char_frequency[i] > 0) {
        nodes.push_back(new Node(i, char_frequency[i]));
      }
    }

    while (nodes.size() > 1) {
      std::sort(nodes.begin(), nodes.end(), Compare());
      Node *left = nodes[nodes.size() - 1];
      Node *right = nodes[nodes.size() - 2];
      nodes.pop_back();
      nodes.pop_back();

      Node *parent = new Node('\0', left->frequency + right->frequency);
      parent->left = left;
      parent->right = right;
      nodes.push_back(parent);
    }

    root = nodes[0];
  }


void HuffmanEncoder::build_huffman_code(Node *root, std::string code) {
    if (!root) {
      return;
    }

    if (root->data != '\0') {
      char_code[root->data] = code;
      return;
    }

    build_huffman_code(root->left, code + '0');
    build_huffman_code(root->right, code + '1');
  }

  std::string HuffmanEncoder::encode() {
    build_huffman_code(root, "");

    std::string encoded_text;
    for (char ch : text) {
      encoded_text += char_code[ch];
    }
    std::cout << "###########    Encode Method ########### " << std::endl;
    std::cout << "Original text: " << text << std::endl;
    std::cout << "Encoded text: " << encoded_text << std::endl;

    for (int i = 0; i < NUM_CHARS; i++) {
      if (!char_code[i].empty()) {
        std::cout << char(i) << ": " << char_code[i] << std::endl;
      }
    }
    std::cout << "###########    Encode Method ########### " << std::endl;
    std::cout << std::endl;
    return encoded_text;
  }



void HuffmanEncoder::save_to_file(const std::string &encoded_text, int char_count[NUM_CHARS], const std::string &file_name) {
    std::ofstream out_file(file_name, std::ios::binary);



    for (int i = 0; i < NUM_CHARS; i++) {
        if (char_count[i] > 0) {
        out_file<<i<<",";
        out_file<<char_count[i]<<"|";;
        }
    }


    out_file<<encoded_text;


    out_file.close();
}




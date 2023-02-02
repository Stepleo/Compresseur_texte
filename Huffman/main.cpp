#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Node.h"
#include "compare.h"
#include "HuffmanEncoder.h"








std::string decode( std::string& encoded_text, std::string codes[256]) {
    std::string Decompressed="";
    for (int i=0; i<256; i++){
        if (codes[i]!=""){
            int pos=encoded_text.find(codes[i]);
            //std::cout<<"position :"<< pos<< std::endl;
            if (pos==0) {
                Decompressed=Decompressed+(char)i;
                encoded_text=encoded_text.substr(codes[i].size());
                i=0;}}
}

    return Decompressed;
}

 void load_from_file(std::string& encoded_text, std::string& middle_string, const std::string &file_name) {


  std::ifstream in_file(file_name, std::ios::binary);
  //std::ofstream verif_file(file_name2, std::ios::binary);
  std::stringstream buffer;
  buffer << in_file.rdbuf();
  std::string contents = buffer.str();
  std::cout<<"saved output in the form  Ascii1 , frequency1 | Ascii2 , frequency2 | Ascii3 , frequency3 ...| Encoded text: "<<std::endl;
  std::cout << contents << std::endl;
  std::cout <<std::endl;
  in_file.close();


  std::istringstream iss(contents);
  for (std::string line; std::getline(iss, line, '|'); ){

    int commaPos = line.find(',');
    if (commaPos!=std::string::npos){
    //std::cout<<"line: "<<line<<std::endl;
    char asciiCode = (char) std::stoi(line.substr(0, commaPos));
    //std::cout<<"ascii: "<<asciiCode<<std::endl;
    int count = std::stoi(line.substr(commaPos + 1));
    //std::cout<<"count: "<<count<<std::endl;
    for (int i=0 ; i<count; i++){middle_string=middle_string+ asciiCode;}}
    else{
        std::cout<<"extracted encoded text : "<<line<<std::endl;
        std::cout <<std::endl;
        encoded_text=line;
    }
  }

}

int main() {
    std::string mode;
    std::cout << "Do you want to Enter a Text (0) to encode or a file directory to a .txt (any other character)? (0/Other): ";
    std::getline(std::cin ,mode);
    std::string text;
    if (mode=="0"){


        std::cout << "Enter the to-be-encoded Text (if Console crashes, then text is too long. please make a .txt): ";
        std::getline(std::cin ,text);
    }
    else{
        std::string filename;
        std::cout << "Enter the to-be-encoded file directory: ";
        std::getline(std::cin, filename);
        std::ifstream Textfile(filename, std::ios::binary);
        std::stringstream buffer;
        buffer << Textfile.rdbuf();
        text = buffer.str();

    }

    //std::cout << "Enter a string to encode using Huffman coding: ";
    //std::getline(std::cin, text);

    std::string encoded_text;
    HuffmanEncoder huffmanEncoder(text);
    encoded_text=huffmanEncoder.encode();

// Compressed string and root node

    int* char_count=huffmanEncoder.get_freq();
// Save the compressed string and root node to a file
    huffmanEncoder.save_to_file(encoded_text,char_count,"compressed.bin");

// Load the compressed string and root node from the file
    std::string new_text="";
    std::string encoded_text2;
    load_from_file(encoded_text2,new_text,"compressed.bin");
    std::cout<<"intermediary string reconstructed from the frequency of ASCII characters : "<<new_text<<std::endl;
    std::cout <<std::endl;
    std::cout<<"Now we encode this intermediary string to get the codes for each characters according to their frequencies : "<<std::endl;
    std::cout <<std::endl;

    HuffmanEncoder huffmanDecoder(new_text);
    huffmanDecoder.encode();
    std::string* Codes=huffmanDecoder.get_code();
    std::cout <<std::endl;
//Decode the compressed string into the decompressed string
    std::string decompressed=decode(encoded_text2, Codes);

    std::cout << "Decompressed text: " << decompressed << std::endl;

return 0;
}






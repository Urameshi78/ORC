#include <iostream>

#include "OCR/OCR.hpp"

int			main(int argc, char **argv){
  if (argc >= 3) {
    OCR ocr;
    int count = ocr.createSet(argv[1], argv[2]);
    std::cout << "Set created with " << count << " entries" << std::endl;
    if (count > 0){
      std::cout << "Output file is " << argv[2] << std::endl;
    }
    return (0);
  }
  std::cerr << "You must select a set folder" << std::endl;
  return (1);
}
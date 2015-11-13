#include <iostream>
#include "OCR/OCR.hpp"

int			main(int argc, char **argv){
  if (argc >= 4) {
    OCR ocr;

    //You have to do this step for the training set and the test set.
    // We are doing only once because for now we are missing samples
    int count = ocr.createSet(argv[1], argv[2]);
    std::cout << "Set created with " << count << " entries" << std::endl;
    if (count > 0){
      std::cout << "Output file is " << argv[2] << std::endl;
    }
    //-------------------

    std::cout << "Training Neural Network" << std::endl;
    ocr.trainNeuralNetwork(argv[2], argv[2], 88);

    std::cout << "Prediction : " << ocr.predictCharacter(argv[3]) << std::endl;
    return (0);
  }
  std::cerr << "Usage : sets/training_set output.ocr sets/training_set/1/66.bmp" << std::endl;
  return (1);
}

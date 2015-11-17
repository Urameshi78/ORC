#include <iostream>
#include "OCR/OCR.hpp"

int			main(int argc, char **argv){
  if (argc >= 4) {
    OCR ocr;

    //You have to do this step for the training set and the test set.
    // We are doing only once because for now we are missing samples
    int count = ocr.createSet(argv[1], argv[2]);
    std::cout << "Set created with " << count << " entries" << std::endl;
    if (count > 0) {
      std::cout << "Output file is " << argv[2] << std::endl;
      std::cout << "Training Neural Network" << std::endl;
      ocr.trainNeuralNetwork(argv[2], argv[2], 88); /* mettre un define */
      std::cout << "Prediction : " << ocr.predictCharacter(argv[3]) << std::endl;
    }
    else {
      std::cerr << "Error cannot create Ouput file for the training" << std::endl;
	return (1);
    }
    return (0);
  }
  std::cerr << "Usage : ./ocr sets/training_sets training_set.text sets/training_sets/1/42.bmp" << std::endl;
  return (1);
}

#include "OCR/OCR.hpp"

OCR::OCR()
:processor(){
}

OCR::~OCR(){
}

int OCR::createSet(std::string const &baseDir, std::string const &outputFile){
  return processor.processSet(baseDir, outputFile);
}

void OCR::trainNeuralNetwork(std::string const &pathTrainingSet, std::string const &pathTestSet, float performanceRequired){
}

void OCR::predict(std::string const &filepath){
}

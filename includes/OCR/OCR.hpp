#ifndef OCR_HPP
# define OCR_HPP

#include "OCR/ImageProcessor.hpp"
#include "OCR/MatriceOCR.hpp"

class OCR{

public:
  OCR();
  ~OCR();

  OCR(const OCR &) = delete;
  OCR &operator=(const OCR &) = delete;

  int   createSet(std::string const &baseDir, std::string const &outputFile);
  void  trainNeuralNetwork(std::string const &pathTrainingSet, std::string const &pathTestSet, float performanceRequired);
  void  predict(std::string const &filepath);

private:
  float	pcTrain(CvANN_MLP&, MatriceOCR&) const;
  ImageProcessor processor;
};

#endif /* OCR_HPP */

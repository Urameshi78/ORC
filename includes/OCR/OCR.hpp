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

  int		createSet(std::string const &baseDir, std::string const &outputFile);
  void		trainNeuralNetwork(std::string const &pathTrainingSet, std::string const &pathTestSet, float performanceRequired);
  void		predict(std::string const &filepath);
  std::string&	getFileTrain();

private:
  void	setFileTrain(const std::string&);
  float	pcTrain(CvANN_MLP&, MatriceOCR&) const;

  ImageProcessor processor;
  std::string	fileTrain;
};

#endif /* OCR_HPP */

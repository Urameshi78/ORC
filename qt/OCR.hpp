#ifndef OCR_HPP
# define OCR_HPP

#include "ImageProcessor.hpp"
#include "MatriceOCR.hpp"

class OCR{

public:
  OCR();
  ~OCR();

  OCR(const OCR &) = delete;
  OCR &operator=(const OCR &) = delete;

  int		            createSet(std::string const &baseDir, QString outputFile);
  void		          trainNeuralNetwork(std::string const &pathTrainingSet, std::string const &pathTestSet, float performanceRequired, int iterationRange = 10);
  char		          predictCharacter(std::string const &filepath);

  std::string const &getNeuralNetworkSerializedFile() const;
  bool              getIsTrained() const;
private:
  void	setNeuralNetworkSerializedFile(const std::string&);
  float	pcTrain();

  ImageProcessor processor;
  std::string 	 nnetworkFile;
  MatriceOCR	   matriceOcr;
  CvANN_MLP      nnetwork;
  bool           isTrained;
};

#endif /* OCR_HPP */

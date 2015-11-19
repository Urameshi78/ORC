#ifndef MATRICE_OCR_HPP
# define MATRICE_OCR_HPP

#include "SetReader.hpp"
#include <iostream>


class MatriceOCR
{

public :

  MatriceOCR();
  ~MatriceOCR();

  cv::Mat& getLayers();
  cv::Mat& getTraining_set();
  cv::Mat& getTraining_set_classifications();
  cv::Mat& getTest_set();
  cv::Mat& getTest_set_classifications();
  cv::Mat& getClassificationResult();
private :

  /* Matrix training & test */

  cv::Mat	layers;
  cv::Mat	training_set;
  cv::Mat	training_set_classifications;
  cv::Mat	test_set;
  cv::Mat	test_set_classifications;
  cv::Mat	classificationResult;
};

#endif /* !MATRICE_OCR_HPP */

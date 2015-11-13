#include "OCR/MatriceOCR.hpp"


MatriceOCR::MatriceOCR() : layers(3,1,CV_32S), training_set(TRAINING_SAMPLES,ATTRIBUTES,CV_32F), training_set_classifications(TRAINING_SAMPLES, CLASSES, CV_32F), test_set(TEST_SAMPLES,ATTRIBUTES,CV_32F), test_set_classifications(TEST_SAMPLES,CLASSES,CV_32F), classificationResult(1, CLASSES, CV_32F)
{
  this->layers.at<int>(0,0) = ATTRIBUTES;
  this->layers.at<int>(1,0) = 16;
  this->layers.at<int>(2,0) = CLASSES;
  
}

MatriceOCR::~MatriceOCR()
{
  
}

cv::Mat& MatriceOCR::getLayers() {
  return (layers);
}

cv::Mat& MatriceOCR::getTraining_set() {
  return (training_set);
}

cv::Mat& MatriceOCR::getTraining_set_classifications() {
  return (training_set_classifications);

}

cv::Mat& MatriceOCR::getTest_set() {
  return (test_set);
}

cv::Mat& MatriceOCR::getTest_set_classifications() {
  return (test_set_classifications);

}

cv::Mat& MatriceOCR::getClassificationResult() {
  return (classificationResult);
}

#include "OCR/OCR.hpp"

OCR::OCR()
:processor(){
}

OCR::~OCR(){
}

int OCR::createSet(std::string const &baseDir, std::string const &outputFile){
  return processor.processSet(baseDir, outputFile);
}

float OCR::pcTrain(CvANN_MLP& nnetwork, MatriceOCR& matriceOcr) const {

  cv::Mat test_sample;
  cv::Mat &test_set = matriceOcr.getTest_set();
  cv::Mat &test_set_classifications = matriceOcr.getTest_set_classifications();
  cv::Mat &classificationResult = matriceOcr.getClassificationResult();
  int correct_class = 0;
  int wrong_class = 0;

  int classification_matrix[CLASSES][CLASSES]={{}};
  
  for (int tsample = 0; tsample < TEST_SAMPLES; tsample++) {

    test_sample = test_set.row(tsample);

    nnetwork.predict(test_sample, classificationResult);

    int maxIndex = 0;
    float value=0.0f;
    float maxValue=classificationResult.at<float>(0,0);
    for(int index=1;index<CLASSES;index++)
      {   value = classificationResult.at<float>(0,index);
	if(value>maxValue)
	  {   maxValue = value;
	    maxIndex=index;
 
	  }
      }
    //    std::cout << "Testing Sample : " << tsample << " -> class result (digit :" << maxIndex << " )" << std::endl;
    if (test_set_classifications.at<float>(tsample, maxIndex)!=1.0f)
      {
	wrong_class++;
	for(int class_index=0;class_index<CLASSES;class_index++)
	  {
	    if(test_set_classifications.at<float>(tsample, class_index)==1.0f)
	      {
		classification_matrix[class_index][maxIndex]++;
		break;
	      }
	  }
 
      } else {
      correct_class++;
      classification_matrix[maxIndex][maxIndex]++;
    }
  }
  return (correct_class*100/TEST_SAMPLES);
}

void OCR::trainNeuralNetwork(std::string const &pathTrainingSet, std::string const &pathTestSet, float performanceRequired){

  MatriceOCR	matriceOcr;
  setReader	trainReader;

  /* train Performance */

  int		retPerformance = 0;

  trainReader.readDataSet(pathTrainingSet, matriceOcr.getTraining_set(), matriceOcr.getTraining_set_classifications(), TRAINING_SAMPLES);
  trainReader.readDataSet(pathTestSet, matriceOcr.getTest_set(), matriceOcr.getTest_set_classifications(), TEST_SAMPLES);


  CvANN_MLP nnetwork(matriceOcr.getLayers(), CvANN_MLP::SIGMOID_SYM,0.6,1);
  CvANN_MLP_TrainParams params(cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001), CvANN_MLP_TrainParams::BACKPROP, 0.1, 0.1);

  while (retPerformance < performanceRequired) {
    std::cout << "Using training dataset" << std::endl;
    nnetwork.train(matriceOcr.getTraining_set(), matriceOcr.getTraining_set_classifications(), cv::Mat(), cv::Mat(),params);

    CvFileStorage* storage = cvOpenFileStorage("param.xml", 0, CV_STORAGE_WRITE);
    nnetwork.write(storage,"DigitOCR");
    cvReleaseFileStorage(&storage);
    retPerformance = this->pcTrain(nnetwork, matriceOcr);
    std::cout << retPerformance << "%" <<std::endl;
  }
  this->setFileTrain("param.xml");
}

void OCR::predict(std::string const &filepath) {
  
  
}

void OCR::setFileTrain(const std::string& file) {
  this->fileTrain = file;
}

std::string& OCR::getFileTrain() {
  return (this->fileTrain);
}

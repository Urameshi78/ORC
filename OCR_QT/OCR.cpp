#include "OCR.hpp"

OCR::OCR()
:processor(), nnetworkFile("/home/pixies/Desktop/OCR/depot/ORC/qt/neuralnetwork.xml"), matriceOcr(), nnetwork(matriceOcr.getLayers(), CvANN_MLP::SIGMOID_SYM,0.6,1), isTrained(false){
  // TODO Load Serialized this->nnetwork file if he exists
}

OCR::~OCR(){
}

int OCR::createSet(std::string const &baseDir, QString outputFile){
  return processor.processSet(baseDir, outputFile);
}

float OCR::pcTrain() {

  cv::Mat test_sample;
  cv::Mat &test_set = this->matriceOcr.getTest_set();
  cv::Mat &test_set_classifications = this->matriceOcr.getTest_set_classifications();
  cv::Mat &classificationResult = this->matriceOcr.getClassificationResult();
  int correct_class = 0;
  int wrong_class = 0;

  int classification_matrix[CLASSES][CLASSES]={{}};

  for (int tsample = 0; tsample < TEST_SAMPLES; tsample++) {

    test_sample = test_set.row(tsample);

    this->nnetwork.predict(test_sample, classificationResult);

    int maxIndex = 0;
    float value=0.0f;
    float maxValue=classificationResult.at<float>(0,0);
    for(int index=1;index<CLASSES;index++){
      value = classificationResult.at<float>(0,index);
      if(value>maxValue){
        maxValue = value;
	maxIndex=index;
      }
    }

    //    std::cout << "Testing Sample : " << tsample << " -> class result (digit :" << maxIndex << " )" << std::endl;
    if (test_set_classifications.at<float>(tsample, maxIndex)!=1.0f){
      wrong_class++;
      for(int class_index=0;class_index<CLASSES;class_index++){
        if(test_set_classifications.at<float>(tsample, class_index)==1.0f){
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

void OCR::trainNeuralNetwork(std::string const &pathTrainingSet, std::string const &pathTestSet, float performanceRequired, int iterationRange){


  int		retPerformance = 0;

  SetReader::readDataSet(pathTrainingSet, this->matriceOcr.getTraining_set(), this->matriceOcr.getTraining_set_classifications(), TRAINING_SAMPLES);
  SetReader::readDataSet(pathTestSet, this->matriceOcr.getTest_set(), this->matriceOcr.getTest_set_classifications(), TEST_SAMPLES);


  CvANN_MLP_TrainParams params(cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 1000, 0.000001), CvANN_MLP_TrainParams::BACKPROP, 0.1, 0.1);


  for (int it = 0; it < iterationRange; ++it) {
    this->nnetwork.train(this->matriceOcr.getTraining_set(), this->matriceOcr.getTraining_set_classifications(), cv::Mat(), cv::Mat(),params);
    int performance = this->pcTrain();
    if (performance > retPerformance){
      retPerformance = performance;
      CvFileStorage* storage = cvOpenFileStorage(this->nnetworkFile.c_str(), 0, CV_STORAGE_WRITE);
      this->nnetwork.write(storage,"DigitOCR");
      cvReleaseFileStorage(&storage);
    }
  }
  if (retPerformance >= performanceRequired){
    std::cout << "We reached required performances : " << retPerformance << "%" << std::endl;
    isTrained = true;
  }else
    std::cout << "We couldn't reach required performances : " << retPerformance << "%" << std::endl;
}

char OCR::predictCharacter(std::string const &filepath) {
  if (isTrained == false)
    return 0;
  cv::Mat charaterMatrice = processor.processImage(filepath);
  cv::Mat classificationResult(1, CLASSES, CV_32F);
  this->nnetwork.predict(charaterMatrice, classificationResult);

  int maxIndex = 0;
  float value = 0.0f;
  float maxValue=classificationResult.at<float>(0,0);

  for(int index=1;index<CLASSES;index++){
    value = classificationResult.at<float>(0,index);
    if(value > maxValue){
      maxValue = value;
      maxIndex=index;
    }
  }
  return ((char) maxIndex + 32); // plus 32 POUR MONTER DANS LA TABLE ASCCI ET DISPLAY NOTRE CARAC
}

void OCR::setNeuralNetworkSerializedFile(const std::string& file) {
  this->nnetworkFile = file;
}

std::string const &OCR::getNeuralNetworkSerializedFile() const{
  return (this->nnetworkFile);
}

bool    OCR::getIsTrained() const{
  return isTrained;
}

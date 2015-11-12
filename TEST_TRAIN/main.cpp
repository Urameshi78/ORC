#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/features2d.hpp>
#include <stdio.h>
#include <fstream>


#define TRAINING_SAMPLES 95       //Number of samples in training dataset
#define ATTRIBUTES 256  //Number of pixels per sample.16X16
// #define TEST_SAMPLES 1170       //Number of samples in test dataset
#define CLASSES  95 //Number of distinct labels.

void read_dataset(char *filename, cv::Mat &data, cv::Mat &classes,  int total_samples)
{
 
  int label;
  float pixelvalue;
  //open the file
  FILE* inputfile = fopen(filename, "r" );
 
  //read each row of the csv file
  for(int row = 0; row < total_samples; row++)
    {
      //for each attribute in the row
      for(int col = 0; col <=ATTRIBUTES; col++)
        {
	  //if its the pixel value.
	  if (col < ATTRIBUTES){
	    std::cout << pixelvalue << std::endl;
	    data.at<float>(row,col) = pixelvalue;
 
	  }//if its the label
	  else if (col == ATTRIBUTES){
	    //make the value of label column in that row as 1.
	    fscanf(inputfile, "%i", &label);
	    classes.at<float>(row,label) = 1.0;
 
	  }
        }
    }
 
  fclose(inputfile);
}

void	testPredict(const cv::Ptr<cv::ml::ANN_MLP>& nnetwork, cv::Mat &test_sample, cv::Mat& classificationResult)
{
  nnetwork->predict(test_sample, classificationResult);
}
 
int	main(int argc, char **argv)
{
  if (argc >= 2) {
    std::string	fileTrain(argv[1]);    

    //matrix to hold the training sample
    cv::Mat training_set(TRAINING_SAMPLES,ATTRIBUTES,CV_32F);
    //matrix to hold the labels of each taining sample
    cv::Mat training_set_classifications(TRAINING_SAMPLES, CLASSES, CV_32F);


    cv::Mat classificationResult(1, CLASSES, CV_32F);

    read_dataset((char*)fileTrain.c_str(), training_set, training_set_classifications, TRAINING_SAMPLES);

    // define the structure for the neural network (MLP)
    // The neural network has 3 layers.
    // - one input node per attribute in a sample so 256 input nodes
    // - 16 hidden nodes
    // - 10 output node, one for each class.
 
    cv::Mat layers(3,1,CV_32S);
    layers.at<int>(0,0) = ATTRIBUTES;//input layer
    layers.at<int>(1,0)=16;//hidden layer
    layers.at<int>(2,0) =CLASSES;//output layer

    cv::Ptr<cv::ml::ANN_MLP> nnetwork = cv::ml::ANN_MLP::create();
    nnetwork->setActivationFunction(cv::ml::ANN_MLP::SIGMOID_SYM, 0.6,1);
    nnetwork->setTermCriteria(cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, (int)1000, 0.000001));
    nnetwork->setTrainMethod(cv::ml::ANN_MLP::BACKPROP, cv::ml::ANN_MLP::BACKPROP, cv::ml::ANN_MLP::BACKPROP);
    nnetwork->setBackpropMomentumScale(0.1);
    nnetwork->setBackpropWeightScale(0.1);
    nnetwork->setLayerSizes(layers); 
    std::cout << "Using training dataset" << std::endl;
    int iterations = nnetwork->train(training_set, cv::ml::ROW_SAMPLE, training_set_classifications);
    nnetwork->train(training_set, cv::ml::ROW_SAMPLE, training_set_classifications);
    nnetwork->train(training_set, cv::ml::ROW_SAMPLE, training_set_classifications);
    printf( "Training iterations: %i\n\n", iterations); 

    std::string trainFile("./param.xml");
    cv::FileStorage storage;
    storage.open(trainFile, 1);
    nnetwork->write(storage);
    storage.release();

    // Test the generated model with the test samples.
    cv::Mat test_sample;
    //count of correct classifications
    int correct_class = 0;
    //count of wrong classifications
    int wrong_class = 0;

    //classification matrix gives the count of classes to which the samples were classified.
    int classification_matrix[CLASSES][CLASSES]={{}};
    
    for (int tsample = 0; tsample < 95; tsample++) {
 
      // extract the sample
 
      test_sample = training_set.row(tsample);

      
      //try to predict its class

      testPredict(nnetwork, test_sample, classificationResult);
    std::cout << classificationResult << std::endl;
      /*The classification result matrix holds weightage  of each class.
	we take the class with the highest weightage as the resultant class */
 
      // find the class with maximum weightage.
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
      std::cout << "Testing Sample : " << tsample << "-> class result digit " << maxIndex <<std::endl;

      //Now compare the predicted class to the actural class. if the prediction is correct then\
      //test_set_classifications[tsample][ maxIndex] should be 1.
      //if the classification is wrong, note that.
      if (training_set_classifications.at<float>(tsample, maxIndex)!=1.0f)
	{
	  // if they differ more than floating point error => wrong class
 
	  wrong_class++;
 
	  //find the actual label 'class_index'
	  for(int class_index=0;class_index<CLASSES;class_index++)
	    {
	      if(training_set_classifications.at<float>(tsample, class_index)==1.0f)
		{
 
		  classification_matrix[class_index][maxIndex]++;// A class_index sample was wrongly classified as maxindex.
		  break;
		}
	    }
 
	} else {
 
	// otherwise correct
 
	correct_class++;
	classification_matrix[maxIndex][maxIndex]++;
      }
    }

    printf( "\nResults on the testing dataset\n"
	    "\tCorrect classification: %d (%g%%)\n"
	    "\tWrong classifications: %d (%g%%)\n", 
	    correct_class, (double) correct_class*100/95,
	    wrong_class, (double) wrong_class*100/95);
    std::cout<<"   ";
    //    for (int i = 0; i < CLASSES; i++)
    //      {
    //    	std::cout<< i<<"\t";
    //      }
    //    std::cout<<"\n";
    //    for(int row=0;row<CLASSES;row++)
    //      {std::cout<<row<<"  ";
    //    	for(int col=0;col<CLASSES;col++)
    //    	  {
    //    	    std::cout<<classification_matrix[row][col]<<"\t";
    //    	  }
    //    	std::cout<<"\n";
    //      }
    return (0);
  }
  std::cerr << "Don't forget the file mother fucke" << std::endl;
  return (1);
}

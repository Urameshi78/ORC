#include "OCR/SetReader.hpp"

setReader::setReader()
{

}

setReader::~setReader()
{
  
}


void setReader::readDataSet(const std::string &DataSetFile, cv::Mat &data, cv::Mat &classes, int max_samples)
{
  int label;
  float pixelvalue;
  //open the file
  FILE* inputfile = fopen(DataSetFile.c_str(), "r" );
 
  //read each row of the csv file
  for(int row = 0; row < max_samples; row++)
    {
      //for each attribute in the row
      for(int col = 0; col <= ATTRIBUTES; col++)
        {
	  //if its the pixel value.
	  if (col < ATTRIBUTES){
	    fscanf(inputfile, "%f,", &pixelvalue);
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

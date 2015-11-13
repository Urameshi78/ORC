#include "OCR/SetReader.hpp"


// TODO Convert to C++ Code
void SetReader::readDataSet(const std::string &DataSetFile, cv::Mat &data, cv::Mat &classes, int max_samples){
  int label;
  float pixelvalue;

  FILE* inputfile = fopen(DataSetFile.c_str(), "r" );

  for(int row = 0; row < max_samples; row++){
    for(int col = 0; col <= ATTRIBUTES; col++){
      if (col < ATTRIBUTES){
        fscanf(inputfile, "%f,", &pixelvalue);
        data.at<float>(row,col) = pixelvalue;
      }
      else if (col == ATTRIBUTES){
        fscanf(inputfile, "%i", &label);
        classes.at<float>(row,label) = 1.0;
      }
    }
  }
  fclose(inputfile);
}

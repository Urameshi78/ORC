#include "SetWriter.hpp"
#include "MatriceOCR.hpp"

SetWriter::SetWriter(QString outputFile)
  :fileOutputQ(outputFile)
{

}

SetWriter::~SetWriter(){
}

void	SetWriter::addMatToSet(cv::Mat const & img, int value,  QTextStream& stream){


  for (int x = 0; x < 16; ++x){
    for (int y = 0; y < 16; ++y){
          stream << ((img.at<uchar>(x, y) == 255) ? 1 : 0) << ",";
        }
    }
  stream << value << '\n';

}

cv::Mat SetWriter::convertMat(cv::Mat const &initialMat){
    cv::Mat res(1,ATTRIBUTES,CV_32F);
    int position = 0;
    for (int x = 0; x < 16; ++x){
      for (int y = 0; y < 16; ++y){
          int value = (initialMat.at<uchar>(x, y) == 255) ? 1 : 0;
          res.at<float>(0, position) = value;
          ++position;
      }
    }
    return res;
}

void SetWriter::close(){
  fileOutput.close();
}

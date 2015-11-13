#include "OCR/SetWriter.hpp"
#include "OCR/MatriceOCR.hpp"

SetWriter::SetWriter(std::string const &outputFile)
  :fileOutput(outputFile, std::ios::out)
{
  // Should check that file is open
}

SetWriter::~SetWriter(){
}

void	SetWriter::addMatToSet(cv::Mat const & img, int value){
  for (int x = 0; x < 16; ++x){
    for (int y = 0; y < 16; ++y){
        //  std::cout << "Test " << (int)(img.at<uchar>(x, y)) << std::endl;
          this->fileOutput << ((img.at<uchar>(x, y) == 255) ? 1 : 0) << ",";
        }
    }
  this->fileOutput << value << '\n';
}

cv::Mat SetWriter::convertMat(cv::Mat const &initialMat){
  std::cout << "BIATCH" << std::endl;
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

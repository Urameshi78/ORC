#include "OCR/SetWriter.hpp"

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
          this->fileOutput << ((img.at<uchar>(x, y) == 255) ? 1 : 0) << ",";
        }
    }
  this->fileOutput << value << '\n';
}

void SetWriter::close(){
  fileOutput.close();
}

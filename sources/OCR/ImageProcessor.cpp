#include <dirent.h>

#include "OCR/ImageProcessor.hpp"

ImageProcessor::ImageProcessor(){
}

ImageProcessor::~ImageProcessor(){

}

int     ImageProcessor::processSet(std::string const &baseDir, std::string const &outputFile){
  DIR * rep = opendir(baseDir.c_str());
  SetWriter writer(outputFile);
  int count = 0;

  if (rep != NULL){
      struct dirent * ent;
      while ((ent = readdir(rep)) != NULL){
        if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
          std::cout << baseDir + "/" + ent->d_name << std::endl;
          int nb = processSample(baseDir + "/" + ent->d_name, writer);
          if (nb == 0)
            return 0;
          count += nb;
        }
      }
    return count;
  }
  writer.close();
  return 0;
}

int     ImageProcessor::processSample(std::string const &baseDir, SetWriter & writer){
  int count = 0;
  for (int value = 32; value <= 126; ++value){
    ++count;
    std::cout << static_cast<char>(value) << std::endl;
    cv::Mat img = cv::imread(baseDir + "/" + std::to_string(value) + ".bmp", 0);
    if (img.empty())
      return 0;
    applyFilters(img);
    cropImgAndScaleDown(img);
    writer.addMatToSet(img, value - 32);
  }
  return count;
}

void		ImageProcessor::applyFilters(cv::Mat& img){
  cv::GaussianBlur(img, img, cv::Size(9,9),1);
  cv::threshold(img, img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
}

void		ImageProcessor::cropImgAndScaleDown(cv::Mat &img){
  this->cropImg(img);
  this->scallDown(img);
}

void		ImageProcessor::scallDown(cv::Mat &img){
  cv::Mat	imgScaledDown(16,16,CV_8U,cv::Scalar(0));

  for (int x = 0; x<16; x++){
    for (int y = 0; y<16; y++){
      int yd = ceil((float)(y*img.cols / 16));
      int xd = ceil((float)(x*img.rows / 16));
      if (yd > 0 && xd > 0){
        imgScaledDown.at<uchar>(x, y) = img.at<uchar>(xd, yd);
      }
    }
  }
  img = imgScaledDown.clone();
}

void		ImageProcessor::cropImg(cv::Mat &img){
  int row = img.rows;
  int col = img.cols;
  int tlx, tly, bry, brx;//t=top r=right b=bottom l=left
  tlx = tly = bry = brx = 0;
  float suml = 0;
  float sumr = 0;
  int flag = 0;

  /* TOP EDGE */
  for (int x = 1; x<row; x++){
    for (int y = 0; y<col; y++){
      if (img.at<uchar>(x, y) == 0){
        flag = 1;
        tly = x;
        break;
      }
    }
    if (flag == 1){
      flag = 0;
      break;
    }
  }

  /* BOTTOM EDGE */
  for (int x = row - 1; x>0; x--){
    for (int y = 0; y<col; y++){
      if (img.at<uchar>(x, y) == 0){
        flag = 1;
        bry = x;
        break;
      }
    }
    if (flag == 1){
      flag = 0;
      break;
    }
  }

  /* LEFT EDGE */
  for (int y = 0; y<col; y++){
    for (int x = 0; x<row; x++){
      if (img.at<uchar>(x, y) == 0){
        flag = 1;
        tlx = y;
        break;
      }
    }
    if (flag == 1){
      flag = 0;
      break;
    }
  }

  /* RIGHT EDGE */
  for (int y = col - 1; y>0; y--){
    for (int x = 0; x<row; x++){
      if (img.at<uchar>(x, y) == 0){
        flag = 1;
        brx = y;
        break;
      }
    }
    if (flag == 1){
      flag = 0;
      break;
    }
  }

  int width = brx - tlx;
  int height = bry - tly;
  cv::Mat crop(img, cv::Rect(tlx, tly, brx - tlx, bry - tly));
  img = crop.clone();
}

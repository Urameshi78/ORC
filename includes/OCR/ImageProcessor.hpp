#ifndef IMAGE_PROCESSOR_HPP
# define IMAGE_PROCESSOR_HPP

#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "OCR/SetWriter.hpp"

class ImageProcessor
{
public :

  ImageProcessor();
  ~ImageProcessor();

  ImageProcessor(ImageProcessor const &) = delete;
  ImageProcessor &operator=(ImageProcessor const &) = delete;

  int		 processSet(std::string const &baseDir, std::string const &outputFile);
  cv::Mat processImage(std::string const &filepath);
  int    processSample(std::string const &baseDir, SetWriter & writer);
private :

  void    applyFilters(cv::Mat &);
  void		cropImgAndScaleDown(cv::Mat &);
  void		cropImg(cv::Mat &);
  void		scallDown(cv::Mat &);
};

#endif /* !IMAGE_PROCESSOR_HPP */

#ifndef SET_WRITER_HPP
# define SET_WRITER_HPP

#include <fstream>
#include "opencv2/opencv.hpp"

class SetWriter
{
public :

  SetWriter(std::string const &outputFile);
  ~SetWriter();

  SetWriter(const SetWriter &) = delete;
  SetWriter &operator=(SetWriter const &) = delete;

  void	addMatToSet(cv::Mat const &, int value);
  static cv::Mat  convertMat(cv::Mat const &initialMat);
  void  close();

private :
  std::fstream	fileOutput;
};

#endif /* !SET_WRITER_HPP */

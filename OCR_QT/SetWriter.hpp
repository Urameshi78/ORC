#ifndef SET_WRITER_HPP
# define SET_WRITER_HPP

#include <fstream>
#include <QFile>
#include <QTextStream>
#include "opencv2/opencv.hpp"

class SetWriter
{
public :

  SetWriter(QString outputFile);
  ~SetWriter();

  SetWriter(const SetWriter &) = delete;
  SetWriter &operator=(SetWriter const &) = delete;

  void	addMatToSet(cv::Mat const &, int value,  QTextStream&);
  static cv::Mat  convertMat(cv::Mat const &initialMat);
  QFile         fileOutputQ;
  void  close();

private :
  std::fstream	fileOutput;
};

#endif /* !SET_WRITER_HPP */

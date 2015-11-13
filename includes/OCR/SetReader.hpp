#ifndef SET_READER_HPP
# define SET_READER_HPP

#include <fstream>
#include "opencv2/opencv.hpp"
#include "opencv2/ml/ml.hpp"

# define TRAINING_SAMPLES 95
# define TEST_SAMPLES 95
# define ATTRIBUTES 256
# define CLASSES 95


class SetReader
{
private:
  SetReader();

public:
  static void readDataSet(const std::string &DataSetFile, cv::Mat &data, cv::Mat &classes, int max_samples);
};

#endif /* ! SET_READER_HPP */

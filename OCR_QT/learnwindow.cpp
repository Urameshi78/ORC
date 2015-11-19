#include <QInputDialog>
#include <OCR.hpp>
 #include "learnwindow.h"

 extern std::string path;

LearnWindow::LearnWindow(Window *contentWindow)
  : Window("Learn", contentWindow)
{
}

        // Learn what image is
void LearnWindow::onClickFunction()
{
  bool ok;
  QString text = QInputDialog::getText(0, "What does the image represents ?",
				       "Text:", QLineEdit::Normal,
				       "", &ok);
  if (ok && !text.isEmpty()) {

    OCR ocr;

    //You have to do this step for the training set and the test set.
    // We are doing only once because for now we are missing samples


    int count = ocr.createSet(text.toStdString(), "/home/pixies/Desktop/OCR/depot/ORC/qt/OutputFile.txt");
    std::cout << "Set created with " << count << " entries" << std::endl;
    std::cout << "Training Neural Network" << std::endl;
    ocr.trainNeuralNetwork("/home/pixies/Desktop/OCR/depot/ORC/qt/OutputFile.txt", "/home/pixies/Desktop/OCR/depot/ORC/qt/OutputFile.txt", 88);
    std::cout   << "Verification de " << std::endl;
    std::cout << "Prediction : " << ocr.predictCharacter(path.c_str()) << std::endl;
  }
}

void LearnWindow::setImage()
{
  CreateImage(cv::Scalar(250, 0, 0), "Learn", cv::Scalar(0, 0, 0));
}

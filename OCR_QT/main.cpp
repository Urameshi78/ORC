#include <QCoreApplication>
#include "learnwindow.h"
#include "loadwindow.h"
#include "imagewindow.h"
#include "quitwindow.h"

#include <iostream>
#include <QApplication>


int main(int argc, char *argv[])
{
  QApplication app( argc, argv );

  ImageWindow image;
  LearnWindow learn(&image);
  LoadWindow load(&image);
  QuitWindow quit(&app);

  // Add settings buttons
  quit.Display(500, 700);
  learn.Display(500, 500); /* Take a look on   LearnWindow::onClickFunction() for the train/predict */
  load.Display(500, 300);
  // Image displaying will prompt for a image file
  image.Display(700, 200);
  return (app.exec());
}

#include "quitwindow.h"

QuitWindow::QuitWindow(QApplication *app)
    : Window("Quit", NULL)
{
    this->app = app;
}

void QuitWindow::onClickFunction()
{
    app->quit();
}

void QuitWindow::setImage()
{
    CreateImage(cv::Scalar(0, 250, 0), "Quit", cv::Scalar(250, 250, 250));
}

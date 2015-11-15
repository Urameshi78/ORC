#include "loadwindow.h"

LoadWindow::LoadWindow(Window *contentWindow)
 : Window("Load", contentWindow)
{
}

void LoadWindow::onClickFunction()
{
    contentWindow->LoadImage();
}

void LoadWindow::setImage()
{
    CreateImage(cv::Scalar(0, 0, 250), "Load", cv::Scalar(250, 250, 250));
}

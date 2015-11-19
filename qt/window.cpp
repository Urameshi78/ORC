#include "window.h"
#include <QFileDialog>
#include <iostream>

std::string path;

void onClickEventHandler(int event, int, int, int, void *window)
{
    Window *win = (Window*)window;
    if  ( event == cv::EVENT_LBUTTONDOWN ) {
        win->onClickFunction();
    }
}

Window::Window(std::string name, Window *contentWindow)
{
    this->name = name;
    this->contentWindow = contentWindow;
}

void Window::Display(int x, int y)
{
    setImage();
    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::moveWindow(name, x, y);
    cv::imshow(name, image);
    cv::setMouseCallback(name, onClickEventHandler, this);
}

void Window::LoadImage()
{
    path = QFileDialog::getOpenFileName(0,"Open Image", "/home/", "Image Files (*.bmp)").toStdString();
    image = cv::imread(path.c_str());
    if (image.empty() == false) {
        cv::imshow(name, image);
    }
    else {
        std::cerr << "Couldn't load the image given" << std::endl;
    }
}

void Window::CreateImage(cv::Scalar color, std::string text, cv::Scalar textColor)
{
    image = cv::Mat(125, 125, CV_8UC(1), color);
    cv::putText(image, text, cv::Point(30,60),cv::FONT_HERSHEY_COMPLEX_SMALL, 1, textColor);
}

cv::Mat Window::GetImage()
{
    return (image);
}

void Window::onClickFunction() {

}

void Window::setImage()
{
}

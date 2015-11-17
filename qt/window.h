#ifndef WINDOW_H
#define WINDOW_H

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Window
{
public:
    void            Display(int x, int y);
    void            LoadImage();
    void            CreateImage(cv::Scalar color, std::string text, cv::Scalar textColor);
    virtual void    onClickFunction();
    cv::Mat         GetImage();
    Window(std::string name, Window *contentWindow);
protected:
    Window          *contentWindow;
    std::string     name;
    cv::Mat         image;

    virtual void    setImage();
};

#endif // WINDOW_H

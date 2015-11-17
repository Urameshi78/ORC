#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include "window.h"

class ImageWindow : public Window
{
public:
    ImageWindow();
    virtual void onClickFunction();
protected:
    virtual void setImage();
};

#endif // IMAGEWINDOW_H

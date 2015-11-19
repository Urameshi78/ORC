#ifndef LEARNWINDOW_H
#define LEARNWINDOW_H

#include "window.h"

class LearnWindow : public Window
{
public:
    LearnWindow(Window *contentWindow);
    virtual void onClickFunction();
protected:
    virtual void setImage();
};

#endif // LEARNWINDOW_H

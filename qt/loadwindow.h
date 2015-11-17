#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include "window.h"

class LoadWindow : public Window
{
public:
    LoadWindow(Window *contentWindow);
    virtual void onClickFunction();
protected:
    virtual void setImage();
};

#endif // LOADWINDOW_H

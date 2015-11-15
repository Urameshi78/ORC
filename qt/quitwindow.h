#ifndef QUITWINDOW_H
#define QUITWINDOW_H

#include "window.h"
#include <QApplication>

class QuitWindow : public Window
{
public:
    QuitWindow(QApplication *app);
    virtual void onClickFunction();
protected:
    virtual void setImage();
private:
    QApplication *app;
};

#endif // QUITWINDOW_H

#include "imagewindow.h"
#include <QMessageBox>

ImageWindow::ImageWindow()
 : Window("Image", NULL)
{
}

// Scan Image
void ImageWindow::onClickFunction()
{
    QMessageBox msgBox;
    msgBox.setText("The image contains :");
    msgBox.setInformativeText("A"); // CHANGE TO ANSWER
    msgBox.exec();
}

void ImageWindow::setImage()
{
    LoadImage();
}

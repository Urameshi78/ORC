#include "learnwindow.h"
#include <QInputDialog>

LearnWindow::LearnWindow(Window *contentWindow)
    : Window("Learn", contentWindow)
{
}

// Learn what image is
void LearnWindow::onClickFunction()
{
    bool ok;
    QString text = QInputDialog::getText(0, "What does the image represents ?",
                                         "Text:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !text.isEmpty()) {
        // LEARN!
        // String is text.ToStdString()
        // Image is s_image
    }
}

void LearnWindow::setImage()
{
    CreateImage(cv::Scalar(250, 0, 0), "Learn", cv::Scalar(0, 0, 0));
}

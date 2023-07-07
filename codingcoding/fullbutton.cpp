#include "fullbutton.h"

FullButton::FullButton(QString ImagePath, QString Description, QWidget* parent)
{
    setParent(parent);
    QPixmap pixmap(ImagePath);
    setIcon(pixmap);
    setIconSize(QSize(150, 150));
    setFixedSize(150, 150);
    setStyleSheet("background-color: rgba(255, 255, 255, 5);");
    QFont font("Arial", 13, QFont::Bold);

    QLabel *label = new QLabel(Description);
    label->setParent(this);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
}

void FullButton::change_icon(QString ImagePath)
{
    QPixmap pixmap(ImagePath);
    setIcon(pixmap);
    setIconSize(QSize(150, 150));
}

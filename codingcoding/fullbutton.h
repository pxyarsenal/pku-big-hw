#ifndef FULLBUTTON_H
#define FULLBUTTON_H

#include <QPushButton>
#include <QWidget>
#include <QLabel>

class FullButton : public QPushButton
{
    Q_OBJECT
public:
    FullButton(QString ImagePath, QString Description, QWidget* parent = nullptr);

    void change_icon(QString ImagePath);
};

#endif // FULLBUTTON_H

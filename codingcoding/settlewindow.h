#ifndef SETTLEWINDOW_H
#define SETTLEWINDOW_H

#include <QWidget>
#include <QLabel>

#include "fullbutton.h"

class SettleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettleWindow(QWidget *parent = nullptr);
    void init(int mode, int _level_id);

    int level_id;
    static bool win_or_not;

private:
    QLabel *background_label;
    FullButton *restart;
    FullButton *to_exit;

signals:
    void Restarted(int id);
    void BacktoMain();

};

#endif // SETTLEWINDOW_H

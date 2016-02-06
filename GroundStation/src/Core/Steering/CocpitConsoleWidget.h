#ifndef COCPITCONSOLEWIDGET_H
#define COCPITCONSOLEWIDGET_H

#include <QWidget>

namespace Ui {
class CocpitConsoleWidget;
}

class CocpitConsoleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CocpitConsoleWidget(QWidget *parent = 0);
    ~CocpitConsoleWidget();

private:
    Ui::CocpitConsoleWidget *ui;
};

#endif // COCPITCONSOLEWIDGET_H

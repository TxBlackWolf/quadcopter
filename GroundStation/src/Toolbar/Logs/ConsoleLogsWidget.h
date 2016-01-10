#ifndef CONSOLELOGSWIDGET_H
#define CONSOLELOGSWIDGET_H

#include <QWidget>

namespace Ui {
class ConsoleLogsWidget;
}

class ConsoleLogsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConsoleLogsWidget(QWidget *parent = 0);
    ~ConsoleLogsWidget();

private:
    Ui::ConsoleLogsWidget *ui;
};

#endif // CONSOLELOGSWIDGET_H

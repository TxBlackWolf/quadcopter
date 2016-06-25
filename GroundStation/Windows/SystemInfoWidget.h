////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       07.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SYSTEMINFOWIDGET_H
#define SYSTEMINFOWIDGET_H

#include <QWidget>

namespace Ui {
    class SystemInfoWidget;
}

class SystemInfoWidget : public QWidget {
    Q_OBJECT

public:
    explicit SystemInfoWidget(QWidget* parent = nullptr);
    virtual ~SystemInfoWidget();

private:
    Ui::SystemInfoWidget* m_ui;
};

#endif

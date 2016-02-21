////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.01.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GOOGLEMAPSVIEW_H
#define GOOGLEMAPSVIEW_H

#include <QWidget>

namespace Ui {
    class GoogleMapsView;
}

class GoogleMapsView : public QWidget {
    Q_OBJECT

public:
    explicit GoogleMapsView(QWidget* parent = nullptr);
    virtual ~GoogleMapsView();

private:
    Ui::GoogleMapsView* m_ui;
};

#endif

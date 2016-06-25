////////////////////////////////////////////////////////////////////////////////////////////////
///
/// @file
/// @author     Kuba Sejdak
/// @date       21.02.2016
///
/// @copyright  This file is a part of SkyViper project. All rights reserved.
///
////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef FPVVIEW_H
#define FPVVIEW_H

#include <QWidget>

namespace Ui {
    class FPVView;
}

class FPVView : public QWidget {
    Q_OBJECT

public:
    explicit FPVView(QWidget* parent = nullptr);
    virtual ~FPVView();

private:
    Ui::FPVView* m_ui;
};

#endif

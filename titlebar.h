/*
The MIT License (MIT)

Copyright © 2018-2020 Antonio Dias

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "iconwidget.h"
#include "titlewidget.h"
#include "captionbutton.h"

class TitleBar : public QFrame
{
    Q_OBJECT
public:
    explicit TitleBar(qreal pixel_ratio, QWidget *parent = nullptr);

signals:
    void showMinimized();
    void showNormal();
    void showMaximized();
    void closeWindow();

public slots:
    void setTitle(const QString &title);
    void setIcon(const QPixmap &icon);
    void setActive(bool active);
    void setMaximized(bool maximized);

private:
    IconWidget *iconwidget;
    TitleWidget *titlewidget;
    CaptionButton *minbtn;
    CaptionButton *restorebtn;
    CaptionButton *maxbtn;
    CaptionButton *clsbtn;
    QString style;
    bool m_active;
    bool m_is_maximized;
};

#endif // TITLEBAR_H

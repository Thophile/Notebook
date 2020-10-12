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

#include "mainwindow.h"

#include <QListWidget>

MainWindow::MainWindow(QWidget *parent) : QGoodWindow(parent)
{
#ifdef Q_OS_WIN
    title_bar = new TitleBar(pixelRatio(), this);

    main_ui = new MainUi(this);


    frame = new QFrame(this);


    m_frame_style = QString("QFrame {background-color: %0; border: %1;}");

    m_color_str = "#FFFFFF";

    frame->setStyleSheet(m_frame_style.arg(m_color_str).arg("none"));


    QVBoxLayout *layout = new QVBoxLayout(frame);
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(title_bar);
    layout->addWidget(main_ui, 1);

    setCentralWidget(frame);

    setMargins(qRound(30 * pixelRatio()), qRound(30 * pixelRatio()), 0, qRound(36 * 3 * pixelRatio()));

    connect(title_bar, &TitleBar::showMinimized, this, &MainWindow::showMinimized);
    connect(title_bar, &TitleBar::showNormal, this, &MainWindow::showNormal);
    connect(title_bar, &TitleBar::showMaximized, this, &MainWindow::showMaximized);
    connect(title_bar, &TitleBar::closeWindow, this, &MainWindow::close);

    connect(this, &MainWindow::windowTitleChanged, this, [=](const QString &title){
        title_bar->setTitle(title);
    });

    connect(this, &MainWindow::windowIconChanged, this, [=](const QIcon &icon){
        if (!icon.isNull())
            title_bar->setIcon(icon.pixmap(GetSystemMetrics(SM_CXICON), GetSystemMetrics(SM_CYICON)));
    });
#else
    QString m_frame_style = QString("QFrame {background-color: #303030;}");

    QFrame *frame = new QFrame(this);
    frame->setStyleSheet(m_frame_style);

    setCentralWidget(frame);
#endif
    resize(qRound(640 * pixelRatio()), qRound(480 * pixelRatio()));

    move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());

#ifdef Q_OS_WIN

    m_color_str = "#222222";

    frame->setStyleSheet(m_frame_style.arg(m_color_str).arg(isMaximized() ? "none" : "none"));

#endif

    QPixmap img(":/icons/placeholder.ico");

    setWindowIcon(img);

    setWindowTitle("Caesar");


}

MainWindow::~MainWindow()
{

}

bool MainWindow::event(QEvent *event)
{
#ifdef Q_OS_WIN
    switch (event->type())
    {
    case QEvent::Show:
    case QEvent::WindowStateChange:
    {
        frame->setStyleSheet(m_frame_style.arg(m_color_str).arg(isMaximized() ? "none" : "none"));

        title_bar->setMaximized(isMaximized());

        break;
    }
    case QEvent::WindowActivate:
    {
        frame->setStyleSheet(m_frame_style.arg(m_color_str).arg(isMaximized() ? "none" : "none"));

        title_bar->setActive(true);

        break;
    }
    case QEvent::WindowDeactivate:
    {
        //Style for out of focus
        frame->setStyleSheet(m_frame_style.arg(m_color_str).arg(isMaximized() ? "none" : "none"));

        title_bar->setActive(false);

        break;
    }
    case QEvent::Resize:
    case QEvent::Hide:
    case QEvent::Move:
    case QEvent::KeyPress:
    case QEvent::KeyRelease:
    case QEvent::MouseMove:
    case QEvent::Wheel:
//        qDebug() << __FUNCTION__ << event;
        break;
    default:
        break;
    }
#endif

    return QGoodWindow::event(event);
}

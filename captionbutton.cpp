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

#include "captionbutton.h"

CaptionButton::CaptionButton(IconType type, qreal pixel_ratio, QWidget *parent) : QWidget(parent)
{
    m_type = type;
    m_pixel_ratio = pixel_ratio;
    m_is_pressed = false;

    setAttribute(Qt::WA_Hover);

    setColors();
    drawIcons();
}

void CaptionButton::drawIcons()
{
    int w = qCeil(10 * m_pixel_ratio);

    if (w <= 10)
        w = 10;
    else if (w <= 12)
        w = 12;
    else
        w = 15;

    switch (m_type)
    {
        case IconType::Minimize:
        {

            m_active_icon = QIcon(":/icons/minimize-active-light.ico").pixmap(w, 1);
            m_inactive_icon = QIcon(":/icons/minimize-inactive-light.ico").pixmap(w, 1);

            break;
        }
        case IconType::Restore:
        {

            m_active_icon = QIcon(":/icons/restore-active-light.ico").pixmap(w, w);
            m_inactive_icon = QIcon(":/icons/restore-inactive-light.ico").pixmap(w, w);

            break;
        }
        case IconType::Maximize:
        {

            m_active_icon = QIcon(":/icons/maximize-active-light.ico").pixmap(w, w);
            m_inactive_icon = QIcon(":/icons/maximize-inactive-light.ico").pixmap(w, w);

            break;
        }
        case IconType::Close:
        {

            m_active_icon = QIcon(":/icons/close-active-light.ico").pixmap(w, w);
            m_inactive_icon = QIcon(":/icons/close-inactive-light.ico").pixmap(w, w);

            break;
        }
    }
}

void CaptionButton::setColors()
{

    if (m_type == IconType::Close)
    {
        m_normal = QColor("transparent");
        m_hover = QColor("#F00000");
        m_pressed = QColor("#F1707A");
    }
    else
    {
        m_normal = QColor("transparent");
        m_hover = QColor("#505050");
        m_pressed = QColor("#3F3F3F");
    }

    m_current_color = m_normal;

    repaint();
}



void CaptionButton::setActive(bool active_window)
{
    if (active_window)
    {

        m_current_icon = m_active_icon;

        m_last_icon = m_active_icon;
    }
    else
    {
        m_current_icon = m_inactive_icon;
        m_last_icon = m_current_icon;
    }

    repaint();
}

void CaptionButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);

    painter.fillRect(rect(), m_current_color);

    int w = qCeil(10 * m_pixel_ratio);

    if (w <= 10)
        w = 10;
    else if (w <= 12)
        w = 12;
    else
        w = 15;

    int h = m_type != IconType::Minimize ? w : 1;

    QRect target_rect;
    target_rect = m_current_icon.rect();
    target_rect.setSize(QSize(w, h));
    target_rect = QRect(rect().center() - target_rect.center(), target_rect.size());

    painter.drawPixmap(target_rect, m_current_icon);
}

bool CaptionButton::event(QEvent *event)
{
    switch (event->type())
    {
    case QEvent::HoverEnter:
    {
        m_last_icon = m_current_icon;

        m_current_icon = m_active_icon;

        m_current_color = m_hover;

        repaint();

        break;
    }
    case QEvent::HoverLeave:
    {
        m_current_icon = m_last_icon;

        m_current_color = m_normal;

        repaint();

        break;
    }
    case QEvent::MouseMove:
    {
        if (m_is_pressed && underMouse())
        {

            m_current_color = m_pressed;

            repaint();
        }
        else if (underMouse())
        {

            m_last_icon = m_active_icon;

            m_current_color = m_hover;

            repaint();
        }
        else
        {

            m_last_icon = m_active_icon;

            m_current_color = m_normal;

            repaint();
        }

        break;
    }
    case QEvent::MouseButtonPress:
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (e->button() != Qt::LeftButton)
            break;

        m_is_pressed = true;

        m_current_color = m_pressed;

        repaint();

        break;
    }
    case QEvent::MouseButtonRelease:
    {
        QMouseEvent *e = static_cast<QMouseEvent*>(event);

        if (e->button() != Qt::LeftButton)
            break;

        m_is_pressed = false;

        m_current_color = m_normal;

        repaint();

        if (underMouse())
            emit clicked();

        break;
    }
    default:
        break;
    }

    return QWidget::event(event);
}

bool CaptionButton::underMouse()
{
    return (rect().contains(mapFromGlobal(QCursor::pos())));
}

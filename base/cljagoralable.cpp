#include "cljagoralable.h"
#include <QPainter>
#include <QPaintEvent>

CLJAgoraLable::CLJAgoraLable(const QString &text, QWidget *parent, Qt::WindowFlags f)
    :QLabel(text,parent,f)
{

}

CLJAgoraLable::~CLJAgoraLable()
{

}

void CLJAgoraLable::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
//    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.setPen(Qt::NoPen);
    QBrush brush(QColor("#00000000"));
    painter.setBrush(brush);
    painter.drawRect(event->rect());
    {
        QBrush brush(QColor("#5000FF00"));
        painter.setBrush(brush);
        int r = event->rect().width() / 4;
        painter.drawRoundedRect(event->rect(),r,r,Qt::AbsoluteSize);
    }
    {
        QPen pen(QColor("#ff0000"));
        pen.setWidth(1);
        painter.setPen(pen);
        QRectF rect = event->rect();
        painter.drawText(rect,this->text(),QTextOption(Qt::AlignCenter));
    }
    return;
}


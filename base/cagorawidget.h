#ifndef CAGORAWIDGET_H
#define CAGORAWIDGET_H
#include <QWidget>

class CAgoraWidget
{
public:
    CAgoraWidget();
    ~CAgoraWidget();

    void doAdjuest();

   QWidget *m_widget;
   WId m_id;
};

#endif // CAGORAWIDGET_H

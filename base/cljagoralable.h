#ifndef CLJAGORALABLE_H
#define CLJAGORALABLE_H
#include <QLabel>

class CLJAgoraLable : public QLabel
{
    Q_OBJECT
public:
    explicit CLJAgoraLable(const QString &text, QWidget *parent=Q_NULLPTR, Qt::WindowFlags f=Qt::WindowFlags());
   ~CLJAgoraLable();

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CLJAGORALABLE_H

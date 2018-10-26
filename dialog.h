#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>

#include "cagoraobject.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void SetAgoraPublishLayout();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed);
    void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed);
    void onUserOffline(uid_t uid, int reason);


private:
    void doAppenUid(uid_t uid);

private:
    Ui::Dialog *ui;
    std::list<unsigned int> m_lstUid;
    QMap<uid_t,QWidget*> m_agoraViewMap;
};

#endif // DIALOG_H

#include "dialog.h"
#include "ui_dialog.h"
#include "cagoraobject.h"
#include "dclog.h"
#include "cparamutils.h"
#ifdef Q_OS_MAC
#include "AgoraBase.h"
#include "cagorawidget.h"
#include <QPainter>
#include <QPaintEvent>
#endif
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
  ,gridLayout(NULL)
{
    ui->setupUi(this);

//    this->setStyleSheet("background: #00000000;");
//    this->setAttribute(Qt::WA_TranslucentBackground);

//    this->setStyleSheet("background: #00000000;");
//    ui->widget->setAttribute(Qt::WA_TranslucentBackground,false);


    CAgoraObject::getInstance();
}

Dialog::~Dialog()
{
    on_pushButton_2_clicked();
    delete ui;
}

void Dialog::SetAgoraPublishLayout()
{
    return updateViewLayoutAgora();
//    int user_count = m_lstUid.size();
    int user_count = m_agoraViewMap.size();
    if (user_count == 0 )
        return;

    printf ("SSSS============== user_count=%d\n",user_count);
    //return;

    LiveTranscoding config;
    config.audioSampleRate = AUDIO_SAMPLE_RATE_44100;
    config.audioChannels = 2;
    config.width = 1280;//;
    config.height = 720;//;
    config.videoFramerate = 15;
    config.videoBitrate = 1500;
    config.videoGop = 20;
    config.userCount = user_count;
    config.watermark = nullptr;
    config.videoCodecProfile = VIDEO_CODEC_PROFILE_HIGH;
    config.transcodingUsers = new TranscodingUser[config.userCount];
    config.lowLatency = true;
    //config.backgroundColor = 0x262626;
//    auto iter = m_lstUid.begin();

    int row = 1;
    int col = 1;

    bool find = false;
    for (; col <= 5; ++col){
        for (; row <= col; ++row){
            if (user_count <= row*col && user_count > col*(row - 1)){
                find = true;
                break;
            }
        }
        if (find) break;
        row = 1;
    }

    int w = config.width / col;
    int h = config.height / row;

    QMapIterator<uid_t,QWidget*>iter(m_agoraViewMap);

    int index = 0;
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            index = i*col + j;
            if (index >= user_count){
                break;
            }
            if(!iter.hasNext())
            {
                break;
            }
            iter.next();
            config.transcodingUsers[index].uid = iter.key();

            config.transcodingUsers[index].x = j*w;
            config.transcodingUsers[index].y = i*h;
            config.transcodingUsers[index].width  = w;
            config.transcodingUsers[index].height = h;
            config.transcodingUsers[index].zOrder = 1;
//            if (iter != m_lstUid.end()){
//                config.transcodingUsers[index].uid = *iter;
//                ++iter;
//            }
        }

        if (index >= user_count){
            break;
        }
    }

//    if (!waterMarkUrl.IsEmpty() && false){
//        if (water_type == WATERMARK_LOCAL_FILE)
//            CAgoraObject::GetAgoraObject()->SetWaterMark(waterMarkUrl, rcWaterMark);
//        else if (water_type == WATERMARK_IMAGE_URL){
//            config.watermark = new RtcImage;
//            config.watermark->url = new char[waterMarkUrl.GetLength()];
//#ifdef UNICODE
//            CHAR szURL[MAX_PATH];

//            ::WideCharToMultiByte(CP_ACP, 0, waterMarkUrl.GetBuffer(0), -1, szURL, MAX_PATH, NULL, NULL);
//            config.watermark->url = szURL;
//#else
//            config.watermark->url = lpURL;
//#endif
//            config.watermark->x = rcWaterMark.left;
//            config.watermark->y = rcWaterMark.left;
//            config.watermark->width = rcWaterMark.Width();
//            config.watermark->height = rcWaterMark.Height();
//        }
//    }

    IRtcEngine *lpRtcEngine = CAgoraObject::getInstance()->m_lpAgoraEngine;
    //        CAgoraObject::GetAgoraObject()->SetLiveTranscoding(config);
    lpRtcEngine->setLiveTranscoding(config);

    if (config.transcodingUsers)
    {
        delete[] config.transcodingUsers;
    }

    updateViewLayoutAgora();
}

void Dialog::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    QBrush brush(QColor("#80000080"));
//    painter.setBrush(brush);
//    painter.drawRect(event->rect());
//    painter.drawLine(event->rect().topLeft(),event->rect().bottomRight());
}

void Dialog::on_pushButton_clicked()
{
//    CString strChannelName("lj2018");
    CAgoraObject *m_lpAgoraObject = CAgoraObject::getInstance();
    connect(&m_lpAgoraObject->m_EngineEventHandler,SIGNAL(sigJoinChannelSuccess(const char*,uid_t,int)),
            this,SLOT(onJoinChannelSuccess(const char*,uid_t,int))) ;
    connect(&m_lpAgoraObject->m_EngineEventHandler,SIGNAL(sigFirstRemoteVideoDecoded(uid_t,int,int,int)),
            this,SLOT(onFirstRemoteVideoDecoded(uid_t,int,int,int))) ;
    connect(&m_lpAgoraObject->m_EngineEventHandler,SIGNAL(sigUserOffline(uid_t,int)),
            this,SLOT(onUserOffline(uid_t,int))) ;
    IRtcEngine *lpRtcEngine = CAgoraObject::getInstance()->m_lpAgoraEngine;

    lpRtcEngine->enableVideo();
    lpRtcEngine->setChannelProfile(agora::rtc::CHANNEL_PROFILE_LIVE_BROADCASTING);
    lpRtcEngine->setClientRole(agora::rtc::CLIENT_ROLE_BROADCASTER);
////        agora_engine->setClientRole(agora::rtc::CLIENT_ROLE_AUDIENCE);
    m_lpAgoraObject->enableLocalCameara(true);// stop agora camera capture
    m_lpAgoraObject->enableLocalRender(true); // stop agora local render
    lpRtcEngine->enableLocalVideo(true);
    lpRtcEngine->disableAudio();
    lpRtcEngine->setVideoProfile(VIDEO_PROFILE_LANDSCAPE_720P, false);
    lpRtcEngine->startPreview();
    CAgoraObject::getInstance()->JoinChannel(CParamUtils::getChannelName().toLatin1(),CParamUtils::getUserId());
}

void Dialog::on_pushButton_2_clicked()
{
    IRtcEngine *lpRtcEngine = CAgoraObject::getInstance()->m_lpAgoraEngine;
//    lpRtcEngine->removePublishStreamUrl("rtmp://push-test.yunxuetang.com.cn/app90/4f03d5dd6c984bd2b105490faa8955c4");
    CAgoraObject::getInstance()->LeaveCahnnel();
    lpRtcEngine->stopPreview();
}

void Dialog::onJoinChannelSuccess(const char *channel, uid_t uid, int elapsed)
{
    DC_LOG_FUNCTION;
    DC_LOG_INFO_VALUE(channel);
    DC_LOG_INFO_VALUE(uid);
    DC_LOG_INFO_VALUE(elapsed);
    doAppenUid(uid);
}

void Dialog::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
    DC_LOG_FUNCTION;
    DC_LOG_INFO_VALUE(height);
    DC_LOG_INFO_VALUE(uid);
    DC_LOG_INFO_VALUE(width);

//    m_lstUid.emplace_back(uid);
//    SetAgoraPublishLayout();
    doAppenUid(uid);
}

void Dialog::onUserOffline(uid_t uid, int reason)
{
    DC_LOG_FUNCTION;
    DC_LOG_INFO_VALUE(reason);
    DC_LOG_INFO_VALUE(uid);

    if(m_agoraViewMap.contains(uid))
    {
        QWidget *widget = m_agoraViewMap.value(uid);
        m_agoraViewMap.remove(uid);
        widget->deleteLater();
        SetAgoraPublishLayout();
    }

}

void Dialog::doAppenUid(uid_t uid)
{
    if(m_agoraViewMap.contains(uid))
    {
        return;
    }
    if(uid == CParamUtils::getUserId())
    {
        return;
    }


    {
//        CAgoraWidget obj;
//        QWidget *widget = obj.m_widget;
//        widget
//        widget->setStyleSheet("background: #80000080;");
//        加了tool 貌似lineedit无法正常输入，需要tab切换窗口后正常 mac
//                this->setAttribute(Qt::WA_TranslucentBackground);
//        widget->show();
    }

    CAgoraWidget obj;
    QWidget *widget = obj.m_widget;
//    widget->setSizePolicy(QSizePolicy::Expanding,
//                QSizePolicy::Expanding);

    m_agoraViewMap.insert(uid,widget);

    DC_LOG_INFO_VALUE(uid);
    DC_LOG_INFO_VALUE(CParamUtils::getUserId());
#ifdef Q_OS_WIN
        VideoCanvas canvas(reinterpret_cast<agora::rtc::view_t>(obj.m_id),RENDER_MODE_FIT, uid);
#else
        VideoCanvas canvas(reinterpret_cast<agora::view_t>(obj.m_id),RENDER_MODE_FIT, uid);
#endif

        IRtcEngine *lpRtcEngine = CAgoraObject::getInstance()->m_lpAgoraEngine;
    if(uid == CParamUtils::getUserId())
    {
        int res = lpRtcEngine->setupLocalVideo(canvas);
        DC_LOG_INFO_VALUE(res);
    }
    else
    {
        int res = lpRtcEngine->setupRemoteVideo(canvas);
        DC_LOG_INFO_VALUE(res);
    }

//    {
//        CAgoraWidget obj;
//        QWidget *widget = obj.m_widget;
//        VideoCanvas canvas(reinterpret_cast<agora::view_t>(obj.m_id),RENDER_MODE_FIT, uid);
//        int res = lpRtcEngine->setupRemoteVideo(canvas);
//        DC_LOG_INFO_VALUE(res);
//        widget->show();
//    }

    SetAgoraPublishLayout();
}

void Dialog::updateViewLayoutAgora()
{
    if(gridLayout)
    {
        gridLayout->deleteLater();
        gridLayout = NULL;
    }
    gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);
    gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    ui->hLayout->addLayout(gridLayout);

    int viewCount = m_agoraViewMap.count();
    QMapIterator<uid_t,QWidget*>iter(m_agoraViewMap);

    int col_number = 1;
    if (viewCount >= 1 && viewCount <= 4)
    {
        col_number = 2;
    }
    else if (viewCount >= 5 && viewCount <= 9)
    {
        col_number = 3;
    }
    else
    {
        col_number = 4;

    }



    int index = 0;
    while(iter.hasNext())
    {
        iter.next();
        int row, col;
        row = index / col_number;
        col = index % col_number;

        qDebug() << "current row = " << row << " col = " << col;
        gridLayout->addWidget(iter.value(), row, col, 1, 1);
        gridLayout->setRowStretch(row, 1);
        gridLayout->setColumnStretch(col, 1);




        index++;
    }

}

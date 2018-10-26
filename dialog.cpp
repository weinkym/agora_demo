#include "dialog.h"
#include "ui_dialog.h"
#include "cagoraobject.h"
#include "dclog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);


}

Dialog::~Dialog()
{
    CAgoraObject::getInstance()->LeaveCahnnel();
    delete ui;
}

void Dialog::SetAgoraPublishLayout()
{
    int user_count = m_lstUid.size();
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
    config.userCount = m_lstUid.size();
    config.watermark = nullptr;
    config.videoCodecProfile = VIDEO_CODEC_PROFILE_HIGH;
    config.transcodingUsers = new TranscodingUser[config.userCount];
    config.lowLatency = true;
    //config.backgroundColor = 0x262626;
    auto iter = m_lstUid.begin();

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

    int index = 0;
    for (int i = 0; i < row; ++i){
        for (int j = 0; j < col; ++j){
            index = i*col + j;
            if (index >= user_count){
                break;
            }
            config.transcodingUsers[index].x = j*w;
            config.transcodingUsers[index].y = i*h;
            config.transcodingUsers[index].width  = w;
            config.transcodingUsers[index].height = h;
            config.transcodingUsers[index].zOrder = 1;
            if (iter != m_lstUid.end()){
                config.transcodingUsers[index].uid = *iter;
                ++iter;
            }
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

    //m_lpAgoraObject->SetLogFilePath(NULL);
    //m_lpAgoraObject->SetMsgHandlerWnd(GetSafeHwnd());
    lpRtcEngine->setChannelProfile(CHANNEL_PROFILE_LIVE_BROADCASTING);
    lpRtcEngine->enableVideo();
    lpRtcEngine->setClientRole(CLIENT_ROLE_BROADCASTER);



//    agora::rtc::view_t v = reinterpret_cast<agora::rtc::view_t>(view);
//#endif
//    VideoCanvas canvas(v, RENDER_MODE_FIT, uid);

    VideoCanvas vc;
    vc.uid = 0;
    vc.view = reinterpret_cast<agora::rtc::view_t>(ui->widget->winId());
    vc.renderMode = RENDER_MODE_TYPE::RENDER_MODE_ADAPTIVE;
    //cancel setVideoProfile bitrate since version 2.1.0
    lpRtcEngine->setVideoProfile(VIDEO_PROFILE_LANDSCAPE_720P, false);
    lpRtcEngine->setupLocalVideo(vc);
    lpRtcEngine->startPreview();

    CAgoraObject::getInstance()->JoinChannel(0,0);
//    bool transcodingEnabled = false;
    bool transcodingEnabled = true;
    int ret = lpRtcEngine->addPublishStreamUrl("rtmp://push-test.yunxuetang.com.cn/app90/4f03d5dd6c984bd2b105490faa8955c4", transcodingEnabled);
    DC_LOG_INFO_VALUE(ret);
}

void Dialog::on_pushButton_2_clicked()
{
    IRtcEngine *lpRtcEngine = CAgoraObject::getInstance()->m_lpAgoraEngine;
    lpRtcEngine->removePublishStreamUrl("rtmp://push-test.yunxuetang.com.cn/app90/4f03d5dd6c984bd2b105490faa8955c4");
    CAgoraObject::getInstance()->LeaveCahnnel();
}

void Dialog::onJoinChannelSuccess(const char *channel, uid_t uid, int elapsed)
{
    DC_LOG_FUNCTION;
    DC_LOG_INFO_VALUE(channel);
    DC_LOG_INFO_VALUE(uid);
    DC_LOG_INFO_VALUE(elapsed);
    m_lstUid.emplace_back(uid);
    SetAgoraPublishLayout();
}

void Dialog::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
    DC_LOG_FUNCTION;
    DC_LOG_INFO_VALUE(height);
    DC_LOG_INFO_VALUE(uid);
    DC_LOG_INFO_VALUE(width);

    m_lstUid.emplace_back(uid);
    SetAgoraPublishLayout();
}

void Dialog::onUserOffline(uid_t uid, int reason)
{
    DC_LOG_FUNCTION;
    DC_LOG_INFO_VALUE(reason);
    DC_LOG_INFO_VALUE(uid);

    m_lstUid.remove(uid);
    SetAgoraPublishLayout();
}

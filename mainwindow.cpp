#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agorartcengine.h"
#include "clogsetting.h"
#include "cparamutils.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    AgoraRtcEngine::GetInstance()->leaveChannel();
}

void MainWindow::on_pushButton_clicked()
{
    DC_LOG_FUNCTION;
    bool ok = AgoraRtcEngine::GetInstance()->InitEngine("e757a06cbc334f0abf545b8705dd1669");
    DC_LOG_INFO_VALUE(ok);
    if(!ok)
    {
        return;
    }

    int res = 0;
    AgoraRtcEngine* agora_engine = AgoraRtcEngine::GetInstance();
    agora_engine->enableVideo(true);
    agora_engine->setChannelProfile(agora::rtc::CHANNEL_PROFILE_LIVE_BROADCASTING);
    agora_engine->setClientRole(agora::rtc::CLIENT_ROLE_BROADCASTER);
    agora_engine->enableLocalCameara(false);// stop agora camera capture
    agora_engine->enableLocalRender(false); // stop agora local render
    agora_engine->keepPreRotation(false);
#ifdef Q_OS_MAC
    agora_engine->getRtcEngine()->setLogFile("/Users/miaozw/Movies/agora.log");
#endif
    void* p = AgoraRtcEngine::GetInstance()->AgoraVideoObserver_Create();
    DC_LOG_INFO(p == NULL ?"F":"T");

    AgoraRtcEngine::GetInstance()->AgoraAudioObserver_Create();


//    agora_engine->EnableWebSdkInteroperability(service_data->enableWebSdkInteroperability);
    agora_engine->setVideoProfileEx(1280,720, 20, 2400);
    agora_engine->setAudioProfile(44100, 2, 1024 * 4);//agora_pcm_encoder



    res = agora_engine->joinChannel("",CParamUtils::getChannelName().toLatin1().data(),CParamUtils::getUserId());
    DC_LOG_INFO_VALUE(res);


//    添加推流地址
//            m_rtcEngine->addPublishStreamUrl(url, true);


    res = agora_engine->AddPublishStreamUrl(CParamUtils::getRTMPUrl().toLatin1().data(),true);
   DC_LOG_INFO_VALUE(res);


   //CDN 转码设置
   LiveTranscoding config;
   config.audioSampleRate = AUDIO_SAMPLE_RATE_44100;
   config.audioChannels = 2;
   //config.audioBitrate
   config.width = 1280;
   config.height = 720;
   config.videoFramerate = 30;
   config.userCount = 1;  //如果 userCount > 1，则需要为每个 transcodingUsers 分别设置布局
   config.videoCodecProfile = VIDEO_CODEC_PROFILE_HIGH;

   //分配用户视窗的合图布局
   config.transcodingUsers = new TranscodingUser[config.userCount];
   config.transcodingUsers[0].uid = CParamUtils::getUserId(); //uid 应和 joinChannel() 输入的 uid 保持一致
   config.transcodingUsers[0].x = 0;
   config.transcodingUsers[0].audioChannel = 2;
   config.transcodingUsers[0].y = 0;
   config.transcodingUsers[0].width = config.width / 2;
   config.transcodingUsers[0].height = config.height;

   agora_engine->SetLiveTranscoding(config);

     if (config.transcodingUsers)
       {
          delete[] config.transcodingUsers;
       }


}

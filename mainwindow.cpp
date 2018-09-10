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

    int res = agora_engine->joinChannel("",CParamUtils::getChannelName().toLatin1().data(),CParamUtils::getUserId());
    DC_LOG_INFO_VALUE(res);
}

#ifndef AGORARTCENGINE_H
#define AGORARTCENGINE_H

#include <IAgoraRtcEngine.h>
#include <IAgoraMediaEngine.h>
#include <string>
#include "ljextendaudioframeobserver.h"
#include "ljextendvideoframeobserver.h"

#ifndef Q_OS_MAC
#include <windows.h>
#include <IAgoraRtcEngine2.h>
#include <memory>
#endif

using namespace agora::rtc;

class AgoraRtcEngine
{
   // Q_OBJECT
public:
    explicit AgoraRtcEngine();
    ~AgoraRtcEngine();
    static AgoraRtcEngine* GetInstance();
    static void ReleaseInstance();

    bool InitEngine(std::string appid);

    bool setClientRole(CLIENT_ROLE_TYPE role, char * lpPermissionKey = NULL);
    int  setChannelProfile(CHANNEL_PROFILE_TYPE profile);

    int enableVideo(bool enabled);
    bool enableLocalRender(bool bEnable);
    int muteLocalAudioStream(bool muted);
    int  setLocalVideoMirrorMode(VIDEO_MIRROR_MODE_TYPE mirrorMode);
    void startPreview();
    void stopPreview();

    int joinChannel(const std::string& key, const std::string& channel, unsigned uid);
    int leaveChannel();

    bool  keepPreRotation(bool bRotate);
    bool  setVideoProfileEx(int nWidth, int nHeight, int nFrameRate, int nBitRate);
    bool  enableLocalCameara(bool bEnable);

    void* AgoraVideoObserver_Create();
    void  AgoraVideoObserver_Destroy(void* data);
    bool  AgoraVideoObserver_Encode(void* data, struct encoder_frame* frame,
        struct encoder_packet* packet, bool *receive_packet);

    bool setAudioProfile(int nSampleRate, int nChannels, int nSamplesPerCall);
    bool setExternalAudioSource(bool bEnabled, int nSampleRate, int nChannels);
    bool enableExtendPlayDevice(bool bEnable);

    void* AgoraAudioObserver_Create();
    void  AgoraAudioObserver_Destroy(void* data);
    bool  AgoraAudioObserver_Encode(void* data, struct encoder_frame* frame,
        struct encoder_packet* packet, bool *receive_packet);

    int ConfigPublisher(const PublisherConfiguration& config);
    int SetVideoCompositingLayout(const VideoCompositingLayout& sei);
    int ClearVideoCompositingLayout();

    int AddPublishStreamUrl(const char *url, bool transcodingEnabled);
    int RemovePublishStreamUrl(const char *url);
    int SetLiveTranscoding(const LiveTranscoding &transcoding);

    int EnableWebSdkInteroperability(bool enabled);
    //设备
    int getRecordingDeviceVolume();
    int getPalyoutDeviceVolume();
    int setRecordingDeviceVolume(int volume);
    int setPalyoutDeviceVolume(int volume);
    int testMicrophone(bool start, int interval);
    int testSpeaker(bool start);

//	obs_service_t* agoraService;
    bool bInit = false;
    int setupRemoteVideo(unsigned int uid, void* view);
    agora::rtc::IRtcEngine* getRtcEngine() {return m_rtcEngine.get();}

    int agora_fps = 15;
    int agora_out_cx = 640;
    int agora_out_cy = 360;
    int agora_video_bitrate = 500;
    void joinedChannelSuccess(const char* channel, unsigned int uid, int elapsed);

//public slots:
private:
    friend class AgoraRtcEngineEvent;
private:
    std::unique_ptr<agora::rtc::IRtcEngine> m_rtcEngine;
    std::unique_ptr<agora::rtc::IRtcEngineEventHandler> m_eventHandler;
    static char* m_appid;
    static AgoraRtcEngine* m_agoraEngine;

    std::unique_ptr<LJExtendVideoFrameObserver> m_videoObserver;
    std::unique_ptr<LJExtendAudioFrameObserver> m_audioObserver;
};

#endif // AGORARTCENGINE_H

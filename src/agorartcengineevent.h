#ifndef AGORARTCENGINEEVENT_H
#define AGORARTCENGINEEVENT_H

#include "AgoraBase.h"
#include "agorartcengine.h"

class AgoraRtcEngineEvent : public agora::rtc::IRtcEngineEventHandler
{
    AgoraRtcEngine& m_engine;
public:
    AgoraRtcEngineEvent(AgoraRtcEngine& engine);

    virtual void onVideoStopped() override;

    virtual void onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed) override;

    virtual void onLeaveChannel(const RtcStats& stats) override;

    virtual void onError(int err, const char* msg) override;

    virtual void onUserJoined(uid_t uid, int elapsed) override;

    virtual void onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason) override;

    virtual void onFirstLocalVideoFrame(int width, int height, int elapsed) override;

    virtual void onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed) override;

    virtual void onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed) override;

};

#endif // AGORARTCENGINEEVENT_H

#include "agorartcengineevent.h"
#include "clogsetting.h"

AgoraRtcEngineEvent::AgoraRtcEngineEvent(AgoraRtcEngine &engine)
    :agora::rtc::IRtcEngineEventHandler()
    ,m_engine(engine)
{

}

void AgoraRtcEngineEvent::onVideoStopped()
{

}

void AgoraRtcEngineEvent::onJoinChannelSuccess(const char *channel, uid_t uid, int elapsed)
{

}

void AgoraRtcEngineEvent::onLeaveChannel(const RtcStats &stats)
{

}

void AgoraRtcEngineEvent::onError(int err, const char *msg)
{
    DC_LOG_INFO_VALUE(err);
    DC_LOG_INFO_VALUE(msg);
}

void AgoraRtcEngineEvent::onUserJoined(uid_t uid, int elapsed)
{

}

void AgoraRtcEngineEvent::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{

}

void AgoraRtcEngineEvent::onFirstLocalVideoFrame(int width, int height, int elapsed)
{

}

void AgoraRtcEngineEvent::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{

}

void AgoraRtcEngineEvent::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed)
{

}

#include "cagoraeventhandler.h"

CAGEngineEventHandler::CAGEngineEventHandler()
{
    qRegisterMetaType< uid_t >("uid_t");
}

CAGEngineEventHandler::~CAGEngineEventHandler()
{

}

void CAGEngineEventHandler::onJoinChannelSuccess(const char *channel, uid_t uid, int elapsed)
{
    emit sigJoinChannelSuccess(channel,uid,elapsed);
}

void CAGEngineEventHandler::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
    emit sigFirstRemoteVideoDecoded( uid,  width,  height,  elapsed);
}

void CAGEngineEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
    emit sigUserOffline(uid,reason);
}

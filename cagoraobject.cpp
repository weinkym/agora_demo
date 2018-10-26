#include "cagoraobject.h"
#include "dclog.h"

CAgoraObject* CAgoraObject::m_instance = NULL;
IRtcEngine	*CAgoraObject::m_lpAgoraEngine = NULL;
CAGEngineEventHandler CAgoraObject::m_EngineEventHandler;

CAgoraObject::CAgoraObject(QObject *parent)
    :QObject(parent)
{

    m_lpAgoraEngine = createAgoraRtcEngine();

    RtcEngineContext ctx;
    ctx.eventHandler = &m_EngineEventHandler;
    ctx.appId = "e757a06cbc334f0abf545b8705dd1669";
    int res = m_lpAgoraEngine->initialize(ctx);
    DC_LOG_INFO_VALUE(res);
}

CAgoraObject::~CAgoraObject()
{

}

CAgoraObject *CAgoraObject::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new CAgoraObject;
    }

    return m_instance;
}

BOOL CAgoraObject::JoinChannel(LPCTSTR lpChannelName, UINT nUID, LPCSTR lpDynamicKey)
{
    int nRet = 0;

    LPCSTR lpStreamInfo = "{\"owner\":true,\"width\":640,\"height\":480,\"bitrate\":500}";
//#ifdef UNICODE
//    CHAR szChannelName[128];

//    ::WideCharToMultiByte(CP_ACP, 0, lpChannelName, -1, szChannelName, 128, NULL, NULL);
//    nRet = m_lpAgoraEngine->joinChannel(lpDynamicKey, szChannelName, lpStreamInfo, nUID);
//#else
//    nRet = m_lpAgoraEngine->joinChannel(lpDynamicKey, lpChannelName, lpStreamInfo, nUID);
//#endif

    nRet = m_lpAgoraEngine->joinChannel(lpDynamicKey, "lj2018", lpStreamInfo, nUID);

    DC_LOG_INFO_VALUE(nRet);
//    if (nRet == 0)
//        m_strChannelName = lpChannelName;

    return nRet == 0 ? TRUE : FALSE;
}

BOOL CAgoraObject::LeaveCahnnel()
{
    m_lpAgoraEngine->stopPreview();
    int nRet = m_lpAgoraEngine->leaveChannel();

    //	m_nSelfUID = 0;

    return nRet == 0 ? TRUE : FALSE;
}

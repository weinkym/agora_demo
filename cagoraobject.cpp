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

bool CAgoraObject::JoinChannel(const char*  lpChannelName, uint nUID, const char*  lpDynamicKey)
{
    int nRet = 0;
    nRet = m_lpAgoraEngine->joinChannel(lpDynamicKey, lpChannelName, 0, nUID);

    DC_LOG_INFO_VALUE(nRet);
    return nRet == 0 ? true : false;
}

bool CAgoraObject::LeaveCahnnel()
{
    m_lpAgoraEngine->stopPreview();
    int nRet = m_lpAgoraEngine->leaveChannel();

    //	m_nSelfUID = 0;

    return nRet == 0 ? true : false;
}

bool CAgoraObject::enableLocalCameara(bool bEnable)
{
#ifdef Q_OS_MAC
    agora::base::AParameter apm(m_lpAgoraEngine);
#else
    AParameter apm(*m_lpAgoraEngine.get());
#endif
    int ret = -1;
    if (!apm.get()) return false;

    if (!bEnable)
        ret = apm->setParameters("{\"che.video.local.camera_index\":1024}");
    else
        ret = apm->setParameters("{\"che.video.local.camera_index\":0}");

    apm.release();
    return ret == 0;
}

bool CAgoraObject::enableLocalRender(bool bEnable)
{
    int ret = -1;
#ifdef Q_OS_MAC
    agora::base::AParameter apm(m_lpAgoraEngine);
#else
    AParameter apm(m_lpAgoraEngine);
#endif
    if (bEnable)
        ret = apm->setParameters("{\"che.video.local.render\":true}");
    else
        ret = apm->setParameters("{\"che.video.local.render\":false}");
    apm.release();
    return ret == 0 ? true : false;
}

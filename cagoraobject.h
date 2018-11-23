#ifndef CAGORAOBJECT_H
#define CAGORAOBJECT_H

#include <QObject>
#include "cagoraeventhandler.h"
#include "IAgoraRtcEngine.h"

using namespace agora::rtc;

class CAgoraObject : public QObject
{
    Q_OBJECT
public:
    CAgoraObject(QObject *parent = nullptr);
    ~CAgoraObject();
    static CAgoraObject *getInstance();

    bool JoinChannel(const char* lpChannelName, uint nUID = 0, const char*  lpDynamicKey = NULL);
    bool LeaveCahnnel();
    bool  enableLocalCameara(bool bEnable);
    bool enableLocalRender(bool bEnable);

public:
    static CAgoraObject* m_instance;
    static CAGEngineEventHandler m_EngineEventHandler;
    static IRtcEngine *m_lpAgoraEngine;

};

#endif // CAGORAOBJECT_H

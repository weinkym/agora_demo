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

    BOOL JoinChannel(LPCTSTR lpChannelName, UINT nUID = 0, LPCSTR lpDynamicKey = NULL);
    BOOL LeaveCahnnel();

public:
    static CAgoraObject* m_instance;
    static CAGEngineEventHandler m_EngineEventHandler;
    static IRtcEngine *m_lpAgoraEngine;

};

#endif // CAGORAOBJECT_H

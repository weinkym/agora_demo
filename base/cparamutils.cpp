#include "cparamutils.h"
#include <QDateTime>

QString CParamUtils::getChannelName()
{
//    return "lj2018";
    return "lj";
}

uint CParamUtils::getUserId()
{
    static uint s_userId = qAbs(QTime::currentTime().msecsTo(QTime(0,0,0,0)));
    return s_userId;
}

QString CParamUtils::getRTMPUrl()
{
    return "rtmp://push-test.yunxuetang.com.cn/app90/98ebd61788174fc48a3663b5af7920f1";
}

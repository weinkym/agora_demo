#include "cparamutils.h"
#include <QDateTime>

QString CParamUtils::getChannelName()
{
    return "lj2018";
//    return "lj";
}

uint CParamUtils::getUserId()
{
    static uint s_userId = qAbs(QTime::currentTime().msecsTo(QTime(0,0,0,0)));
    return s_userId;
}

QString CParamUtils::getRTMPUrl()
{
    return "rtmp://push-test.yunxuetang.com.cn/app90/4f03d5dd6c984bd2b105490faa8955c4";
}

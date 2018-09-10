#ifndef DCLOG_H
#define DCLOG_H

#include <QDebug>
#include <QTime>
#include <QDateTime>
#include <QSize>
#include <QSizeF>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>

#include <iostream>
#include <type_traits>
#include <cstdint>
#include "dclogcontentdefine.h"

class DCFunLogHelper
{
public:
    DCFunLogHelper(const QString &funcionName);
    ~DCFunLogHelper();
private:
    QString m_functionInfo;
    QTime m_time;
};
#define DC_LOG_FUNCTION DCFunLogHelper logFuncHelper(Q_FUNC_INFO)


#define DC_LOG_DATE QDateTime::currentDateTime().toString("yyyyMMdd hh:mm:ss ")
#define DC_LOG_FILE_INFO (QString(" [file = ") + QString(__FILE__) + QString(" ,Line = ") + QString::number(__LINE__) + QString("]"))

#define DC_LOG_CONTENT(log) QString("===DCLIVE===")+DC_LOG_DATE+(log)+DC_LOG_FILE_INFO

#define C_CONTENT_DEBUG(log) qDebug()<<(DC_LOG_CONTENT(log))


#define DC_LOG_TEST(log) {C_CONTENT_DEBUG(log);}
#define DC_LOG_DEBUG(log) {C_CONTENT_DEBUG(log);}
#define DC_LOG_INFO(log) {C_CONTENT_DEBUG(log);}
#define DC_LOG_WARNING(log) {C_CONTENT_DEBUG(log);}
#define DC_LOG_ERROR(log) {C_CONTENT_DEBUG(log);}

#define DC_LOG_TEST_VALUE(value) DC_LOG_TEST(QString(#value"=%1").arg(dcCreateLogContent(value)))
#define DC_LOG_DEBUG_VALUE(value) DC_LOG_DEBUG(QString(#value"=%1").arg(dcCreateLogContent(value)))
#define DC_LOG_INFO_VALUE(value) DC_LOG_INFO(QString(#value"=%1").arg(dcCreateLogContent(value)))
#define DC_LOG_WARNING_VALUE(value) DC_LOG_WARNING(QString(#value"=%1").arg(dcCreateLogContent(value)))
#define DC_LOG_ERROR_VALUE(value) DC_LOG_ERROR(QString(#value"=%1").arg(dcCreateLogContent(value)))


//#define DC_LOG_TEST_TT DC_LOG_TEST(QString("TTTTTTTTTTTTTTTV"));
//#define DC_LOG_TEST_LINE DC_LOG_TEST(QString("LINE=%1").arg(__LINE__));

//#define C_BOOL_VALUE_TO_STRING(value) (value ? "TRUE":"FALSE")

//#define C_VALUE_LOG_TEST_BOOL(value) DC_LOG_TEST(QString(#value"=%1").arg(C_BOOL_VALUE_TO_STRING(value)))
//#define C_VALUE_LOG_DEBUG_BOOL(value) DC_LOG_DEBUG(QString(#value"=%1").arg(C_BOOL_VALUE_TO_STRING(value)))
//#define C_VALUE_LOG_INFO_BOOL(value) DC_LOG_INFO(QString(#value"=%1").arg(C_BOOL_VALUE_TO_STRING(value)))
//#define C_VALUE_LOG_WARNING_BOOL(value) DC_LOG_WARNING(QString(#value"=%1").arg(C_BOOL_VALUE_TO_STRING(value)))
//#define C_VALUE_LOG_ERROR_BOOL(value) DC_LOG_ERROR(QString(#value"=%1").arg(C_BOOL_VALUE_TO_STRING(value)))




#endif // DCLOG_H

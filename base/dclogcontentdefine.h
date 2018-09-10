#ifndef DCLOGCONTENTDEFINE_H
#define DCLOGCONTENTDEFINE_H

#include <QTime>
#include <QDateTime>
#include <QSize>
#include <QSizeF>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>

template<typename T>
class DCLogEngine
{
public:
    static QString createValue(const T &value)
    {
      return QString("%1").arg(value);
    };

private:

};

template<>
class DCLogEngine<QSize>
{
public:
    static QString createValue(const QSize &value)
    {
        return QString("(w=%1,h=%2)").arg(value.width()).arg(value.height());
    };

private:
};

template<>
class DCLogEngine<QSizeF>
{
public:
    static QString createValue(const QSizeF &value)
    {
        return QString("(w=%1,h=%2)").arg(value.width()).arg(value.height());
    };

private:
};

template<>
class DCLogEngine<QRect>
{
public:
    static QString createValue(const QRect &value)
    {
        return QString("(x=%1,y=%2,w=%3,h=%4)").arg(value.x()).arg(value.y()).arg(value.width()).arg(value.height());
    };

private:
};

template<>
class DCLogEngine<QRectF>
{
public:
    static QString createValue(const QRectF &value)
    {
        return QString("(x=%1,y=%2,w=%3,h=%4)").arg(value.x()).arg(value.y()).arg(value.width()).arg(value.height());
    };

private:
};

template<>
class DCLogEngine<QTime>
{
public:
    static QString createValue(const QTime &value)
    {
        return QString("(%1)").arg(value.toString("hh:mm:ss"));
    };

private:
};

template<>
class DCLogEngine<QDateTime>
{
public:
    static QString createValue(const QDateTime &value)
    {
        return QString("(%1)").arg(value.toString("yyyy-MM-dd hh:mm:ss"));
    };

private:
};

template<>
class DCLogEngine<bool>
{
public:
    static QString createValue(const bool &value)
    {
        return QString("(%1)").arg(value ? "T":"F");
    };

private:
};


template<typename TYPE>
QString dcCreateLogContent(const TYPE& data)
{
    return DCLogEngine<TYPE>::createValue(data);
}

#endif // DCLOGCONTENTDEFINE_H

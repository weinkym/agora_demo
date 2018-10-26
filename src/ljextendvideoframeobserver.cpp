#include "ljextendvideoframeobserver.h"

#include "clogsetting.h"
#include <QFile>
#include <string.h>

LJExtendVideoFrameObserver::LJExtendVideoFrameObserver()
{
    m_lpImageBuffer = (char*)malloc(1382400);
//    m_lpImageBuffer = new BYTE[0x800000];

//    m_lpRenderBuffer = new BYTE[0x800000];

#ifdef Q_OS_MAC
    QFile file("/Users/miaozw/Movies/1280_720.yuv");
#else
    QFile file("E:\\TEST_DOCUMENT\\YUV\\1280_720.yuv");
#endif
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray array =  file.readAll();
        DC_LOG_INFO_VALUE(array.size());
        memcpy(m_lpImageBuffer,array.data(),array.size());
    }


    m_RenderWidth = 0;
    m_RenderHeight = 0;
}


LJExtendVideoFrameObserver::~LJExtendVideoFrameObserver()
{
    delete[] m_lpImageBuffer;
//    m_lpImageBuffer = NULL;
//    delete[] m_lpRenderBuffer;
//    m_lpRenderBuffer = NULL;
}

int timeinc = 0;
bool LJExtendVideoFrameObserver::onCaptureVideoFrame(VideoFrame& videoFrame)
{
//    DC_LOG_FUNCTION;
//    DC_LOG_INFO_VALUE(videoFrame.width);
//    DC_LOG_INFO_VALUE(videoFrame.height);
    uint64_t nBufferSize = 0x800000;
    int nUvLen = videoFrame.height * videoFrame.width / 4;
    int nYLen = nUvLen * 4;

    char *m_lpY = m_lpImageBuffer;
    char *m_lpU = m_lpImageBuffer + nUvLen * 4;
    char *m_lpV = m_lpImageBuffer + 5 * nUvLen;

    memcpy(videoFrame.yBuffer, m_lpY, nYLen);
    videoFrame.yStride = videoFrame.width;

    memcpy(videoFrame.uBuffer, m_lpU, nUvLen);
    videoFrame.uStride = videoFrame.width/2;

    memcpy(videoFrame.vBuffer, m_lpV, nUvLen);
    videoFrame.vStride = videoFrame.width/2;

    videoFrame.type = FRAME_TYPE_YUV420;
    videoFrame.rotation = 0;
    videoFrame.renderTimeMs = QDateTime::currentDateTime().toTime_t();
    return true;
}

bool LJExtendVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame)
{
    return true;
}

void LJExtendVideoFrameObserver::setVideoResolution(int w, int h)
{
    m_resolutionX = w;
    m_resolutionY = h;
}

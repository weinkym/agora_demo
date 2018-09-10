#ifndef LJEXTENDVIDEOFRAMEOBSERVER_H
#define LJEXTENDVIDEOFRAMEOBSERVER_H

#include "IAgoraMediaEngine.h"


class LJExtendVideoFrameObserver :
    public agora::media::IVideoFrameObserver
{
public:
    LJExtendVideoFrameObserver();
    ~LJExtendVideoFrameObserver();

    virtual bool onCaptureVideoFrame(VideoFrame& videoFrame);
    virtual bool onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame);

    void setVideoResolution(int w, int h);
    char*				m_lpImageBuffer;
//    char*					m_lpRenderBuffer;
    int					m_RenderWidth;
    int					m_RenderHeight;

private:
//    LPBYTE				m_lpY;
//    LPBYTE				m_lpU;
//    LPBYTE				m_lpV;

    int                m_resolutionX;
    int                m_resolutionY;
};

#endif // LJEXTENDVIDEOFRAMEOBSERVER_H

#include "ljextendaudioframeobserver.h"
#include "clogsetting.h"
#include "agorartcengine.h"

extern AgoraRtcEngine*	pAgoraManager;


LJExtendAudioFrameObserver::LJExtendAudioFrameObserver()
{
//	this->pCircleBuffer = new CicleBuffer(44100 * 2 * 2, 0);
//    pPlayerData = new BYTE[0x800000];
}

LJExtendAudioFrameObserver::~LJExtendAudioFrameObserver()
{
//    delete[] pPlayerData;
}

static inline int16_t MixerAddS16(int16_t var1, int16_t var2) {
    static const int32_t kMaxInt16 = 32767;
    static const int32_t kMinInt16 = -32768;
    int32_t tmp = (int32_t)var1 + (int32_t)var2;
    int16_t out16;

    if (tmp > kMaxInt16) {
        out16 = kMaxInt16;
    }
    else if (tmp < kMinInt16) {
        out16 = kMinInt16;
    }
    else {
        out16 = (int16_t)tmp;
    }

    return out16;
}

void MixerAddS16(int16_t* src1, const int16_t* src2, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        src1[i] = MixerAddS16(src1[i], src2[i]);
    }
}

bool mixAudioData(char* psrc, char* pdst, int datalen)
{
    if (!psrc || !pdst || datalen <= 0)
    {
        return false;
    }

    for (int i = 0; i < datalen; i++)
    {
        pdst[i] += psrc[i];
    }
    return true;
}

bool LJExtendAudioFrameObserver::onRecordAudioFrame(AudioFrame& audioFrame)
{
//    DC_LOG_FUNCTION;
//    static QTime time = QTime::currentTime();
//    QTime c_time = QTime::currentTime();
//    int ms = time.msecsTo(c_time);
//    time = c_time;
//    DC_LOG_INFO_VALUE(ms);
//    SIZE_T nSize = audioFrame.channels*audioFrame.samples * 2;
//    unsigned int datalen = 0;
////    pCircleBuffer->readBuffer(this->pPlayerData, nSize, &datalen);

//    if (nSize > 0 && datalen > 0)
//    {
//        int nMixLen = datalen > nSize ? nSize : datalen;
//        memcpy((int16_t*)audioFrame.buffer, (int16_t*)pPlayerData, nMixLen);
//    }

    return true;
}

bool LJExtendAudioFrameObserver::onPlaybackAudioFrame(AudioFrame& audioFrame)
{
//    SIZE_T nSize = audioFrame.channels*audioFrame.samples * 2;

    return true;
}

bool LJExtendAudioFrameObserver::onMixedAudioFrame(AudioFrame& audioFrame)
{
    return true;
}

bool LJExtendAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame)
{
    return true;
}

#ifndef LJEXTENDAUDIOFRAMEOBSERVER_H
#define LJEXTENDAUDIOFRAMEOBSERVER_H

#include "IAgoraMediaEngine.h"

class LJExtendAudioFrameObserver :
    public agora::media::IAudioFrameObserver
{
public:
//	CicleBuffer* pCircleBuffer;
    LJExtendAudioFrameObserver();
    ~LJExtendAudioFrameObserver();
//    LPBYTE pPlayerData;
//    char * pPlayerData;
    int    nPlayerDataLen;
    bool   bDebug;

    virtual bool onRecordAudioFrame(AudioFrame& audioFrame);
    virtual bool onPlaybackAudioFrame(AudioFrame& audioFrame);
    virtual bool onMixedAudioFrame(AudioFrame& audioFrame);
    virtual bool onPlaybackAudioFrameBeforeMixing(unsigned int uid, AudioFrame& audioFrame);
};


#endif // LJEXTENDAUDIOFRAMEOBSERVER_H

#ifndef __SOUND_H__
#define __SOUND_H__

class TSound {

public:
    virtual void init() = 0;
    virtual void deinit() = 0;
    virtual void playSound() = 0;
    virtual void pauseSound() = 0;
};

#endif
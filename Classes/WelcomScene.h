//
//  WelcomScene.h
//  Aircraft
//
//  Created by lc on 12/3/14.
//
//

#ifndef __Aircraft__WelcomScene__
#define __Aircraft__WelcomScene__

#include <stdio.h>
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class WelcomeScene : public Scene {
public:
    CREATE_FUNC(WelcomeScene);
    
    virtual bool init();
    
    WelcomeLayer* welcomeLayer;
    
    void preLoadMusic();
};

#endif /* defined(__Aircraft__WelcomScene__) */

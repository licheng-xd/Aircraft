//
//  WelcomeLayer.h
//  Aircraft
//
//  Created by lc on 12/3/14.
//
//

#ifndef __Aircraft__WelcomeLayer__
#define __Aircraft__WelcomeLayer__

#include <stdio.h>
#include "PlistHandler.h"
#include "GameScene.h"
#include "GameOverLayer.h"

USING_NS_CC;

class WelcomeLayer : public Layer {
private:
    bool haveSaveFile();
    
    void getHighestHistoryScore();
    
public:
    CREATE_FUNC(WelcomeLayer);
    
    virtual bool init();
    
    void loadingDone(Node* target);
};

#endif /* defined(__Aircraft__WelcomeLayer__) */

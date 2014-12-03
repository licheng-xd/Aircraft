//
//  GameScene.h
//  Aircraft
//
//  Created by lc on 12/3/14.
//
//

#ifndef __Aircraft__GameScene__
#define __Aircraft__GameScene__

#include <stdio.h>
#include "GameLayer.h"


USING_NS_CC;

class GameScene : public Scene {
public:
    GameLayer* gameLayer;
    
    virtual bool init();
    
    CREATE_FUNC(GameScene);
};

#endif /* defined(__Aircraft__GameScene__) */

//
//  GameOverScene.h
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#ifndef __Aircraft__GameOverScene__
#define __Aircraft__GameOverScene__

#include <stdio.h>
#include "GameOverLayer.h"

USING_NS_CC;

class GameOverScene : public Scene {
public:
    
    GameOverScene(void);
    
    ~GameOverScene(void);
    
    virtual bool init();
    
    static GameOverScene* create(int score);
    
    GameOverLayer* gameOverLayer;
    
    int m_score;
};

#endif /* defined(__Aircraft__GameOverScene__) */

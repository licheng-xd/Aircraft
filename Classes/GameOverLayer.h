//
//  GameOverLayer.h
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#ifndef __Aircraft__GameOverLayer__
#define __Aircraft__GameOverLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public Layer {
public:
    GameOverLayer(void);
    
    ~GameOverLayer(void);
    
    static GameOverLayer* create(int score);

    virtual bool init();
    
    void menuBackCallback(Ref* target);
    
    void beginChangeHighestScore(Node* target);
    
    void showAD();
    
    int m_score;
    
    static int m_highestScore;
    
    Label* highestScoreLabel;
};

#endif /* defined(__Aircraft__GameOverLayer__) */

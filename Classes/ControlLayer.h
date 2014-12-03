//
//  ControlLayer.h
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#ifndef __Aircraft__ControlLayer__
#define __Aircraft__ControlLayer__

#include <stdio.h>
#include "PlaneLayer.h"
#include <string.h>

USING_NS_CC;
using namespace std;

const int ENEMY1_LIFE = 1;

const int ENEMY2_LIFE = 2;

const int ENEMY3_LIFE = 8;

const int TAG_AIRPLANE = 10;

const int TAG_BOMB_MENUITEM = 12;

const int TAG_BOMBCOUNT_LABEL = 13;

class ControlLayer : public Layer {
private:
    Label* scoreLable;
    
    MenuItemSprite* pauseItem;
    
    void menuPausedCallback(Ref* pSender);
    
public:
    static ControlLayer* create();

    void updateScore(int score);
    
    virtual bool init();
    
    void finish();
};

#endif /* defined(__Aircraft__ControlLayer__) */

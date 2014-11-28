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

USING_NS_CC;

const int TAG_AIRPLANE = 10;

const int ENEMY1_LIFE = 1;

const int ENEMY2_LIFE = 2;

const int ENEMY3_LIFE = 8;

class ControlLayer : public Node {
private:
    int m_score = 0;
public:
    static ControlLayer* create();

    void updateScore(int score);
    
    void finish();
};

#endif /* defined(__Aircraft__ControlLayer__) */

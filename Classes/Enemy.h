//
//  Enemy.h
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#ifndef __Aircraft__Enemy__
#define __Aircraft__Enemy__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Node {
    
private:
    Sprite* m_sprite;
    
    int m_life;
    
public:
    Enemy();
    ~Enemy();
    
    static Enemy* create();
    
    void bindSprite(Sprite* sprite, int life);
    
    Sprite* getSprite();
    
    int getLife();
    
    void loseLife();
    
    Rect getBoundingBox();
};

#endif /* defined(__Aircraft__Enemy__) */

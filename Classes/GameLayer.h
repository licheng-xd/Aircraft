//
//  GameLayer.h
//  Aircraft
//
//  Created by lc on 11/23/14.
//
//

#ifndef __Aircraft__GameLayer__
#define __Aircraft__GameLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletLayer.h"
#include "PlistHandler.h"
#include "EnemyLayer.h"
#include "ControlLayer.h"

USING_NS_CC;

class GameLayer : public Layer {
private:
    int score = 0;
    
public:
    PlaneLayer* planeLayer;
    
    BulletLayer* bulletLayer;
    
    EnemyLayer* enemyLayer;
    
    ControlLayer* controlLayer;
    
    Sprite *bg1, *bg2;
    
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
    
    void backgroundMove(float dt);
    
    virtual void update(float dt);
    
    bool updatePlane();
    
    bool checkPlaneBox(Enemy* enemy);
};

#endif /* defined(__Aircraft__GameLayer__) */

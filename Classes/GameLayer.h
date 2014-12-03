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
#include "UFOLayer.h"
#include "MutiBulletLayer.h"
#include "GameOverScene.h"

USING_NS_CC;

class GameLayer : public Layer {
private:
    int m_score = 0;
    
    void backgroundMove(float dt);
    
    virtual void update(float dt);
    
    void updateBullet();
    
    void updateMutiBulelt();
    
    bool updateEnemy();
    
    void updateUFO();
    
    void updateBombMenu(int count);
    
    void menuBombCallback(Ref* target);
    
    bool checkPlaneBox(Enemy* enemy);
    
    Sprite *bg1, *bg2;
    
    Menu* bombMenu;
    
    Label* bombCountLabel;
    
    int m_bombCount = 0;
    
public:
    GameLayer(void);
    
    ~GameLayer(void);
    
    PlaneLayer* planeLayer;
    
    BulletLayer* bulletLayer;
    
    EnemyLayer* enemyLayer;
    
    ControlLayer* controlLayer;
    
    UFOLayer* ufoLayer;
    
    MutiBulletLayer* mutiBulletLayer;
    
    static Scene* createScene();
    
    virtual bool init();
    
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__Aircraft__GameLayer__) */

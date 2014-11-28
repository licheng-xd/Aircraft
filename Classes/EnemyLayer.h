//
//  EnemyLayer.h
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#ifndef __Aircraft__EnemyLayer__
#define __Aircraft__EnemyLayer__

#include <stdio.h>
#include "Enemy.h"
#include "PlistHandler.h"
#include "ControlLayer.h"

USING_NS_CC;

class EnemyLayer : public Layer {
public:
    __Array* m_allEnemy1;
    __Array* m_allEnemy2;
    __Array* m_allEnemy3;
    
    EnemyLayer(void);
    ~EnemyLayer(void);
    
    static EnemyLayer* create();
    
    virtual bool init();
    
    void addEnemy1(float dt);
    
    void addEnemy2(float dt);
    
    void addEnemy3(float dt);
    
    void enemy1MoveFinished(Node* pNode);
    
    void enemy2MoveFinished(Node* pNode);
    
    void enemy3MoveFinished(Node* pNode);
    
    void blowupEnemy1(Enemy* enemy1);
    
    void blowupEnemy2(Enemy* enemy2);
    
    void blowupEnemy3(Enemy* enemy3);
    
    void removeEnemy1(Node* targe, void* data);
    
    void removeEnemy2(Node* targe, void* data);
    
    void removeEnemy3(Node* targe, void* data);
    
    void removeAllEnemy1();
    
    void removeAllEnemy();
};

#endif /* defined(__Aircraft__EnemyLayer__) */

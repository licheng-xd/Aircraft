//
//  BulletLayer.h
//  Aircraft
//
//  Created by lc on 11/26/14.
//
//

#ifndef __Aircraft__BulletLayer__
#define __Aircraft__BulletLayer__

#include <stdio.h>
#include "PlaneLayer.h"
#include "PlistHandler.h"

USING_NS_CC;

class BulletLayer : public Layer {
    
public:
    
    __Array *m_pAllBullet;
    
    BulletLayer(void);
    
    ~BulletLayer(void);
    
    Size winSize;
    
    SpriteBatchNode *bulletBatchNode;
    
    virtual bool init();
    
    void addBullet(float dt);
    
    void bulletMoveFinished(Node *pSender);
    
    static BulletLayer* create();
    
    void startShoot(float delay);
    
    void stopShoot();
    
    void removeBullet(Sprite *bullet);
};

#endif /* defined(__Aircraft__BulletLayer__) */

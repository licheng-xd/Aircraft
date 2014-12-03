//
//  MutiBulletLayer.h
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#ifndef __Aircraft__MutiBulletLayer__
#define __Aircraft__MutiBulletLayer__

#include <stdio.h>
#include "PlistHandler.h"
#include "PlaneLayer.h"

USING_NS_CC;

class MutiBulletLayer : public Layer {
public:
    MutiBulletLayer(void);
    
    ~MutiBulletLayer(void);
    
    CREATE_FUNC(MutiBulletLayer);
    
    bool init();
    
    void addMutiBullet(float dt);
    
    void mutiBulletMoveFinished(Node* target);
    
    void removeMutiBullet(Sprite* mutiBullet);
    
    void startShoot();
    
    void stopShoot();
    
public:
    __Array* m_allMutiBullet;
};

#endif /* defined(__Aircraft__MutiBulletLayer__) */

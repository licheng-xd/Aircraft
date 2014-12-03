//
//  UFOLayer.h
//  Aircraft
//
//  Created by lc on 12/1/14.
//
//

#ifndef __Aircraft__UFOLayer__
#define __Aircraft__UFOLayer__

#include <stdio.h>
#include "PlistHandler.h"

USING_NS_CC;

class UFOLayer : public Layer {
private:
    void addUFO(int type); // 1-ufo1,2-ufo2
    
public:
    __Array* m_allMutiBullte;
    
    __Array* m_allBomb;
    
public:
    UFOLayer(void);
    
    ~UFOLayer(void);
    
    CREATE_FUNC(UFOLayer);
    
    bool init();
    
    void addBomb(float dt);
    
    void removeBomb(Node* bomb);
    
    void bombMoveFinished(Node* target);
    
    void addMutiBullet(float dt);
    
    void removeMutiBullet(Node* mutiBulelt);
    
    void mutiBulletMoveFinished(Node* target);
};

#endif /* defined(__Aircraft__UFOLayer__) */

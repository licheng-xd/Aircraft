//
//  ControlLayer.cpp
//  Aircraft
//
//  Created by lc on 11/27/14.
//
//

#include "ControlLayer.h"

ControlLayer* ControlLayer::create() {
    ControlLayer* p = new ControlLayer();
    if (p != NULL) {
        p->autorelease();
        return p;
    }
    else {
        return NULL;
    }
}

void ControlLayer::updateScore(int score) {
    this->m_score = score;
}

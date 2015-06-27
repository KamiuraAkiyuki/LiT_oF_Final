//
//  unicolorPlanet.h
//  LifeisTechFinalAssignment
//
//  Created by Akiyuki Kamiura on 2015/06/27.
//
//

#ifndef __LifeisTechFinalAssignment__unicolorPlanet__
#define __LifeisTechFinalAssignment__unicolorPlanet__

#include <stdio.h>
#include "ofMain.h"

class unicolorPlanet{
    
private:
    float radius;
    
    
public:
    unicolorPlanet(){};
    unicolorPlanet(float radius){
        this -> radius = radius;
    }
    
    void draw();
    
};

#endif /* defined(__LifeisTechFinalAssignment__unicolorPlanet__) */

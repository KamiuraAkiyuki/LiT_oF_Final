//
//  boxGrid.h
//  LifeisTechFinalAssignment
//
//  Created by Akiyuki Kamiura on 2015/06/23.
//
//

#ifndef __LifeisTechFinalAssignment__boxGrid__
#define __LifeisTechFinalAssignment__boxGrid__

#include <stdio.h>
#include "ofMain.h"

class boxGrid{
    
private:
    ofPoint startPoint;
    float bottomWidth = 3;
    float bottomHeight = 3;
    float boxHeight = 0;
    ofColor boxColor;
    
public:
    boxGrid(){};
    boxGrid(ofPoint startPoint, ofColor boxColor){
        this -> startPoint = startPoint;
        this -> boxColor = boxColor;
    };
    
    // セッター
    void setStartPoint(ofPoint point);
    void setBottomWidth(float bottomWidth);
    void setBottomHeight(float bottomHeight);
    void setBoxColor(ofColor boxColor);
    void setBoxHeight(float boxHeight);
    
    // ゲッター
    ofPoint getStartPoint();
    float getBottomWidth();
    float getBottomHeight();
    ofColor getBoxColor();
    float getBoxHeight();
};

#endif /* defined(__LifeisTechFinalAssignment__boxGrid__) */

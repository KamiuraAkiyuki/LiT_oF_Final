//
//  boxGrid.cpp
//  LifeisTechFinalAssignment
//
//  Created by Akiyuki Kamiura on 2015/06/23.
//
//

#include "boxGrid.h"

// set
void boxGrid::setStartPoint(ofPoint point){
    this -> startPoint = point;
}
void boxGrid::setBottomWidth(float bottomWidth){
    this -> bottomWidth = bottomWidth;
}
void boxGrid::setBottomHeight(float bottomHeight){
    this -> bottomHeight = bottomHeight;
}
void boxGrid::setBoxHeight(float boxHeight){
    this -> boxHeight = boxHeight;
}
void boxGrid::setBoxColor(ofColor boxColor){
    this -> boxColor = boxColor;
}

// get
ofPoint boxGrid::getStartPoint(){
    return startPoint;
}
float boxGrid::getBottomWidth(){
    return bottomWidth;
}
float boxGrid::getBottomHeight(){
    return bottomHeight;
}
float boxGrid::getBoxHeight(){
    return boxHeight;
}
ofColor boxGrid::getBoxColor(){
    return boxColor;
}


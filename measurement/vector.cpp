#include "vector.h"
#define PI 3.14159

using namespace std;

void Vector::addAnglerVelocity(const int16_t anglerVelocity){
  if((int8_t)aryAnglerVelocity.size() >= maxAry){
    aryAnglerVelocity.erase(aryAnglerVelocity.begin());
  }
  aryAnglerVelocity.push_front(anglerVelocity);
}

void Vector::resetAnglerVelocity(){
  aryAnglerVelocity.clear();
}

float Vector::getStable(const int idx){
  float stable = 0;
  int max = idx;
  auto itr = aryAnglerVelocity.begin();
  if((int)aryAnglerVelocity.size() < idx){
    max = (int)aryAnglerVelocity.size();
  }
  for(int i = 0; i < max; i++){
    stable += pow(*itr, 2);
    itr++;
  }
  sqrt(stable);
  if(stable == 0){
    return 0;
  }
  return stable / idx;
}

float Vector::getRotate(const int idx){
  float rotate = 0;
  int max = idx;
  auto itr = aryAnglerVelocity.begin();
  if((int)aryAnglerVelocity.size() < idx){
    max = (int)aryAnglerVelocity.size();
  }
  for(int i = 0; i < max; i++){
    if(i < (int)aryAnglerVelocity.size()){
      rotate += *itr;
      itr++;
    }
  }
  if(rotate == 0){
    return 0;
  }
  return rotate / 2;
}

void Vector::setRotateOffset(const int32_t left, const int32_t right){
  this->leftOffset = left;
  this->rightOffset = right;
}

void Vector::setRotateOffset(){
  this->leftOffset = ev3->leftWheel.getCount();
  this->rightOffset = ev3->rightWheel.getCount();
}

float Vector::getScalar(){
  int32_t left = ev3->leftWheel.getCount() - this->leftOffset;
  int32_t right = ev3->rightWheel.getCount() - this->rightOffset;
  float scalar = 0;
  if(left < right){
    scalar = (float)(right - left) / 2 + left;
    scalar = scalar / 360 * 2 * PI * WHEEL;
  }else if(left > right){
    scalar = (float)(left - right) / 2 + right;
    scalar = scalar / 360 * 2 * PI * WHEEL;
  }else{
    scalar = (float)left / 360 * 2 * PI * WHEEL;
  }

  return scalar;
}

float Vector::getAngle(){
  int32_t left = ev3->leftWheel.getCount() - this->leftOffset;
  int32_t right = ev3->rightWheel.getCount() - this->rightOffset;
  float angle = 0;

  angle = (float)(left - right);
  angle = angle / 3;

  return angle;
}
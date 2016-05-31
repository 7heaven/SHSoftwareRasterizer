//
//  Transform.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/26.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "Transform.hpp"
#include "math.h"

namespace sh{
    Transform::Transform()
    :m(Matrix44::identity()){
        
    }
    
    Transform::~Transform(){
        delete m;
    }
    
    SHVector3D Transform::operator*(SHVector3D vector){
        SHVector3D resultVector = (SHVector3D){0, 0, 0, 0};
        
        resultVector.x = (*this->m)[0][0] * vector.x +
        (*this->m)[0][1] * vector.y +
        (*this->m)[0][2] * vector.z +
        (*this->m)[0][3] * vector.w;
        
        resultVector.y = (*this->m)[1][0] * vector.x +
        (*this->m)[1][1] * vector.y +
        (*this->m)[1][2] * vector.z +
        (*this->m)[1][3] * vector.w;
        
        resultVector.z = (*this->m)[2][0] * vector.x +
        (*this->m)[2][1] * vector.y +
        (*this->m)[2][2] * vector.z +
        (*this->m)[2][3] * vector.w;
        
        resultVector.w = (*this->m)[3][0] * vector.x +
        (*this->m)[3][1] * vector.y +
        (*this->m)[3][2] * vector.z +
        (*this->m)[3][3] * vector.w;
        
        return resultVector;
    }
    
    Transform * Transform::operator*=(Transform &t){
        (*this->m) *= *t.m;
        
        return this;
    }
    
    Transform * Transform::translate(const SHVector3D &vector){
        Transform *t = new Transform();
        (*t->m)[0][3] = vector.x;
        (*t->m)[1][3] = vector.y;
        (*t->m)[2][3] = vector.z;
        return t;
    }
    
    Transform * Transform::perspective(float fov, float clipNear, float clipFar){
        return perspective(clipNear);
    }
    
    Transform * Transform::perspective(float N){
        Transform *t = new Transform();
        (*t->m)[3][2] = 1.0F / N;
        (*t->m)[3][3] = 0;
        
        return t;
    }
    
    Transform * Transform::scale(const SHVector3D &vector){
        Transform *t = new Transform();
        (*t->m)[0][0] = vector.x;
        (*t->m)[1][1] = vector.y;
        (*t->m)[2][2] = vector.z;
        
        return t;
    }
    
    Transform * Transform::rotate(const SHVector3D &vector){
        Transform *t = new Transform();
        float c = cos(vector.w);
        float s = sin(vector.w);
        
        float oneMinusC = 1 - c;
        
        (*t->m)[0][0] = c + vector.x * vector.x * oneMinusC;
        (*t->m)[0][1] = vector.x * vector.y * oneMinusC + vector.z * s;
        (*t->m)[0][2] = vector.x * vector.z * oneMinusC - vector.y * s;
        (*t->m)[1][0] = vector.x * vector.y * oneMinusC - vector.z * s;
        (*t->m)[1][1] = c + vector.y * vector.y * oneMinusC;
        (*t->m)[1][2] = vector.y * vector.z * oneMinusC + vector.x * s;
        (*t->m)[2][0] = vector.x * vector.z * oneMinusC + vector.y * s;
        (*t->m)[2][1] = vector.y * vector.z * oneMinusC - vector.x * s;
        (*t->m)[2][2] = c + vector.z * vector.z * oneMinusC;
        
        return t;
    }
    
    Transform * Transform::rotate(const float angleX, const float angleY, const float angleZ){
        float cx = cos(angleX);
        float sx = sin(angleX);
        float cy = cos(angleY);
        float sy = sin(angleY);
        float cz = cos(angleZ);
        float sz = sin(angleZ);
        
        Transform *t = new Transform();
        (*t->m)[0][0] = cz * cx - sz * cy * sx;
        (*t->m)[0][1] = -sz * cx - cz * cy * sx;
        (*t->m)[0][2] = sy * sx;
        (*t->m)[1][0] = cz * sx + sz * cy * cx;
        (*t->m)[1][1] = -sz * sx + cz * cy * cx;
        (*t->m)[1][2] = -sy * cx;
        (*t->m)[2][0] = sz * sy;
        (*t->m)[2][1] = cz * sy;
        (*t->m)[2][2] = cy;
        
        return t;
    }
    
    Transform * Transform::lookAt(const SHPoint3D &cameraPos, const SHVector3D &directionVector){
        return nullptr;
    }
}
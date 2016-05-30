//
//  Transform.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/26.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "Transform.hpp"

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
        (*t->m)[0][0] = 1.0F;
        (*t->m)[1][1] = 1.0F;
        (*t->m)[2][2] = 1.0F;
        (*t->m)[3][2] = 1.0F / N;
        
        return t;
    }
    
    Transform * Transform::scale(const SHVector3D &vector){
        Transform *t = new Transform();
        (*t->m)[0][0] = vector.x;
        (*t->m)[1][1] = vector.y;
        (*t->m)[2][2] = vector.z;
        
        return t;
    }
    
    Transform * Transform::rotate(const SHVector3D &vector, float angle){
        return nullptr;
    }
    
    Transform * Transform::rotate(const float angleX, const float angleY, const float angleZ){
        return nullptr;
    }
    
    Transform * Transform::lookAt(const SHPoint3D &cameraPos, const SHVector3D &directionVector){
        return nullptr;
    }
}
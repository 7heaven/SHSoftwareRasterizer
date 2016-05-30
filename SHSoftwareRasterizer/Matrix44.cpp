//
//  Matrix44.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "Matrix44.hpp"

#include <algorithm>

namespace sh{

    Matrix44::Matrix44(float mat[16]){
        memcpy(this->mat, mat, sizeof(float) * 16);
    }
    
    Matrix44::Matrix44(float m00, float m01, float m02, float m03,
                       float m10, float m11, float m12, float m13,
                       float m20, float m21, float m22, float m23,
                       float m30, float m31, float m32, float m33){
        auto tmp = new float[16];
        tmp[0] = m00;
        tmp[1] = m01;
        tmp[2] = m02;
        tmp[3] = m03;
        tmp[4] = m10;
        tmp[5] = m11;
        tmp[6] = m12;
        tmp[7] = m13;
        tmp[8] = m20;
        tmp[9] = m21;
        tmp[10] = m22;
        tmp[11] = m23;
        tmp[12] = m30;
        tmp[13] = m31;
        tmp[14] = m32;
        tmp[15] = m33;
        
        memcpy(this->mat, tmp, sizeof(float) * 16);
        
    }
    
    Matrix44 * Matrix44::identity(){
        auto identity = new float[16];
        memset(identity, 0, sizeof(float) * 16);
        identity[0] = 1;
        identity[5] = 1;
        identity[10] = 1;
        identity[15] = 1;
        
        return new Matrix44(identity);
    }
    
    void Matrix44::toIdentity(){
        memset(this->mat, 0, sizeof(float) * 16);
        this->mat[0] = 1;
        this->mat[5] = 1;
        this->mat[10] = 1;
        this->mat[15] = 1;
    }
    
    Matrix44 Matrix44::operator*=(Matrix44 &m){
        auto tmp = new float[16];
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                int dest = i * 4 + j;
                tmp[dest] = this->mat[i * 4] * m.mat[j] +
                            this->mat[i * 4 + 1] * m.mat[j + 4] +
                            this->mat[i * 4 + 2] * m.mat[j + 8] +
                            this->mat[i * 4 + 3] * m.mat[j + 12];
            }
        }
        
        memcpy(this->mat, tmp, sizeof(float) * 16);
        delete[] tmp;
        
        return *this;
    }
    
    Matrix44 Matrix44::operator+=(Matrix44 &m){
        for(int i = 0; i < 16; i++){
            this->mat[i] = this->mat[i] + m.mat[i];
        }
        
        return *this;
    }
    
    SHVector3D Matrix44::operator*(SHVector3D vector){
        SHVector3D resultVector = (SHVector3D){0, 0, 0, 0};
        
        resultVector.x = this->mat[0] * vector.x +
                         this->mat[1] * vector.y +
                         this->mat[2] * vector.z +
                         this->mat[3] * vector.w;
        
        resultVector.y = this->mat[4] * vector.x +
                         this->mat[5] * vector.y +
                         this->mat[6] * vector.z +
                         this->mat[7] * vector.w;
        
        resultVector.z = this->mat[8] * vector.x +
                         this->mat[9] * vector.y +
                         this->mat[10] * vector.z +
                         this->mat[11] * vector.w;
        
        resultVector.w = this->mat[12] * vector.x +
                         this->mat[13] * vector.y +
                         this->mat[14] * vector.z +
                         this->mat[15] * vector.w;
        
        return resultVector;
    }

    Matrix44::~Matrix44(){
    }

}
//
//  Matrix44.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef Matrix44_hpp
#define Matrix44_hpp

#include <stdio.h>
#include "BasicGeometry.h"

namespace sh{

class Matrix44{
    class Row{
    public:
        int row;
        Matrix44 &m;
        
        Row(int row, Matrix44 &m):row(row), m(m){}
        
        const float &operator[](const unsigned int pos) const{
            return m.mat[row * 4 + pos];
        }
        
        float &operator[](const unsigned int pos){
            return m.mat[row * 4 + pos];
        }
    };
public:
    
    Matrix44(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);
    Matrix44(float mat[16]);
    ~Matrix44();
    
    static Matrix44 * identity();
    void toIdentity();
    
    Matrix44 operator*=(Matrix44 &m);
    Matrix44 operator+=(Matrix44 &m);
    
    SHVector3D operator*(SHVector3D vector);
    
    Row operator[](const unsigned int pos){
        return Row(pos, *this);
    }
    
private:
    
    float mat[16];
    
};

}

#endif /* Matrix44_hpp */

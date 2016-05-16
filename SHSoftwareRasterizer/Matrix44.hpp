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
public:
    Matrix44(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33);
    Matrix44(float mat[16]);
    ~Matrix44();
    
    static Matrix44 * identity();
    void toIdentity();
    
    Matrix44 operator*=(Matrix44 &mat);
    Matrix44 operator+=(Matrix44 &mat);
    
    SHVector3D operator*(SHVector3D vector);
    
    const float &operator[](int pos) const;
    float &operator[](int pos);
    
//    operator float();
//    float& operator=(int pos);
    
private:
    
    float mat[16];
    
};

}

#endif /* Matrix44_hpp */

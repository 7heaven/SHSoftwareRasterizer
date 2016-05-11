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

    Matrix44::Matrix44(int mat[16]){
        memcpy(this->mat, mat, sizeof(int) * 16);
    }
    
    Matrix44 * Matrix44::identity(){
        auto identity = new int[16];
        memset(identity, 0, sizeof(int) * 16);
        identity[0] = 1;
        identity[5] = 1;
        identity[10] = 1;
        identity[15] = 1;
        
        return new Matrix44(identity);
    }

    Matrix44::~Matrix44(){
    
    }

}
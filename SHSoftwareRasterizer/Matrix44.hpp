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

namespace sh{

class Matrix44{
public:
    Matrix44(int mat[16]);
    ~Matrix44();
    
    static Matrix44 * identity();
    
private:
    
    int mat[16];
    
};

}

#endif /* Matrix44_hpp */

//
//  Vertex3D.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/14.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef Vertex3D_hpp
#define Vertex3D_hpp

#include <stdio.h>
#include "BasicGeometry.h"

class Vertex3D{
public:
    Vertex3D(float x, float y, float z, float w);
    
    int x();
    int y();
    int z();
    int w();
private:
    SHTriangle3D pos;
    SHTriangle3D normal;
    SHPointF texturePos;
};

#endif /* Vertex3D_hpp */

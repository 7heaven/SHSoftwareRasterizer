//
//  Vector3D.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/14.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "Vertex3D.hpp"

namespace sh{
    Vertex3D::Vertex3D()
    :pos(SHVector3DMake(0, 0, 0, 0)),
    normal(SHPoint3DMake(0, 0, 0)),
    u(0),
    v(0),
    screenPos(SHPointMake(0, 0)){
        
    }
    
    Vertex3D::~Vertex3D(){
        
    }
}
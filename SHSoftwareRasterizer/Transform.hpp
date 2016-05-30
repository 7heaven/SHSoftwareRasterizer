//
//  Transform.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/26.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "BasicGeometry.h"
#include "Matrix44.hpp"

namespace sh{
    class Transform {
    public:
        Transform();
        ~Transform();
        
        SHVector3D operator*(SHVector3D vector);
        
        static Transform * translate(const SHVector3D &vector);
        static Transform * scale(const SHVector3D &vector);
        static Transform * rotate(const SHVector3D &vector, float angle);
        static Transform * rotate(const float angleX, const float angleY, const float angleZ);
        
        static Transform * perspective(float fov, float clipNear, float clipFar);
        static Transform * perspective(float N);
        static Transform * lookAt(const SHPoint3D &cameraPos, const SHVector3D &directionVector);
        
        Matrix44 *m;
    private:
        
    };
}

#endif /* Transform_hpp */

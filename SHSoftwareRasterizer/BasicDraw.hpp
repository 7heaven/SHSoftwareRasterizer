//
//  BasicDraw.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/13.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef BasicDraw_h
#define BasicDraw_h

#include <stdio.h>
#include "BasicGeometry.h"
#include "IDevice.h"
#include "Vertex3D.hpp"
#include "Texture.hpp"
#include "ILight.h"

namespace sh{

    class BasicDraw{
    public:
        static void drawLine(IDevice &device, SHPoint p0, SHPoint p1, SHColor color);
        static void drawTriangle(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color);
        static void drawPerspTriangle(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture, ILight &light);
    private:
        static void drawSubTri(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color);
        static void drawSubPerspTri(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture, ILight &light);
        static SHPoint getStep(SHPoint p0, SHPoint p1, float s);
    };
    
}

#endif /* BasicDraw_h */

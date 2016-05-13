//
//  BasicDraw.c
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/13.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "BasicDraw.hpp"
#include "math.h"

namespace sh{
    
    void BasicDraw::drawLine(IDevice &device, SHPoint p0, SHPoint p1, SHColor color){
        float x0 = p0.x;
        float y0 = p0.y;
        float x1 = p1.x;
        float y1 = p1.y;
        int dx = fabsf(x1-x0), sx = x0<x1 ? 1 : -1;
        int dy = fabsf(y1-y0), sy = y0<y1 ? 1 : -1;
        int err = (dx>dy ? dx : -dy)/2, e2;
        
        for(;;){
            device.setPixel((SHPoint){static_cast<int>(x0), static_cast<int>(y0)}, color);
            if (x0==x1 && y0==y1) break;
            e2 = err;
            if (e2 >-dx) { err -= dy; x0 += sx; }
            if (e2 < dy) { err += dx; y0 += sy; }
        }
    }
    
}
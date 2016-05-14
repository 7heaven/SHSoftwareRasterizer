//
//  BasicDraw.c
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/13.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "BasicDraw.hpp"
#include <stdlib.h>
#include "math.h"

namespace sh{
    
    void BasicDraw::drawLine(IDevice &device, SHPoint p0, SHPoint p1, SHColor color){
        int x = p0.x;
        int y = p0.y;
        
        int dx = abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
        int dy = abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;
        
        for(;;){
            device.setPixel((SHPoint){x, y}, color);
            if (x == p1.x && y == p1.y) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x += sx; }
            if (e2 < dy) { err += dx; y += sy; }
        }
    }
    
}
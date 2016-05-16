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
    
    SHPoint BasicDraw::getStep(SHPoint p0, SHPoint p1, float s){
        int x = p0.x;
        int y = p0.y;
        
        int dx = abs(p1.x - p0.x), sx = p0.x < p1.x ? 1 : -1;
        int dy = abs(p1.y - p0.y), sy = p0.y < p1.y ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2, e2;
        
        for(;;){
            if (x == p1.x && y == p1.y) break;
            e2 = err;
            if (e2 > -dx) { err -= dy; x += sx; }
            if (e2 < dy) { err += dx; y += sy; }
        }
        
        return (SHPoint){0, 0};
    }
    
    void BasicDraw::drawTriangle(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color){
        
        //simple sort by y
        for(;;){
            if(a.y <= b.y && b.y <= c.y){
                break;
            }
            
            if(a.y > b.y){
                SHPoint tmp = a;
                a = b;
                b = tmp;
            }
            
            if(b.y > c.y){
                SHPoint tmp = b;
                b = c;
                c = tmp;
            }
        }
        
        //return if area is zero
        if((a.y == b.y == c.y) || (a.x == b.x == c.x)) return;
        
        //two vertex of the triangle already has the same y value, so we only need to draw sub triangle once
        if(a.y == b.y || b.y == c.y){
            drawSubTri(device, a, b, c, color);
        }else{
            float r = (float) (c.x - a.x) / (float) (c.y - a.y);
            int x = r * (b.y - a.y);
            
            SHPoint tmp = SHPointMake(a.x + x, b.y);
            
            drawSubTri(device, a, b, tmp, color);
            drawSubTri(device, b, tmp, c, color);
        }
    }
    
    void BasicDraw::drawSubTri(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color){
        int y0 = a.y;
        int y1 = c.y;
        
        int yStep = y0;
        float leftR, rightR;
        SHPoint left, right;
        if(a.y == b.y){
            if(a.x > b.x){
                SHPoint tmp = a;
                a = b;
                b = tmp;
            }
            
            left = a;
            right = b;
            
            leftR = (float) (c.x - a.x) / (float) (y1 - y0);
            rightR = (float) (c.x - b.x) / (float) (y1 - y0);
            
        }else{
            if(b.x > c.x){
                SHPoint tmp = b;
                b = c;
                c = tmp;
            }
            
            left = a;
            right = a;
            
            leftR = (float) (b.x - a.x) / (float) (y1 - y0);
            rightR = (float) (c.x - a.x) / (float) (y1 - y0);
        }
        
        while(yStep <= y1){
            int leftX = left.x + (float) (yStep - y0) * leftR;
            int rightX = right.x + (float) (yStep - y0) * rightR;
            
            for(int xStep = leftX; xStep <= rightX; xStep++){
                device.setPixel((SHPoint){xStep, yStep}, color);
            }
            
            yStep++;
        }
    }
    
    void BasicDraw::drawPerspTriangle(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture){
        
        //simple sort by screen y
        for(;;){
            if(a->screenPos.y <= b->screenPos.y && b->screenPos.y <= c->screenPos.y){
                break;
            }
            
            if(a->screenPos.y > b->screenPos.y){
                Vertex3D *tmp = a;
                a = b;
                b = tmp;
            }
            
            if(b->screenPos.y > c->screenPos.y){
                Vertex3D *tmp = b;
                b = c;
                c = tmp;
            }
        }
        
        //return if area is zero
        if((a->screenPos.y == b->screenPos.y == c->screenPos.y) || (a->screenPos.x == b->screenPos.x == c->screenPos.x)) return;
        
        if(a->screenPos.y == b->screenPos.y || b->screenPos.y == c->screenPos.y){
            
        }else{
//            float r = (float) (c.x - a.x) / (float) (c.y - a.y);
//            int x = r * (b.y - a.y);
//            
//            SHPoint tmp = SHPointMake(a.x + x, b.y);
        }
        
    }
    
    void BasicDraw::drawSubPerspTri(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture){
        
    }
    
}
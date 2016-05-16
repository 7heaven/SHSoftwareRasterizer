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
        
        float leftX = left.x;
        float rightX = right.x;
        
        while(yStep <= y1){
            
            for(int xStep = leftX; xStep <= rightX; xStep++){
                device.setPixel((SHPoint){xStep, yStep}, color);
            }
            
            yStep++;
            leftX += leftR;
            rightX += rightR;
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
        
        a->pos.z = 1.0F / a->pos.z;
        b->pos.z = 1.0F / b->pos.z;
        c->pos.z = 1.0F / c->pos.z;
        
        a->u = 1.0F / a->u;
        a->v = 1.0F / a->v;
        b->u = 1.0F / b->u;
        b->v = 1.0F / b->v;
        c->u = 1.0F / c->u;
        c->v = 1.0F / c->v;
        
        if(a->screenPos.y == b->screenPos.y || b->screenPos.y == c->screenPos.y){
            drawSubPerspTri(device, a, b, c, texture);
        }else{
            float ca_y_length = (float) (c->screenPos.y - a->screenPos.y);
            float ba_y_length = (float) (b->screenPos.y - a->screenPos.y);
            
            float r = (float) (c->screenPos.x - a->screenPos.x) / ca_y_length;
            int x = r * ba_y_length;
            SHPoint screenPosTmp = SHPointMake(a->screenPos.x + x, b->screenPos.y);
            
            Vertex3D *vertexTmp = new Vertex3D();
            vertexTmp->screenPos = screenPosTmp;
            
            float ru = (float) (c->u - a->u) / ca_y_length;
            float iu = ru * ba_y_length;
            vertexTmp->u = iu;
            
            float rv = (float) (c->v - a->v) / ca_y_length;
            float iv = rv * ba_y_length;
            vertexTmp->v = iv;
            
            float rz = (float) (c->pos.z - a->pos.z) / ca_y_length;
            float iz = rz * ba_y_length;
            vertexTmp->pos.z = iz;
            
            drawSubPerspTri(device, a, b, vertexTmp, texture);
            drawSubPerspTri(device, vertexTmp, b, c, texture);
        }
        
    }
    
    void BasicDraw::drawSubPerspTri(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture){
        int y0 = a->screenPos.y;
        int y1 = c->screenPos.y;
        
        int yStep = y0;
        float leftR, rightR;
        Vertex3D *left;
        Vertex3D *right;
        float leftIz;
        float rightIz;
        float leftIu;
        float rightIu;
        float leftIv;
        float rightIv;
        
        float leftIzStep;
        float rightIzStep;
        float leftIuStep;
        float rightIuStep;
        float leftIvStep;
        float rightIvStep;
        
        float y_length = (y1 - y0);
        if(a->screenPos.y == b->screenPos.y){
            if(a->screenPos.x > b->screenPos.x){
                Vertex3D *tmp = a;
                a = b;
                b = tmp;
            }
            
            left = a;
            right = b;
            
            leftR = (float) (c->screenPos.x - a->screenPos.x) / y_length;
            rightR = (float) (c->screenPos.x - b->screenPos.x) / y_length;
            
            leftIz = left->pos.z;
            rightIz = right->pos.z;
            leftIu = left->u;
            rightIu = right->u;
            leftIv = left->v;
            rightIv = right->v;
            
            leftIzStep = (float) (c->pos.z - a->pos.z) / y_length;
            rightIzStep = (float) (c->pos.z - b->pos.z) / y_length;
            leftIuStep = (float) (c->u - a->u) / y_length;
            rightIuStep = (float) (c->u - b->u) / y_length;
            leftIvStep = (float) (c->v - a->v) / y_length;
            rightIvStep = (float) (c->v - b->v) / y_length;
            
        }else{
            if(b->screenPos.x > c->screenPos.x){
                Vertex3D *tmp = b;
                b = c;
                c = tmp;
            }
            
            left = a;
            right = a;
            
            leftR = (float) (b->screenPos.x - a->screenPos.x) / y_length;
            rightR = (float) (c->screenPos.x - a->screenPos.x) / y_length;
            
            leftIz = left->pos.z;
            rightIz = right->pos.z;
            leftIu = left->u;
            rightIu = right->u;
            leftIv = left->v;
            rightIv = right->v;
            
            leftIzStep = (float) (b->pos.z - a->pos.z) / y_length;
            rightIzStep = (float) (c->pos.z - a->pos.z) / y_length;
            leftIuStep = (float) (b->u - a->u) / y_length;
            rightIuStep = (float) (c->u - a->u) / y_length;
            leftIvStep = (float) (b->v - a->v) / y_length;
            rightIvStep = (float) (c->v - a->v) / y_length;
        }
        
        float leftX = left->screenPos.x;
        float rightX = right->screenPos.x;
        while(yStep <= y1){
            
            float xIz = leftIz;
            float xIu = leftIu;
            float xIv = leftIv;
            
            float xIzStep = (rightIz - leftIz) / y_length;
            float xIuStep = (rightIu - leftIu) / y_length;
            float xIvStep = (rightIv - leftIv) / y_length;
            
            for(int xStep = leftX; xStep <= rightX; xStep++){
                
                int realU = xIu / xIz * texture.width;
                int realV = xIv / xIz * texture.height;
                
                SHColor c = texture.getPixel(1, 0);
                
                device.setPixel((SHPoint){xStep, yStep}, c);
                
                xIz += xIzStep;
                xIu += xIuStep;
                xIv += xIvStep;
            }
            
            leftIz += leftIzStep;
            rightIz += rightIzStep;
            leftIu += leftIuStep;
            rightIu += rightIuStep;
            leftIv += leftIvStep;
            rightIv += rightIvStep;
            
            yStep++;
            leftX += leftR;
            rightX += rightR;
        }
    }
    
}
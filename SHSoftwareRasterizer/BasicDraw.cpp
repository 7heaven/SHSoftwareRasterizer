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
#include <chrono>
#include <thread>

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
    
    ////////////////////
    // 绘制2D纯色三角形
    ////////////////////
    void BasicDraw::drawTriangle(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color){
        
        //根据y值做简单排序
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
        
        //如果面积为零 返回
        if((a.y == b.y == c.y) || (a.x == b.x == c.x)) return;
        
        if(a.y == b.y || b.y == c.y){
            //当前状态已经是平顶三角形或者平底三角形 直接进入drawSubTri绘制
            drawSubTri(device, a, b, c, color);
        }else{
            //把当前三角形拆分为平顶三角形和平底三角形
            //三角形填充的过程是扫描线的形式，如果不是平顶三角形或者平底三角形则在扫描线进行到位于中间的顶点位置的时候需要做斜率的切换
            float r = (float) (c.x - a.x) / (float) (c.y - a.y);
            int x = r * (b.y - a.y);
            
            SHPoint tmp = SHPointMake(a.x + x, b.y);
            
            //对两个拆分后的三角形进行填充绘制
            drawSubTri(device, a, b, tmp, color);
            drawSubTri(device, b, tmp, c, color);
        }
    }
    
    ////////////////////
    // 绘制拆分后的三角形
    ////////////////////
    void BasicDraw::drawSubTri(IDevice &device, SHPoint a, SHPoint b, SHPoint c, SHColor color){
        int y0 = a.y;
        int y1 = c.y;
        
        int yStep = y0 < 0 ? 0 : y0;
        float leftXStep, rightXStep;
        SHPoint left, right;
    
        if(a.y == b.y){
            //平顶三角形
            
            //保证a在左边 b在右边
            if(a.x > b.x){
                SHPoint tmp = a;
                a = b;
                b = tmp;
            }
            
            //对三角形左右两条边做递增的计算
            left = a;
            right = b;
            
            //y每+1s时 两边的x递增值
            leftXStep = (float) (c.x - a.x) / (float) (y1 - y0);
            rightXStep = (float) (c.x - b.x) / (float) (y1 - y0);
            
        }else{
            //平底三角形
            
            //保证b在左边， c在右边
            if(b.x > c.x){
                SHPoint tmp = b;
                b = c;
                c = tmp;
            }
            
            //对三角形左右两条边做递增的计算
            left = a;
            right = a;
            
            //y每+1s时 两边的x递增值
            leftXStep = (float) (b.x - a.x) / (float) (y1 - y0);
            rightXStep = (float) (c.x - a.x) / (float) (y1 - y0);
        }
        
        float leftX = left.x;
        float rightX = right.x;
        
        //从上到下的绘制过程
        while(yStep <= y1){
            
            //扫描线绘制
            for(int xStep = (leftX < 0 ? 0 : leftX); xStep <= (rightX > device.getBounds().w ? device.getBounds().w : rightX); xStep++){
                device.setPixel((SHPoint){xStep, yStep}, color);
            }
            
            yStep++;
            
            if(yStep > device.getBounds().h) break;
            
            leftX += leftXStep;
            rightX += rightXStep;
        }
    }
    
    ////////////////////
    // 绘制带有透视纹理贴图的三角形
    ////////////////////
    void BasicDraw::drawPerspTriangle(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture, ILight &light){
        
        //根据屏幕y坐标做简单的排序
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
        
        //面积零时  返回
        if((a->screenPos.y == b->screenPos.y == c->screenPos.y) || (a->screenPos.x == b->screenPos.x == c->screenPos.x)) return;
        
        //基于Chris Hecker的透视纹理贴图算法, 文章地址:http://chrishecker.com/Miscellaneous_Technical_Articles
        //把本来呈非线性递增的u,v,z值转换为线性递增的u/z, v/z, 1/z,
        //在扫描线绘制的时候只需要每次增加预先计算出来的递增值，然后再用 u/z除以1/z, v/z除以1/z来得到正确的uv纹理的坐标
        
        //把所有u转换为u/z 所有v转换为v/z
        a->u = (a->pos.z == 0 ? 0 : a->u / a->pos.z);
        a->v = (a->pos.z == 0 ? 0 : a->v / a->pos.z);
        b->u = (b->pos.z == 0 ? 0 : b->u / b->pos.z);
        b->v = (b->pos.z == 0 ? 0 : b->v / b->pos.z);
        c->u = (c->pos.z == 0 ? 0 : c->u / c->pos.z);
        c->v = (c->pos.z == 0 ? 0 : c->v / c->pos.z);
        
        //把所有z转换为1/z
        a->pos.z = (a->pos.z == 0 ? 0 : 1.0F / a->pos.z);
        b->pos.z = (b->pos.z == 0 ? 0 : 1.0F / b->pos.z);
        c->pos.z = (c->pos.z == 0 ? 0 : 1.0F / c->pos.z);
        
        if(a->screenPos.y == b->screenPos.y || b->screenPos.y == c->screenPos.y){
            //当前状态已经是平顶三角形或者平底三角形 直接进入drawSubPerspTri绘制
            drawSubPerspTri(device, a, b, c, texture, light);
        }else{
            
            //把当前三角形拆分为平顶三角形和平底三角形
            //三角形填充的过程是扫描线的形式，如果不是平顶三角形或者平底三角形则在扫描线进行到位于中间的顶点位置的时候需要做斜率的切换
            
            float ca_y_length = (float) (c->screenPos.y - a->screenPos.y);
            float ba_y_length = (float) (b->screenPos.y - a->screenPos.y);
            
            float r = (float) (c->screenPos.x - a->screenPos.x) / ca_y_length;
            int x = r * ba_y_length;
            SHPoint screenPosTmp = SHPointMake(a->screenPos.x + x, b->screenPos.y);
            
            Vertex3D *vertexTmp = new Vertex3D();
            vertexTmp->screenPos = screenPosTmp;
            
            float ru = (float) (c->u - a->u) / ca_y_length;
            float iu = ru * ba_y_length;
            vertexTmp->u = a->u + iu;
            
            float rv = (float) (c->v - a->v) / ca_y_length;
            float iv = rv * ba_y_length;
            vertexTmp->v = a->v + iv;
            
            float rz = (float) (c->pos.z - a->pos.z) / ca_y_length;
            float iz = rz * ba_y_length;
            vertexTmp->pos.z = a->pos.z + iz;
            
            //对拆分后的三角面片进行绘制
            drawSubPerspTri(device, a, b, vertexTmp, texture, light);
            drawSubPerspTri(device, vertexTmp, b, c, texture, light);
            
            delete vertexTmp;
        }
        
    }
    
    void BasicDraw::drawSubPerspTri(IDevice &device, Vertex3D *a, Vertex3D *b, Vertex3D *c, Texture &texture, ILight &light){
        //扫描线从y0-y1
        int y0 = a->screenPos.y;
        int y1 = c->screenPos.y;
        
        int yStep = y0;
        float leftXStep, rightXStep;
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
        
        //计算左边的u/z, v/z, 1/z, x以及右边的u/z, v/z, 1/z, x的y轴递增量
        if(a->screenPos.y == b->screenPos.y){
            if(a->screenPos.x > b->screenPos.x){
                Vertex3D *tmp = a;
                a = b;
                b = tmp;
            }
            
            left = a;
            right = b;
            
            leftXStep = (float) (c->screenPos.x - a->screenPos.x) / y_length;
            rightXStep = (float) (c->screenPos.x - b->screenPos.x) / y_length;
            
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
            
            leftXStep = (float) (b->screenPos.x - a->screenPos.x) / y_length;
            rightXStep = (float) (c->screenPos.x - a->screenPos.x) / y_length;
            
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
            
            float x_length = (float) (rightX - leftX);
            if(x_length == 0) x_length = 1.0F;
            
            //计算x轴方向上的u/z, v/z, 1/z递增量
            float xIzStep = (rightIz - leftIz) / x_length;
            float xIuStep = (rightIu - leftIu) / x_length;
            float xIvStep = (rightIv - leftIv) / x_length;
            
            for(int xStep = leftX; xStep <= rightX; xStep++){
                
                //除以1/z得到当前扫描线位置的真实uv坐标
                float u = (xIz == 0 ? 0 : xIu / xIz);
                float v = (xIz == 0 ? 0 : xIv / xIz);
                
                //把uv转换到纹理坐标
                float realU = u * texture.width;
                float realV = v * texture.height;
                
                //获取纹理坐标对应颜色值
                SHColor c = texture.getPixel(realU, realV);
                
                //光线计算
                if(&light != NULL){
                    c = light.compute(c);
                }
                
                float z = 1 / xIz;
                
                if(z <= device.getZDepth(SHPointMake(xStep, yStep))){
                    //绘制扫描线位置
                    device.setPixel((SHPoint){xStep, yStep}, c);
                    device.setZDepth(SHPointMake(xStep, yStep), z);
                }
                
                //x轴方向的相关量递增
                xIz += xIzStep;
                xIu += xIuStep;
                xIv += xIvStep;
            }
            
            //y轴方向的相关量递增
            leftIz += leftIzStep;
            rightIz += rightIzStep;
            leftIu += leftIuStep;
            rightIu += rightIuStep;
            leftIv += leftIvStep;
            rightIv += rightIvStep;
            
            leftX += leftXStep;
            rightX += rightXStep;
            
            yStep++;
        }
    }
    
}
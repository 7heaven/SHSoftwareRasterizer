//
//  BasicGeometry.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef BasicGeometry_h
#define BasicGeometry_h

typedef struct{
    int x;
    int y;
}SHPoint;

typedef struct{
    float x;
    float y;
}SHPointF;

typedef struct{
    float x;
    float y;
    float z;
}SHPoint3D;

typedef struct{
    SHPointF a;
    SHPointF b;
    SHPointF c;
}SHTriangle;

typedef struct{
    SHPoint3D a;
    SHPoint3D b;
    SHPoint3D c;
}SHTriangle3D;

typedef struct{
    unsigned int a;
    unsigned int b;
    unsigned int c;
}SHSimpleTri;

typedef struct{
    int x;
    int y;
    int w;
    int h;
}SHRect;

typedef struct{
    float x;
    float y;
    float z;
    float w;
}SHVector3D;

typedef struct{
    unsigned char a;
    unsigned char r;
    unsigned char g;
    unsigned char b;
}SHColor;

static inline SHPoint SHPointMake(int x, int y){
    return (SHPoint){x, y};
}

static inline SHPointF SHPointFMake(float x, float y){
    return (SHPointF){x, y};
}

static inline SHPoint3D SHPoint3DMake(float x, float y, float z){
    return (SHPoint3D){x, y, z};
}

static inline SHRect SHRectMake(int x, int y, int w, int h){
    return (SHRect){x, y, w, h};
}

static inline SHVector3D SHVector3DMake(float x, float y, float z, float w){
    return (SHVector3D){x, y, z, w};
}

static inline SHColor SHColorMake(unsigned int color){
    return (SHColor){static_cast<unsigned char>((color >> 24) & 0xFF),
                     static_cast<unsigned char>((color >> 16) & 0xFF),
                     static_cast<unsigned char>((color >> 8) & 0xFF),
                     static_cast<unsigned char>(color & 0xFF)};
}


#endif /* BasicGeometry_h */

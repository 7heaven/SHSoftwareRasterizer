//
//  ViewController.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/7.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "ViewController.h"
#import "SHSoftwareCanvas.h"
#import "Matrix44.hpp"
#import "BasicDraw.hpp"
#import "BoxObject.h"

#define N 500.0F

@implementation ViewController{
    SHSoftwareCanvas *canvas;
    NSTimer *timer;
    
    float angle;
    
    sh::Matrix44 *_transform;
    sh::Matrix44 *_projection;
    
    BoxObject *_box;
    
    int _intx;
    int _inty;
    
    int _tx;
    int _ty;
    
    CGPoint _dragPoint;
    CGPoint centerPoint;
    CGFloat _previousRadianX;
    CGFloat _previousRadianY;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    canvas = [[SHSoftwareCanvas alloc] init];
    canvas.frame = self.view.bounds;
    
    [self.view addSubview:canvas];
    
    NSTrackingAreaOptions options = (NSTrackingActiveAlways | NSTrackingInVisibleRect |
                                     NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved);
    
    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:self.view.bounds
                                                        options:options
                                                          owner:self
                                                       userInfo:nil];
    
    [self.view addTrackingArea:area];
    
    _transform = sh::Matrix44::identity();
    _projection = [self getPerspectiveMatrixWithFovy:3.1415926f * 0.5f aspect:self.view.frame.size.width / self.view.frame.size.height zn:1.0F zf:500.0F];
    
    _box = [[BoxObject alloc] initWithLength:150];
    
    centerPoint = CGPointMake(self.view.frame.size.width / 2, self.view.frame.size.height / 2);
}

- (void) rotateX:(float) x y:(float) y{
    
    sh::Matrix44 *xMatrix = [self xRotateMatrix:x];
    sh::Matrix44 *yMatrix = [self zRotateMatrix:y];
    
    *_transform *= *xMatrix;
    *_transform *= *yMatrix;
    
}

- (sh::Matrix44 *) xRotateMatrix:(float) radian{
    float cosX = cosf(radian);
    float sinX = sinf(radian);
    
    sh::Matrix44 *xMatrix = new sh::Matrix44(1,    0,     0, 0,
                                             0, cosX, -sinX, 0,
                                             0, sinX,  cosX, 0,
                                             0,    0,     0, 1);
    
    return xMatrix;
}

- (sh::Matrix44 *) yRotateMatrix:(float) radian{
    float cosY = cosf(radian);
    float sinY = sinf(radian);
    
    sh::Matrix44 *yMatrix = new sh::Matrix44( cosY, 0, sinY, 0,
                                                 0, 1,    0, 0,
                                             -sinY, 0, cosY, 0,
                                                 0, 0,    0, 1);
    
    return yMatrix;
}

- (sh::Matrix44 *) zRotateMatrix:(float) radian{
    float cosZ = cosf(radian);
    float sinZ = sinf(radian);
    
    sh::Matrix44 *zMatrix = new sh::Matrix44(cosZ, -sinZ, 0, 0,
                                             sinZ,  cosZ, 0, 0,
                                                0,     0, 1, 0,
                                                0,     0, 0, 1);
    
    return zMatrix;
}

- (void) mouseDown:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    if (isnan(_dragPoint.x) || isnan(_dragPoint.y)) _dragPoint = CGPointMake(0, 0);
    if (!_box) _box = [[BoxObject alloc] initWithLength:150];
    
    _intx = location.x;
    _inty = location.y;
}

- (sh::Matrix44 *) getPerspectiveMatrixWithFovy:(float) fovy aspect:(float) aspect zn:(float) zn zf:(float) zf{
    float fax = 1.0F / (float) tan(fovy * 0.5F);
    
    sh::Matrix44 *projectMat = new sh::Matrix44((float)(fax / aspect),            0,                    0, 0,
                                                                    0, (float)(fax),                    0, 0,
                                                                    0,            0,       zf / (zf - zn), 1,
                                                                    0,            0, -zn * zf / (zf - zn), 0);
    
    return projectMat;
}

- (SHPoint)perspective:(SHVector3D)vector {
    CGFloat x = N * (vector.x / vector.z);
    CGFloat y = N * (vector.y / vector.z);
    
    return SHPointMake(x + centerPoint.x, y + centerPoint.y);
}

- (void) mouseDragged:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    _tx = location.x - _intx;
    _ty = location.y - _inty;
    
    _dragPoint = CGPointMake(_dragPoint.x + (_tx - _dragPoint.x) * 0.01, _dragPoint.y + (_ty - _dragPoint.y) * 0.01);
    
    [canvas flushWithColor:(SHColor){0, 0, 0, 0}];
    _transform->toIdentity();
    [self rotateX:(_ty - centerPoint.y) / 200 + _previousRadianY y:(_tx - centerPoint.x) / 200 + _previousRadianX];
    
    for(int i = 0; i < _box.triangleArray.count; i++){
        SHSimpleTri tri = getSimpleTri(_box.triangleArray[i]);
        
        SHVector3D a = getVector3D(_box.vectorArray[tri.a]);
        SHVector3D b = getVector3D(_box.vectorArray[tri.b]);
        SHVector3D c = getVector3D(_box.vectorArray[tri.c]);
        
        a = *_transform * a;
        b = *_transform * b;
        c = *_transform * c;
        
        a.z += 600;
        b.z += 600;
        c.z += 600;
        
        SHPoint pa = [self perspective:a];
        SHPoint pb = [self perspective:b];
        SHPoint pc = [self perspective:c];
        
        BOOL shouldPass = [self crossProductWith:(SHPoint){pb.x - pa.x, pb.y - pa.y}
                                              p1:(SHPoint){pc.x - pa.x, pc.y - pa.y}];
        
        if(!shouldPass) continue;
        
//        SHVector3D a2D = *_projection * a;
//        SHVector3D b2D = *_projection * b;
//        SHVector3D c2D = *_projection * c;
//        
//        SHPoint pa = SHPointMake(a2D.x + centerPoint.x, a2D.y + centerPoint.y);
//        SHPoint pb = SHPointMake(b2D.x + centerPoint.x, b2D.y + centerPoint.y);
//        SHPoint pc = SHPointMake(c2D.x + centerPoint.x, c2D.y + centerPoint.y);
        
        sh::BasicDraw::drawLine(*[canvas getNativePtr], pa, pb, SHColorMake(0xFF0099CC));
        sh::BasicDraw::drawLine(*[canvas getNativePtr], pb, pc, SHColorMake(0xFF0099CC));
        sh::BasicDraw::drawLine(*[canvas getNativePtr], pc, pa, SHColorMake(0xFF0099CC));
        
    }
    
//    sh::BasicDraw::drawLine(*[canvas getNativePtr], (SHPoint){150, 150}, (SHPoint){static_cast<int>(location.x), static_cast<int>(self.view.bounds.size.height - location.y)}, (SHColor){0xFF, 0x00, 0x99, 0xCC});
//    
    [canvas update];
    
    
}

- (BOOL) crossProductWith:(SHPoint) p0 p1:(SHPoint) p1{
    int s = p0.x * p1.y - p1.x * p0.y;
    
    return s <= 0;
}

- (NSDictionary *)crossProWithV0:(SHVector3D)v0 v1:(SHVector3D)v1 center:(CGPoint)cPoint {
    CGFloat t_x = v0.y * v1.z - v0.z * v1.y;
    CGFloat t_y = v0.z * v1.x - v0.x * v1.z;
    CGFloat t_z = v0.x * v1.y - v0.y * v1.x;
    
    CGFloat m = sqrt(t_x * t_x + t_y * t_y + t_z * t_z);
    //向量单位化
    t_x /= m;
    t_y /= m;
    //不开方,以减少运算量
    return @{ @"cross" : @(t_x * t_x + t_y * t_y), @"z" : @(t_z) };
}

- (void)mouseUp:(NSEvent *)theEvent {
    CGPoint location = theEvent.locationInWindow;
    
    _previousRadianX = (_tx - centerPoint.x) / 200;
    _previousRadianY = (_ty - centerPoint.y) / 200;
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end

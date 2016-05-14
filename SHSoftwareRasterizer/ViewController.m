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
    
    _box = [[BoxObject alloc] initWithLength:150];
    
    centerPoint = CGPointMake(self.view.frame.size.width / 2, self.view.frame.size.height / 2);
}

- (void) rotateX:(float) x y:(float) y{
    _transform->toIdentity();
    
    float cosX = cosf(x);
    float sinX = sinf(x);
    float cosY = cosf(y);
    float sinY = sinf(y);
    
    sh::Matrix44 *xMatrix = new sh::Matrix44(1,    0,     0, 0,
                                             0, cosX, -sinX, 0,
                                             0, sinX,  cosX, 0,
                                             0,    0,     0, 1);
    
    sh::Matrix44 *yMatrix = new sh::Matrix44( cosY, 0, sinY, 0,
                                                 0, 1,    0, 0,
                                             -sinY, 0, cosY, 0,
                                                 0, 0,    0, 1);
    
    *_transform *= *xMatrix;
    *_transform *= *yMatrix;
    
}

- (void) mouseDown:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    if (isnan(_dragPoint.x) || isnan(_dragPoint.y)) _dragPoint = CGPointMake(0, 0);
    if (!_box) _box = [[BoxObject alloc] initWithLength:150];
    
    _intx = location.x;
    _inty = location.y;
}

- (SHPoint)perspective:(SHVector3D)vector {
    CGFloat x = N * (vector.x / vector.z) + centerPoint.x;
    CGFloat y = N * (vector.y / vector.z) + centerPoint.y;
    
    return SHPointMake(x, y);
}

- (void) mouseDragged:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    _tx = location.x - _intx;
    _ty = location.y - _inty;
    
    _dragPoint = CGPointMake(_dragPoint.x + (_tx - _dragPoint.x) * 0.01, _dragPoint.y + (_ty - _dragPoint.y) * 0.01);
    
    [canvas flushWithColor:(SHColor){0, 0, 0, 0}];
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
        
        SHPoint a2D = [self perspective:a];
        SHPoint b2D = [self perspective:b];
        SHPoint c2D = [self perspective:c];
        
        sh::BasicDraw::drawLine(*[canvas getNativePtr], a2D, b2D, SHColorMake(0xFF0099CC));
        sh::BasicDraw::drawLine(*[canvas getNativePtr], b2D, c2D, SHColorMake(0xFF0099CC));
        sh::BasicDraw::drawLine(*[canvas getNativePtr], c2D, a2D, SHColorMake(0xFF0099CC));
        
    }
    
//    sh::BasicDraw::drawLine(*[canvas getNativePtr], (SHPoint){150, 150}, (SHPoint){static_cast<int>(location.x), static_cast<int>(self.view.bounds.size.height - location.y)}, (SHColor){0xFF, 0x00, 0x99, 0xCC});
//    
    [canvas update];
    
    
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

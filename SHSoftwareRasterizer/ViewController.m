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
#import "Object3DEntity.h"
#import <sys/time.h>

#define N 500.0F

#define compareByte(a, b) [a.description isEqualToString:b]

@implementation ViewController{
    SHSoftwareCanvas *canvas;
    NSTimer *timer;
    
    float angle;
    
    sh::Matrix44 *_transform;
    sh::Matrix44 *_projection;
    
    Object3DEntity *_box;
    
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
//    _projection = [self getPerspectiveMatrixWithFovy:M_PI_2 aspect:self.view.frame.size.width / self.view.frame.size.height zn:1.0F zf:500.0F];
    
    _projection = [self getPerspectiveMatrix];
    
    _box = [[BoxObject alloc] initWithLength:150];
    
    centerPoint = CGPointMake(self.view.frame.size.width / 2, self.view.frame.size.height / 2);
    
    [self.fpsLabel removeFromSuperview];
    [self.view addSubview:self.fpsLabel];
    
    [self.fileButton removeFromSuperview];
    [self.view addSubview:self.fileButton];
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
    float fax = 1.0F / (float) tan(fovy * 0.5F * (M_PI / 180));
    
    sh::Matrix44 *projectMat = new sh::Matrix44((float)(fax),            0,                    0, 0,
                                                           0, (float)(fax),                    0, 0,
                                                           0,            0,       zf / (zf - zn), 1,
                                                           0,            0, -zn * zf / (zf - zn), 0);
    
    return projectMat;
}

- (sh::Matrix44 *) getPerspectiveMatrix{
    sh::Matrix44 *projectMat = new sh::Matrix44(10.0F, 0, 0, 0,
                                                0, 10.0F, 0, 0,
                                                0, 0, 10.0F, 0,
                                                0, 0, 1.0F/(float) N, 0);
    
    return projectMat;
}

- (void) mouseDragged:(NSEvent *)theEvent{
    timeval time;
    gettimeofday(&time, NULL);
    
    CGPoint location = theEvent.locationInWindow;
    
    _tx = location.x - _intx;
    _ty = location.y - _inty;
    
    _dragPoint = CGPointMake(_dragPoint.x + (_tx - _dragPoint.x) * 0.01, _dragPoint.y + (_ty - _dragPoint.y) * 0.01);
    
//    [canvas flushWithColor:(SHColor){0, 0, 0, 0}];
    [canvas flushWithDirtyRect:SHRectMake(centerPoint.x - 150, centerPoint.y - 150, 300, 300) color:SHColorMake(0x0)];
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
        
        a.z += 550;
        b.z += 550;
        c.z += 550;
        
        SHVector3D a2D = *_projection * a;
        SHVector3D b2D = *_projection * b;
        SHVector3D c2D = *_projection * c;
        
        SHPoint pa = SHPointMake(a2D.x / a2D.w + centerPoint.x, a2D.y / a2D.w + centerPoint.y);
        SHPoint pb = SHPointMake(b2D.x / b2D.w + centerPoint.x, b2D.y / b2D.w + centerPoint.y);
        SHPoint pc = SHPointMake(c2D.x / c2D.w + centerPoint.x, c2D.y / c2D.w + centerPoint.y);
        
        BOOL shouldPass = [self crossProductWith:(SHPoint){pb.x - pa.x, pb.y - pa.y}
                                              p1:(SHPoint){pc.x - pa.x, pc.y - pa.y}];
        
        if(!shouldPass) continue;
        
        sh::BasicDraw::drawLine(*[canvas getNativePtr], pa, pb, SHColorMake(0xFF0099CC));
        sh::BasicDraw::drawLine(*[canvas getNativePtr], pb, pc, SHColorMake(0xFF0099CC));
        sh::BasicDraw::drawLine(*[canvas getNativePtr], pc, pa, SHColorMake(0xFF0099CC));
        
    }

    [canvas update];
    
    timeval aftertime;
    gettimeofday(&aftertime, NULL);
    __int32_t gap = aftertime.tv_usec - time.tv_usec;
    int fps = 1000 / gap;
    
    [self.fpsLabel setStringValue:[NSString stringWithFormat:@"FPS:%d/S", gap]];
    
}

- (BOOL) crossProductWith:(SHPoint) p0 p1:(SHPoint) p1{
    int s = p0.x * p1.y - p1.x * p0.y;
    
    return s <= 0;
}

- (void)mouseUp:(NSEvent *)theEvent {
    CGPoint location = theEvent.locationInWindow;
    
    _previousRadianX = (_tx - centerPoint.x) / 200;
    _previousRadianY = (_ty - centerPoint.y) / 200;
}

- (Object3DEntity *)parse3DSFileWithPath:(NSURL *)path {
    NSLog(@"path:%@", path);

    NSData *fileData = [NSData dataWithContentsOfURL:path];
    if (fileData) {
        NSLog(@"path:%@", path);
        Object3DEntity *object3D = [[Object3DEntity alloc] init];
        
        NSUInteger totalBytesCount = [fileData length];
        
        NSInteger index = 0;
        
        NSData *byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
        
        index += 2;
        
        NSData *chunkLength = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:4];
        
        index += 4;
        
        NSInteger totalLength = 0;
        while (index < totalBytesCount) {
//            if (self.delegate && [self.delegate respondsToSelector:@selector(fileParser:parseProgress:)]) {
//                [self.delegate fileParser:self parseProgress:totalLength > 0 ? (float)index / (float)totalLength : 0];
//            }
            
            int length;
            
            [chunkLength getBytes:&length length:sizeof(length)];
            
            if (compareByte(byteData, @"<4d4d>")) {
                [chunkLength getBytes:&totalLength length:sizeof(totalLength)];
                // file header
            } else if (compareByte(byteData, @"<3d3d>")) {
            } else if (compareByte(byteData, @"<0041>")) {
            } else if (compareByte(byteData, @"<0040>")) {
                byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:1];
                index += 1;
                
                char size;
                
                [byteData getBytes:&size length:sizeof(size)];
                while (size != 0) {
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:1];
                    index += 1;
                    
//                    if (self.delegate && [self.delegate respondsToSelector:@selector(fileParser:parseProgress:)]) {
//                        [self.delegate fileParser:self
//                                    parseProgress:totalLength > 0 ? (float)index / (float)totalLength : 0];
//                    }
                    
                    [byteData getBytes:&size length:sizeof(size)];
                }
                
            } else if (compareByte(byteData, @"<1041>")) {
                byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
                
                index += 2;
                short size;
                [byteData getBytes:&size length:sizeof(size)];
                for (int i = 0; i < size; i++) {
//                    if (self.delegate && [self.delegate respondsToSelector:@selector(fileParser:parseProgress:)]) {
//                        [self.delegate fileParser:self
//                                    parseProgress:totalLength > 0 ? (float)index / (float)totalLength : 0];
//                    }
                    
                    float x, y, z;
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:4];
                    
                    [byteData getBytes:&x length:sizeof(x)];
                    
                    index += 4;
                    
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:4];
                    
                    [byteData getBytes:&y length:sizeof(y)];
                    
                    index += 4;
                    
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:4];
                    
                    [byteData getBytes:&z length:sizeof(z)];
                    
                    index += 4;
                    
                    [object3D.vectorArray addObject:Vector3DMake(x, y, z)];
                }
            } else if (compareByte(byteData, @"<2041>")) {
                byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
                
                index += 2;
                
                short size;
                
                [byteData getBytes:&size length:sizeof(size)];
                
                for (int i = 0; i < size; i++) {
//                    if (self.delegate && [self.delegate respondsToSelector:@selector(fileParser:parseProgress:)]) {
//                        [self.delegate fileParser:self
//                                    parseProgress:totalLength > 0 ? (float)index / (float)totalLength : 0];
//                    }
                    
                    short a, b, c;
                    
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
                    [byteData getBytes:&a length:sizeof(a)];
                    
                    index += 2;
                    
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
                    [byteData getBytes:&b length:sizeof(b)];
                    
                    index += 2;
                    
                    byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
                    [byteData getBytes:&c length:sizeof(c)];
                    
                    index += 4;
                    
                    [object3D.triangleArray addObject:TSimple3DMake(a, b, c)];
                }
                
            } else if (compareByte(byteData, @"<4041>")) {
                index += length - 6;
            } else {
                index += length - 6;
            }
            
            byteData = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:2];
            
            index += 2;
            
            chunkLength = [NSData dataWithBytes:((char *)[fileData bytes] + index)length:4];
            
            index += 4;
        }
        
        return object3D;
    }
    
    return nil;
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

- (IBAction)fileButtonClick:(id)sender {
    
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    
    // This method displays the panel and returns immediately.
    // The completion handler is called when the user selects an
    // item or cancels the panel.
    [panel beginWithCompletionHandler:^(NSInteger result){
        if (result == NSFileHandlingPanelOKButton) {
            NSURL *_selectedDoc = [[panel URLs] objectAtIndex:0];
            
            NSLog(@"_sel:%@", _selectedDoc);
            
            Object3DEntity *entity = [self parse3DSFileWithPath:_selectedDoc];
            
            if(entity != nil){
                _box = entity;
            }
            
        }
        
    }];
}

@end

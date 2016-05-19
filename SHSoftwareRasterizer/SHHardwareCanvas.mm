//
//  SHHardwareCanvas.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "SHHardwareCanvas.h"
#import "MacDevice.hpp"
#import "BasicGeometry.h"

@implementation SHHardwareCanvas{
    MacDevice *_nativePtr;
    
    float *_zDepth;
    unsigned long _canvasPixelSize;
}

- (instancetype) init{
    if(self = [super init]){
        [self initProcess];
    }
    
    return self;
}

- (void) initProcess{
    _nativePtr = new MacDevice(self);
    
    [self initRawDataBackend];
    [self initDepthStore];
}

- (void) initRawDataBackend{
    
}

- (void) initDepthStore{
    
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
}


# pragma mark - override


- (sh::IDevice *) getNativePtr{
    return _nativePtr;
}

- (float) getZDepth:(SHPoint)pos{
    int position = pos.y * self.frame.size.width + pos.x;
    if(position < 0 || position > _canvasPixelSize) return 0;
    
    return _zDepth[position];
    
}

- (void) setZDepth:(float) zDepth position:(SHPoint) pos{
    int position = pos.y * self.frame.size.width + pos.x;
    if(position < 0 || position > _canvasPixelSize) return;
    
    _zDepth[position] = zDepth;
}

- (void) flushWithDirtyRect:(SHRect) dirtyRect color:(SHColor) color{
    
}

- (void) flushWithColor:(SHColor) color{
    
}

- (void) setPixel:(SHPoint) position color:(SHColor) color{
    
}

- (void) setPixels:(SHPoint[]) positions color:(SHColor) color{
    
}

- (SHRect) getBounds{
    return SHRectMake(0, 0, self.frame.size.width, self.frame.size.height);
}

@end

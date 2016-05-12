//
//  SHCanvas.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "SHCanvas.h"
#include <OpenGL/gl.h>

#define INSTINCT_SIZE CGSizeMake(20, 20)

@implementation SHCanvas{
    CGImageRef imageBackend;
    unsigned char *rawData;
    CGSize backendSize;
    
    SHColor backgroundColor;
}

- (instancetype) initWithBackgroundColor:(SHColor) color{
    if(self = [super init]){
        backgroundColor = color;
        [self initImageBackend];
    }
    
    return self;
}

- (instancetype) init{
    if(self = [super init]){
        [self initImageBackend];
    }
    
    return self;
}

- (instancetype) initWithCoder:(NSCoder *)coder{
    if(self = [super initWithCoder:coder]){
        [self initImageBackend];
    }
    
    return self;
}

- (void) initImageBackend{
    self.layer = [CALayer layer];
    imageBackend = [self createCGImageWithSize:self.bounds.size.width == 0 ? INSTINCT_SIZE : self.bounds.size];
    self.layer.contents = (__bridge id _Nullable)(imageBackend);
}

- (void) setPixel:(SHPoint) position color:(SHColor) color{
    
    int positionOffset = (self.bounds.size.width * position.y + position.x) * 3;
    
    rawData[positionOffset] = color.r;
    rawData[positionOffset + 1] = color.g;
    rawData[positionOffset + 2] = color.b;
    
    [self setNeedsDisplay:YES];
    [self displayIfNeeded];
}

- (void) setFrame:(NSRect)frame{
    [super setFrame:frame];
    
    [self initImageBackend];
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
}

- (CGImageRef) createCGImageWithSize:(CGSize) size{
    
    backendSize = size;
    
    if(&backgroundColor == nil){
        backgroundColor = (SHColor){0xFF, 0xFF, 0xFF, 0xFF};
    }
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    rawData = (unsigned char*) malloc(size.height * size.width * 3);
    for(int i = 0; i < size.width * size.height; i++){
        rawData[i * 3] = backgroundColor.r;
        rawData[i * 3 + 1] = backgroundColor.g;
        rawData[i * 3 + 2] = backgroundColor.b;
    }
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                              rawData,
                                                              size.width * size.height * 3,
                                                              NULL);
    
    CGImageRef image = CGImageCreate(size.width,
                                      size.height,
                                      8,
                                      24,
                                      3 * size.width,
                                      colorSpace,
                                      kCGBitmapByteOrderDefault,
                                      provider,
                                      NULL,
                                      false,
                                      kCGRenderingIntentDefault);
    
    CFRelease(colorSpace);
    CFRelease(provider);
    
    return image;
}

- (void) dealloc{
    free(rawData);
}

@end

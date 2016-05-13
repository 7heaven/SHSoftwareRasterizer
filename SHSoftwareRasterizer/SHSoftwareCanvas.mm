//
//  SHCanvas.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "SHSoftwareCanvas.h"

#define INSTINCT_SIZE CGSizeMake(20, 20)

@implementation SHSoftwareCanvas{
    CGImageRef _imageBackend;
    unsigned char *_rawData;
    CGSize _backendSize;
    unsigned long _rawDataSize;
    unsigned long _canvasPixelSize;
    
    SHColor _backgroundColor;
}

- (instancetype) initWithBackgroundColor:(SHColor) color{
    if(self = [super init]){
        _backgroundColor = color;
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
    
    CGSize size = self.bounds.size.width == 0 ? INSTINCT_SIZE : self.bounds.size;
    
    _canvasPixelSize = size.width * size.height;
    _rawDataSize = _canvasPixelSize * 3;
    
    _rawData = (unsigned char*) malloc(size.height * size.width * 3);
    for(int i = 0; i < _canvasPixelSize; i++){
        _rawData[i * 3] = _backgroundColor.r;
        _rawData[i * 3 + 1] = _backgroundColor.g;
        _rawData[i * 3 + 2] = _backgroundColor.b;
    }
    
    _imageBackend = [self createCGImageWithSize:size];
    self.image = [[NSImage alloc] initWithCGImage:_imageBackend size:size];
}



- (void) drawLineFrom:(SHPoint) p0 to:(SHPoint) p1 color:(SHColor) color{
    float x0 = p0.x;
    float y0 = p0.y;
    float x1 = p1.x;
    float y1 = p1.y;
    int dx = fabsf(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = fabsf(y1-y0), sy = y0<y1 ? 1 : -1;
    int err = (dx>dy ? dx : -dy)/2, e2;
    
    for(;;){
        [self setPixel:(SHPoint){x0, y0} color:color];
        if (x0==x1 && y0==y1) break;
        e2 = err;
        if (e2 >-dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
    
}

- (void) setPixel:(SHPoint) position color:(SHColor) color{
    
    int positionOffset = (self.bounds.size.width * position.y + position.x) * 3;
    
    if(positionOffset < 0 || positionOffset > _rawDataSize) return;
    
    _rawData[positionOffset] = color.r;
    _rawData[positionOffset + 1] = color.g;
    _rawData[positionOffset + 2] = color.b;
}

- (void) flushWithColor:(SHColor) color{
    for(int i = 0; i < _canvasPixelSize; i++){
        _rawData[i * 3] = color.r;
        _rawData[i * 3 + 1] = color.g;
        _rawData[i * 3 + 2] = color.b;
    }
}

- (void) update{
    _imageBackend = [self createCGImageWithSize:self.bounds.size];
    self.image = [[NSImage alloc] initWithCGImage:_imageBackend size:self.bounds.size];
}

- (void) setFrame:(NSRect)frame{
    [super setFrame:frame];
    
    [self initImageBackend];
}

- (CGImageRef) createCGImageWithSize:(CGSize) size{
    
    _backendSize = size;
    
    if(&_backgroundColor == nil){
        _backgroundColor = (SHColor){0xFF, 0xFF, 0xFF, 0xFF};
    }
    
    CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
    
    CGDataProviderRef provider = CGDataProviderCreateWithData(NULL,
                                                              _rawData,
                                                              _rawDataSize,
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
                                      NO,
                                      kCGRenderingIntentDefault);
    
    CFRelease(colorSpace);
    CFRelease(provider);
    
    return image;
}

- (void) dealloc{
    self.image = nil;
    CFRelease(_imageBackend);
    free(_rawData);
}

@end

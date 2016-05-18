//
//  SHCanvas.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "SHSoftwareCanvas.h"
#import "MacDevice.hpp"

#define INSTINCT_SIZE CGSizeMake(20, 20)

@implementation SHSoftwareCanvas{
    CGImageRef _imageBackend;
    unsigned char *_rawData;
    CGSize _backendSize;
    unsigned long _rawDataSize;
    unsigned long _canvasPixelSize;
    
    SHColor _backgroundColor;
    
    MacDevice *_nativePtr;
    
    float *_zDepth;
}

- (instancetype) initWithBackgroundColor:(SHColor) color{
    if(self = [super init]){
        _backgroundColor = color;
        [self initProcess];
    }
    
    return self;
}

- (instancetype) init{
    if(self = [super init]){
        [self initProcess];
    }
    
    return self;
}

- (instancetype) initWithCoder:(NSCoder *)coder{
    if(self = [super initWithCoder:coder]){
        [self initProcess];
    }
    
    return self;
}

- (void) initProcess{
    _nativePtr = new MacDevice(self);
    
    [self initImageBackend];
    [self initZDepthMap];
}

- (void) initZDepthMap{
    _zDepth = (float *) malloc(sizeof(float) * _canvasPixelSize);
    memset(_zDepth, 600, sizeof(float) * _canvasPixelSize);
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

- (void) setPixel:(SHPoint) position color:(SHColor) color{
    
    int positionOffset = (self.bounds.size.width * position.y + position.x) * 3;
    
    if(positionOffset < 0 || positionOffset > _rawDataSize) return;
    
    _rawData[positionOffset] = color.r;
    _rawData[positionOffset + 1] = color.g;
    _rawData[positionOffset + 2] = color.b;
}

- (void) setPixels:(SHPoint [])positions color:(SHColor)color{
    size_t length = sizeof(&positions) / sizeof(positions[0]);
    
    NSLog(@"length:%zu", length);
    
    for(int i = 0; i < length; i++){
        [self setPixel:positions[i] color:color];
    }
}

- (void) flushWithDirtyRect:(SHRect) dirtyRect color:(SHColor) color{
    
    if(dirtyRect.x < 0 || dirtyRect.y < 0 || dirtyRect.x + dirtyRect.w > self.frame.size.width || dirtyRect.y + dirtyRect.h > self.frame.size.height) return;
    
    for(int i = dirtyRect.y; i < dirtyRect.y + dirtyRect.h; i++){
        int start = dirtyRect.x + i * self.frame.size.width;
        for(int j = start; j < start + dirtyRect.w; j++){
            _rawData[j * 3] = color.r;
            _rawData[j * 3 + 1] = color.g;
            _rawData[j * 3 + 2] = color.b;
        }
    }
}

- (void) flushWithColor:(SHColor) color{
    for(int i = 0; i < _canvasPixelSize; i++){
        _rawData[i * 3] = color.r;
        _rawData[i * 3 + 1] = color.g;
        _rawData[i * 3 + 2] = color.b;
    }
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

- (SHRect) getBounds{
    return SHRectMake(0, 0, self.frame.size.width, self.frame.size.height);
}

- (void) update{
    _imageBackend = [self createCGImageWithSize:self.bounds.size];
    self.image = [[NSImage alloc] initWithCGImage:_imageBackend size:self.bounds.size];
    memset(_zDepth, 600, sizeof(float) * _canvasPixelSize);
}

- (void) setFrame:(NSRect)frame{
    [super setFrame:frame];
    
    [self initImageBackend];
    [self initZDepthMap];
}

- (CGImageRef) createCGImageWithSize:(CGSize) size{
    
    _backendSize = size;
    
    if(&_backgroundColor == nil){
        _backgroundColor = (SHColor){0, 0, 0, 0};
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

- (sh::IDevice *) getNativePtr{
    return _nativePtr;
}

- (void) dealloc{
    self.image = nil;
    CFRelease(_imageBackend);
    free(_rawData);
    delete _nativePtr;
    free(_zDepth);
}

@end

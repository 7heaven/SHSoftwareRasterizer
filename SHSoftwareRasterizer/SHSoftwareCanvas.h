//
//  SHCanvas.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "BasicGeometry.h"
#import "IDevice_osx.h"
#import "IDevice.h"

@interface SHSoftwareCanvas : NSImageView <IDevice_osx>

- (instancetype) initWithBackgroundColor:(SHColor) color;

- (void) drawLineFrom:(SHPoint) p0 to:(SHPoint) p1 color:(SHColor) color;

- (void) setPixel:(SHPoint) position color:(SHColor) color;
- (void) setPixels:(SHPoint[]) positions color:(SHColor) color;

- (void) flushWithColor:(SHColor) color;

- (void) update;

- (IDevice *) getNativePtr;

@end

class SHSoftwareDevice : public IDevice{
public:
    SHSoftwareDevice(SHSoftwareCanvas *canvas);
    
    void update();
    
    void setPixel(SHPoint position, SHColor color);
    void setPixels(SHPoint position[], SHColor color);
    void flush(SHColor color);
private:
    SHSoftwareCanvas *_canvas;
};

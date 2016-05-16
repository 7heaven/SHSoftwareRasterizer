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

- (void) update;

- (sh::IDevice *) getNativePtr;

@end

class SHSoftwareDevice : public sh::IDevice{
public:
    SHSoftwareDevice(SHSoftwareCanvas *canvas);
    
    void update();
    
    void setPixel(SHPoint position, SHColor color);
    void setPixels(SHPoint position[], SHColor color);
    
    void flush(SHRect dirtyRect, SHColor color);
    void flush(SHColor color);
    
    float getZDepth(SHPoint pos);
private:
    SHSoftwareCanvas *_canvas;
};

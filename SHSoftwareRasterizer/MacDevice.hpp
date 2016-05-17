//
//  MacDevice.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef MacDevice_h
#define MacDevice_h

#include "IDevice.h"
#include "BasicGeometry.h"
#include "IDevice_osx.h"

class MacDevice : public sh::IDevice{
public:
    MacDevice(id<IDevice_osx> device);
    
    void update();
    
    void setPixel(SHPoint position, SHColor color);
    void setPixels(SHPoint position[], SHColor color);
    
    void flush(SHRect dirtyRect, SHColor color);
    void flush(SHColor color);
    
    float getZDepth(SHPoint pos);
    void setZDepth(SHPoint pos, float zDepth);
    SHRect getBounds();
private:
    id<IDevice_osx> _device;
};


#endif
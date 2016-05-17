//
//  IDevice.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/13.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef IDevice_h
#define IDevice_h

#include "BasicGeometry.h"

namespace sh{
    class IDevice{
    public:
        virtual void update() = 0;
        
        virtual void setPixel(SHPoint position, SHColor color) = 0;
        virtual void setPixels(SHPoint position[], SHColor color) = 0;
        
        virtual void flush(SHRect dirtyRect, SHColor color) = 0;
        virtual void flush(SHColor color) = 0;
        
        virtual float getZDepth(SHPoint pos) = 0;
        virtual void setZDepth(SHPoint pos, float zDepth) = 0;
        
        virtual SHRect getBounds() = 0;
    };
}

#endif /* IDevice_h */

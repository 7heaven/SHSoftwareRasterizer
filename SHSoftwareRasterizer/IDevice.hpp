//
//  IDevice.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/13.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef IDevice_hpp
#define IDevice_hpp

#include "BasicGeometry.h"

class IDevice{
public:
    IDevice();
    virtual void update() = 0;
    
    virtual void setPixel(SHPoint position, SHColor color) = 0;
    virtual void setPixels(SHPoint position[], SHColor color) = 0;
    virtual void flush(SHColor color) = 0;
};

#endif /* IDevice_hpp */

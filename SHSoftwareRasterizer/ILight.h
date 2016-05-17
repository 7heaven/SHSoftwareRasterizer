//
//  ILight.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef ILight_h
#define ILight_h

#include "BasicGeometry.h"

class ILight{
public:
    virtual SHColor compute(SHColor inputPixelColor) = 0;
};

#endif /* ILight_h */

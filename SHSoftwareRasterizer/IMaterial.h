//
//  IMaterial.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/18.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef IMaterial_h
#define IMaterial_h

#include "BasicGeometry.h"

namespace sh{
    class IMaterial{
    public:
        virtual SHColor compute(SHPointF uv) = 0;
    };
}

#endif /* IMaterial_h */

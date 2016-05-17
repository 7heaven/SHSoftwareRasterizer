//
//  FakeLight.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/17.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef FakeLight_hpp
#define FakeLight_hpp

#include <stdio.h>
#include "ILight.h"
#include "BasicGeometry.h"

namespace sh{
    class FakeLight : public ILight{
    public:
        FakeLight(float m);
        SHColor compute(SHColor inputPixelColor);
    private:
        float m;
    };
}

#endif /* FakeLight_hpp */

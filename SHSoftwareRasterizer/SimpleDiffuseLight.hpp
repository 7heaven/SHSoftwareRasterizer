//
//  SimpleDiffuseLight.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/17.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef SimpleDiffuseLight_hpp
#define SimpleDiffuseLight_hpp

#include <stdio.h>
#include "ILight.h"

namespace sh{
    class SimpleDiffuseLight: public ILight{
    public:
        SimpleDiffuseLight(float m);
        SHColor compute(SHColor inputPixelColor);
        SHColor compute(const Vertex3D &a,
                        const Vertex3D &b,
                        const Vertex3D &c,
                        SHColor inputPixelColor);
    private:
        float m;
    };
}

#endif /* SimpleDiffuseLight_hpp */

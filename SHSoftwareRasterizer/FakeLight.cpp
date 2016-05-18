//
//  FakeLight.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/17.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "FakeLight.hpp"

namespace sh{
    FakeLight::FakeLight(float m){
        this->m = m;
    }
    
    SHColor FakeLight::compute(SHColor inputPixelColor){
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        
        if(m <= 0.2){
            //模拟金属质感
            float ra = ((0.2F - m) + 1.0F) * 1.2F;
            unsigned char add = 0x55 * (1.0F - (m * 5.0F));
            int preR = (int) (ra * (int) (inputPixelColor.r + add));
            int preG = (int) (ra * (int) (inputPixelColor.g + add));
            int preB = (int) (ra * (int) (inputPixelColor.b + add));
            
            if(preR > 0xFF) preR = 0xFF;
            if(preG > 0xFF) preG = 0xFF;
            if(preB > 0xFF) preB = 0xFF;
            
            red = preR;
            green = preG;
            blue = preB;
        }else{
            float ra = (1.0 - ((m - 0.2) * 1.25));
            red = ra * inputPixelColor.r;
            green = ra * inputPixelColor.g;
            blue = ra * inputPixelColor.b;
        }
        
        return SHColorMake(0xFF000000 | red << 16 | green << 8 | blue);
    }
    
    SHColor FakeLight::compute(const Vertex3D &a,
                               const Vertex3D &b,
                               const Vertex3D &c,
                               SHColor inputPixelColor){
        return SHColorMake(0);
    }
}
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
        
        unsigned char full = 0xFF;
        SHColor revertColor = (SHColor){0xFF, static_cast<unsigned char>(full - inputPixelColor.r), static_cast<unsigned char>(full - inputPixelColor.g), static_cast<unsigned char>(full - inputPixelColor.b)};
        
        if(m <= 0.2){
            float ra = (1.0 - m * 5.0F);
            red = inputPixelColor.r + ra * revertColor.r;
            green = inputPixelColor.g + ra * revertColor.g;
            blue = inputPixelColor.b + ra * revertColor.b;
        }else{
            float ra = (1.0 - ((m - 0.2) * 1.25));
            red = ra * inputPixelColor.r;
            green = ra * inputPixelColor.g;
            blue = ra * inputPixelColor.b;
        }
        
        return SHColorMake(0xFF000000 | red << 16 | green << 8 | blue);
    }
}
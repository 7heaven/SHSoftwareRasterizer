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
        
        unsigned char revertRed = 0xFF - inputPixelColor.r;
        unsigned char revertGreen = 0xFF - inputPixelColor.g;
        unsigned char revertBlue = 0xFF - inputPixelColor.b;
        
        if(m <= 0.2){
            float ra = (1.0 - m * 5.0F);
            red = inputPixelColor.r + ra * revertRed;
            green = inputPixelColor.g + ra * revertGreen;
            blue = inputPixelColor.b + ra * revertBlue;
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
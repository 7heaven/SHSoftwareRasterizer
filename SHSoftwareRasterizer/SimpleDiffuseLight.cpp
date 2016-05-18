//
//  SimpleDiffuseLight.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/17.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "SimpleDiffuseLight.hpp"

namespace sh {
    SimpleDiffuseLight::SimpleDiffuseLight(float m){
        this->m = m;
    }
    
    SHColor SimpleDiffuseLight::compute(SHColor inputPixelColor){
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        
        float ra = (1.0 - m) + 0.4;
        int preR = (int) (ra * inputPixelColor.r);
        int preG = (int) (ra * inputPixelColor.g);
        int preB = (int) (ra * inputPixelColor.b);
        
        if(preR > 0xFF) preR = 0xFF;
        if(preG > 0xFF) preG = 0xFF;
        if(preB > 0xFF) preB = 0xFF;
        
        red = preR;
        green = preG;
        blue = preB;
        
        return SHColorMake(0xFF000000 | red << 16 | green << 8 | blue);
    }
    
    SHColor SimpleDiffuseLight::compute(const sh::Vertex3D &a, const sh::Vertex3D &b, const sh::Vertex3D &c, SHColor inputPixelColor){
        return SHColorMake(0);
    }
}
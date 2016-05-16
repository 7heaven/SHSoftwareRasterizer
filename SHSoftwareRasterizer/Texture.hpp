//
//  Texture.hpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <stdio.h>
#include "BasicGeometry.h"

namespace sh{
    class Texture{
    public:
        Texture(SHColor *pixels, unsigned int width, unsigned int height);
        ~Texture();
        
        SHColor getPixel(unsigned int x, unsigned int y);
        
        unsigned int width;
        unsigned int height;
    private:
        SHColor *pixels;
        
        unsigned int totalSize;
    };
}

#endif /* Texture_hpp */

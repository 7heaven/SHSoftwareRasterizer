//
//  Texture.cpp
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "Texture.hpp"

namespace sh{
    Texture::Texture(SHColor *pixels, unsigned int width, unsigned int height){
        this->pixels = pixels;
        this->width = width;
        this->height = height;
        
        this->totalSize = this->width * this->height;
    }
    
    SHColor Texture::getPixel(unsigned int x, unsigned int y){
        int pos = y * this->width + x;
        
        if(pos < 0 || pos >= this->totalSize) return (SHColor){0};
        
        return this->pixels[pos];
    }
}
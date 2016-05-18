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
    
    SHColor Texture::getPixel(unsigned int u, unsigned int v){
        int pos = v * this->width + u;
        
        if(pos < 0 || pos >= this->totalSize) return (SHColor){0xFF, 0xFF, 0xFF, 0xFF};
        
        return this->pixels[pos];
    }
    
    SHColor Texture::getPixelF(float u, float v){
        float ru = u * this->width;
        float rv = v * this->height;
        
        int x = (int) (ru);
        int y = (int) (rv);
        
        ru = ru - x;
        rv = rv - y;
        
        if(ru == 0 && rv == 0){
            return getPixel(x, y);
        }else{
            if(ru == 0){
                SHColor lowerY = getPixel(x, y);
                SHColor upperY = getPixel(x, y + 1);
                
                return mixRGB(lowerY, upperY, rv);
            }else if(rv == 0){
                SHColor lowerX = getPixel(x, y);
                SHColor upperX = getPixel(x + 1, y);
                
                return mixRGB(lowerX, upperX, ru);
            }else{
                SHColor tlC = getPixel(x, y);
                SHColor trC = getPixel(x + 1, y);
                SHColor blC = getPixel(x, y + 1);
                SHColor brC = getPixel(x + 1, y);
                
                SHColor mixLeft = mixRGB(tlC, blC, rv);
                SHColor mixRight = mixRGB(trC, brC, rv);
                
                return mixRGB(mixLeft, mixRight, ru);
            }
        }
    }
    
    SHColor Texture::mixARGB(SHColor a, SHColor b, float mixedValue){
        unsigned char alpha = a.a;
        unsigned char red = a.r;
        unsigned char green = a.g;
        unsigned char blue = a.b;
        
        char da = b.a - a.a;
        char dr = b.r - a.r;
        char dg = b.g - a.g;
        char db = b.b - a.b;
        
        alpha += (float) da * mixedValue;
        red += (float) dr * mixedValue;
        green += (float) dg * mixedValue;
        blue += (float) db * mixedValue;
        
        return SHColorMake(alpha << 24 | red << 16 | green << 8 | blue);
    }
    
    SHColor Texture::mixRGB(SHColor a, SHColor b, float mixedValue){
        unsigned char red = a.r;
        unsigned char green = a.g;
        unsigned char blue = a.b;
        
        char dr = b.r - a.r;
        char dg = b.g - a.g;
        char db = b.b - a.b;
        
        red += (float) dr * mixedValue;
        green += (float) dg * mixedValue;
        blue += (float) db * mixedValue;
        
        return SHColorMake(0xFF000000 | red << 16 | green << 8 | blue);
    }
}
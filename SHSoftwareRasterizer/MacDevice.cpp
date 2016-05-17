//
//  MacDevice.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/16.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#include "MacDevice.hpp"

MacDevice::MacDevice(id<IDevice_osx> device){
    this->_device = device;
}

void MacDevice::update(){
    [this->_device update];
}

void MacDevice::setPixel(SHPoint position, SHColor color){
    [this->_device setPixel:position color:color];
}

void MacDevice::setPixels(SHPoint *position, SHColor color){
    [this->_device setPixels:position color:color];
}

void MacDevice::flush(SHRect dirtyRect, SHColor color){
    [this->_device flushWithDirtyRect:dirtyRect color:color];
}

void MacDevice::flush(SHColor color){
    [this->_device flushWithColor:color];
}

float MacDevice::getZDepth(SHPoint pos){
    return [this->_device getZDepth:pos];
}

void MacDevice::setZDepth(SHPoint pos, float zDepth){
    return [this->_device setZDepth:zDepth position:pos];
}

SHRect MacDevice::getBounds(){
    return [this->_device getBounds];
}
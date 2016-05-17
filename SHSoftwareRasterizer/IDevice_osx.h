//
//  IDevice.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDevice.h"

@protocol IDevice_osx <NSObject>

- (void) setPixel:(SHPoint) position color:(SHColor) color;
- (void) setPixels:(SHPoint[]) positions color:(SHColor) color;

- (void) flushWithDirtyRect:(SHRect) dirtyRect color:(SHColor) color;
- (void) flushWithColor:(SHColor) color;

- (float) getZDepth:(SHPoint) pos;
- (void) setZDepth:(float) zDepth position:(SHPoint) pos;
- (SHRect) getBounds;

- (void) update;

- (sh::IDevice *) getNativePtr;

@end

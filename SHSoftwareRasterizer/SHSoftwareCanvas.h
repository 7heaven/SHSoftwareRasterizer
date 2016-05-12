//
//  SHCanvas.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "BasicGeometry.h"
#import "IDevice.h"

@interface SHSoftwareCanvas : NSImageView <IDevice>

- (instancetype) initWithBackgroundColor:(SHColor) color;

- (void) drawLineFrom:(SHPoint) p0 to:(SHPoint) p1 color:(SHColor) color;

- (void) setPixel:(SHPoint) position color:(SHColor) color;
- (void) setPixels:(SHPoint[]) positions color:(SHColor) color;

- (void) flushWithColor:(SHColor) color;

- (void) update;

@end

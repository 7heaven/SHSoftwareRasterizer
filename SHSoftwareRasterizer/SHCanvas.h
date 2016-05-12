//
//  SHCanvas.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "BasicGeometry.h"

@interface SHCanvas : NSView

- (instancetype) initWithBackgroundColor:(SHColor) color;

- (void) setPixel:(SHPoint) position color:(SHColor) color;

@end

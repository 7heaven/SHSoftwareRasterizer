//
//  SHCanvas.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface SHCanvas : NSView

- (void) setPixel(SHPoint position, SHColor color);

@end

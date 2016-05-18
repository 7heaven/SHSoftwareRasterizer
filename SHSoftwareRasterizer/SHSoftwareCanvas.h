//
//  SHCanvas.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/12.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "BasicGeometry.h"
#import "IDevice_osx.h"


@interface SHSoftwareCanvas : NSImageView <IDevice_osx>

- (instancetype) initWithBackgroundColor:(SHColor) color;

- (sh::IDevice *) getNativePtr;

@end
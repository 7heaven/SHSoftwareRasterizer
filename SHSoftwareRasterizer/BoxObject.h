//
//  BoxObject.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/15.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BasicGeometry.h"
#import "Object3DEntity.h"


@interface BoxObject : Object3DEntity

- (instancetype) initWithLength:(int) length;

@end

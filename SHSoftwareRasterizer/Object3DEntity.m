//
//  Object3DEntity.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/15.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "Object3DEntity.h"

@implementation Object3DEntity

- (instancetype)init {
    if (self = [super init]) {
        self.vectorArray = [[NSMutableArray alloc] init];
        self.triangleArray = [[NSMutableArray alloc] init];
        self.uvMapArray = [[NSMutableArray alloc] init];
    }
    
    return self;
}

@end

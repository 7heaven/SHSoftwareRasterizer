//
//  BoxObject.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/15.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "BoxObject.h"

@implementation BoxObject

- (instancetype) initWithLength:(int) length{
    if(self = [super init]){
        CGFloat halfLength = length / 2;
        
        self.vectorArray = [@[
                              Vector3DMake(-halfLength, -halfLength, -halfLength),
                              Vector3DMake(halfLength, -halfLength, -halfLength),
                              Vector3DMake(halfLength, halfLength, -halfLength),
                              Vector3DMake(-halfLength, halfLength, -halfLength),
                              Vector3DMake(-halfLength, -halfLength, halfLength),
                              Vector3DMake(halfLength, -halfLength, halfLength),
                              Vector3DMake(halfLength, halfLength, halfLength),
                              Vector3DMake(-halfLength, halfLength, halfLength)
                              ] mutableCopy];
        
        self.uvMapArray = [@[
                             UVMake(0, 0),
                             UVMake(1, 0),
                             UVMake(1, 1),
                             UVMake(0, 1),
                             UVMake(1, 1),
                             UVMake(0, 1),
                             UVMake(0, 0),
                             UVMake(1, 0)
                             
                             ] mutableCopy];
        
        self.triangleArray = [@[
                                TSimple3DMake(0, 2, 1),
                                TSimple3DMake(0, 3, 2),
                                TSimple3DMake(4, 5, 6),
                                TSimple3DMake(4, 6, 7),
                                TSimple3DMake(4, 3, 0),
                                TSimple3DMake(4, 7, 3),
                                TSimple3DMake(1, 6, 5),
                                TSimple3DMake(1, 2, 6),
                                TSimple3DMake(3, 6, 2),
                                TSimple3DMake(3, 7, 6),
                                TSimple3DMake(4, 0, 1),
                                TSimple3DMake(4, 1, 5)
                                ] mutableCopy];
    }
    
    return self;
}

@end

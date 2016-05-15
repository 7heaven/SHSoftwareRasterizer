//
//  Object3DEntity.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/15.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Object3DEntity : NSObject

@property (strong, nonatomic) NSMutableArray *vectorArray;
@property (strong, nonatomic) NSMutableArray *triangleArray;
@property (strong, nonatomic) NSMutableArray *uvMapArray;

@end

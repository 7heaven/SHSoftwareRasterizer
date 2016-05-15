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

inline NSValue *Vector3DMake(float x, float y, float z){
    SHVector3D v = (SHVector3D){x, y, z, 1.0F};
    
    return [NSValue value:&v withObjCType:@encode(SHVector3D)];
}

inline SHVector3D getVector3D(NSValue *value){
    SHVector3D vector;
    [value getValue:&vector];
    
    return vector;
}

inline NSValue *TSimple3DMake(unsigned int a, unsigned int b, unsigned int c){
    SHSimpleTri tri = (SHSimpleTri){a, b, c};
    
    return [NSValue value:&tri withObjCType:@encode(SHSimpleTri)];
}

inline SHSimpleTri getSimpleTri(NSValue *value){
    SHSimpleTri tri;
    [value getValue:&tri];
    
    return tri;
}


@interface BoxObject : Object3DEntity

- (instancetype) initWithLength:(int) length;

@end

//
//  ViewController.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/7.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "ViewController.h"
#import "SHCanvas.h"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    SHCanvas *canvas = [[SHCanvas alloc] init];
    canvas.frame = self.view.bounds;
    
    [self.view addSubview:canvas];
    
    [canvas setPixel:(SHPoint){20, 20} color:(SHColor){0xFF, 0xFF, 0x99, 0xCC}];
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(20 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [canvas setPixel:(SHPoint){50,50} color:(SHColor){0xFF, 0xFF, 0xFF, 0xFF}];
    });
}

- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end

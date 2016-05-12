//
//  ViewController.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/7.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "ViewController.h"
#import "SHSoftwareCanvas.h"

@implementation ViewController{
    SHSoftwareCanvas *canvas;
    NSTimer *timer;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    // Do any additional setup after loading the view.
    canvas = [[SHSoftwareCanvas alloc] init];
    canvas.frame = self.view.bounds;
    
    [self.view addSubview:canvas];
    
    [canvas setPixel:(SHPoint){20, 20} color:(SHColor){0xFF, 0xFF, 0x99, 0xCC}];
    [canvas drawLineFrom:(SHPoint){50, 50} to:(SHPoint){150, 85} color:(SHColor){0xFF, 0x00, 0x99, 0xCC}];
    
    
//    timer = [NSTimer scheduledTimerWithTimeInterval:5 target:self selector:@selector(setPixels) userInfo:nil repeats:YES];
//    [timer fire];
}

- (void) setPixels{
    int x = arc4random() % (int) self.view.frame.size.width;
    int y = arc4random() % (int) self.view.frame.size.height;
    
    NSLog(@"x:%d, y:%d", x, y);
    
    [canvas setPixel:(SHPoint){x, y} color:(SHColor){0xFF, 0xFF, 0xFF, 0xFF}];
    [canvas update];
}

- (void) viewDidAppear{
    [super viewDidAppear];
    
    NSLog(@"viewDidApper");
    
    int x = arc4random() % (int) self.view.frame.size.width;
    int y = arc4random() % (int) self.view.frame.size.height;
    
    NSLog(@"x:%d, y:%d", x, y);
    
    [canvas setPixel:(SHPoint){x, y} color:(SHColor){0xFF, 0xFF, 0xFF, 0xFF}];
}



- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end

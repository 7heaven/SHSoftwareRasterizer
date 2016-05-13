//
//  ViewController.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/7.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "ViewController.h"
#import "SHSoftwareCanvas.h"
#import "Matrix44.hpp"
#import "BasicDraw.hpp"

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
    
    NSTrackingAreaOptions options = (NSTrackingActiveAlways | NSTrackingInVisibleRect |
                                     NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved);
    
    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:self.view.bounds
                                                        options:options
                                                          owner:self
                                                       userInfo:nil];
    
    [self.view addTrackingArea:area];
}

- (void) mouseMoved:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    [canvas flushWithColor:(SHColor){0, 0, 0, 0}];
    
    sh::BasicDraw::drawLine(*[canvas getNativePtr], (SHPoint){150, 150}, (SHPoint){static_cast<int>(location.x), static_cast<int>(self.view.bounds.size.height - location.y)}, (SHColor){0xFF, 0x00, 0x99, 0xCC});
    
    [canvas update];
}



- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

    // Update the view, if already loaded.
}

@end

//
//  ViewController.h
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/7.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface ViewController : NSViewController
@property (weak) IBOutlet NSButton *fileButton;

@property (weak) IBOutlet NSTextField *fpsLabel;
- (IBAction)fileButtonClick:(id)sender;

@end


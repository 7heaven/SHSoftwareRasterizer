//
//  ViewController.m
//  SHSoftwareRasterizer
//
//  Created by 7heaven on 16/5/7.
//  Copyright © 2016年 7heaven. All rights reserved.
//

#import "ViewController.h"
#import "BoxObject.h"
#import <sys/time.h>

#define N 750.0f

@implementation ViewController{
    sh::IDevice *_renderDevice;
    NSTimer *timer;
    
    float angle;
    
    sh::Transform *_transform;
    
    sh::Transform *_worldTransform;
    sh::Transform *_projectionTransform;
    
    Object3D *object;
    
    int _intx;
    int _inty;
    
    int _tx;
    int _ty;
    
    CGPoint _dragPoint;
    CGPoint centerPoint;
    CGFloat _previousRadianX;
    CGFloat _previousRadianY;
    
    CGPoint _currentPointInWindow;
    
    SHRect dirtyRect;
    
    sh::Texture *texture;
}

- (void)viewDidLoad {
    [super viewDidLoad];

    SHSoftwareCanvas *canvas = [[SHSoftwareCanvas alloc] initWithBackgroundColor:SHColorMake(0xFF0099CC)];
    canvas.frame = self.view.bounds;
    _renderDevice = [canvas getNativePtr];
    
    [self.view addSubview:canvas];
    
    NSTrackingAreaOptions options = (NSTrackingActiveAlways | NSTrackingInVisibleRect |
                                     NSTrackingMouseEnteredAndExited | NSTrackingMouseMoved);
    
    NSTrackingArea *area = [[NSTrackingArea alloc] initWithRect:self.view.bounds
                                                        options:options
                                                          owner:self
                                                       userInfo:nil];
    
    [self.view addTrackingArea:area];
    
    _transform = new sh::Transform();
    
    float scaleFactor = 55.0F;
    _worldTransform = sh::Transform::scale(SHVector3DMake(scaleFactor, scaleFactor, scaleFactor, 1));
    
    _projectionTransform = sh::Transform::perspective(3.1415926f * 0.12f, self.view.frame.size.width / self.view.frame.size.height, 1.0f, 500.0f);
//    _projectionTransform = sh::Transform::perspective(N);
    
    centerPoint = CGPointMake(self.view.frame.size.width / 2, self.view.frame.size.height / 2);
    dirtyRect = SHRectMake(0, 0, 0, 0);
    
    [self.fpsLabel removeFromSuperview];
    [self.view addSubview:self.fpsLabel];
    
    [self.fileButton removeFromSuperview];
    [self.view addSubview:self.fileButton];
    
    texture = [self readTextureFromImage:[NSImage imageNamed:@"uv_map_axe"]];
}

- (sh::Texture *) readTextureFromImage:(NSImage *) image{
    NSBitmapImageRep *imageRep = [NSBitmapImageRep imageRepWithData:[image TIFFRepresentation]];
    imageRep = [imageRep bitmapImageRepByConvertingToColorSpace:[NSColorSpace deviceRGBColorSpace] renderingIntent:NSColorRenderingIntentDefault];
    
    int width = (int) [imageRep pixelsWide];
    int height = (int) [imageRep pixelsHigh];
    
    SHColor *pixels = (SHColor *) malloc(width * height * sizeof(SHColor));
    
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            NSColor *c = [imageRep colorAtX:x y:y];
            
            pixels[y * width + x] = (SHColor){0xFF, static_cast<unsigned char>(c.redComponent * 255), static_cast<unsigned char>(c.greenComponent * 255), static_cast<unsigned char>(c.blueComponent * 255)};
        }
    }
    
    return new sh::Texture(pixels, width, height);
    
}


- (void) rotateX:(float) x y:(float) y{
    
    sh::Transform *rotate = sh::Transform::rotate(0, y, x);
    
    *_transform *= *rotate;
    *_transform *= *_worldTransform;
    
}

- (void) mouseDown:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    if (isnan(_dragPoint.x) || isnan(_dragPoint.y)) _dragPoint = CGPointMake(0, 0);
//    if (!_box) _box = [[BoxObject alloc] initWithLength:150];
    
    _intx = location.x;
    _inty = location.y;
    _tx = 0;
    _ty = 0;
    
    [self performFrameUpdate];
}

- (void) mouseDragged:(NSEvent *)theEvent{
    timeval time;
    gettimeofday(&time, NULL);
    long previousTime = (time.tv_sec * 1000) + (time.tv_usec / 1000);
    
    CGPoint location = theEvent.locationInWindow;
    
    _tx = location.x - _intx;
    _ty = location.y - _inty;
    
    [self performFrameUpdate];
    
    timeval aftertime;
    gettimeofday(&aftertime, NULL);
    long currentTime = (aftertime.tv_sec * 1000) + (aftertime.tv_usec / 1000);
    long gap = currentTime - previousTime;
    int fps = 1000 / (gap + 1);
    
    [self.fpsLabel setStringValue:[NSString stringWithFormat:@"%ldms/F", gap]];
    
}

- (void) mouseUp:(NSEvent *)theEvent{
    CGPoint location = theEvent.locationInWindow;
    
    _previousRadianX = (_tx - centerPoint.x) / 200 + _previousRadianX;
    _previousRadianY = (_ty - centerPoint.y) / 200 + _previousRadianY;
}

- (void) performFrameUpdate{
    
    if(object == NULL) return;
    
    _dragPoint = CGPointMake(_dragPoint.x + (_tx - _dragPoint.x) * 0.01, _dragPoint.y + (_ty - _dragPoint.y) * 0.01);
    
    //    [canvas flushWithDirtyRect:dirtyRect color:SHColorMake(0x0)];
    //    dirtyRect = SHRectMake(0, 0, 0, 0);
    //    [canvas flushWithColor:SHColorMake(0xFF0099CC)];
    _renderDevice->flush(SHColorMake(0xFF0099CC));
    
    //矩阵还原
    _transform->m->toIdentity();
    
    (*_transform->m)[2][3] = 400;
    
    //矩阵旋转
    [self rotateX:(_tx - centerPoint.x) / 200 + _previousRadianX y:(_ty - centerPoint.y) / 200 + _previousRadianY];
    
    for(int i = 0; i < object->_mesh_count; i++){
        NSLog(@"mesh_count:%llu", object->_mesh_count);
        Mesh3D mesh = object->_meshes[i];
        
        NSLog(@"tri_count:%llu", mesh._trianglesSize);
        for(int j = 0; j < mesh._trianglesSize; j++){
            //获取三角形
            SHSimpleTri tri = mesh._triangles[j];
            
            //获取三角形对应的顶点
            SHVector3D a = mesh._vertexes[tri.a];
            SHVector3D b = mesh._vertexes[tri.b];
            SHVector3D c = mesh._vertexes[tri.c];
            
            //获取三角形顶点的uv坐标
            SHUVCoorF auv;
            SHUVCoorF buv;
            SHUVCoorF cuv;
            if(mesh._uvmaps != nullptr){
                auv = mesh._uvmaps[tri.a];
                buv = mesh._uvmaps[tri.b];
                cuv = mesh._uvmaps[tri.c];
            }else{
                auv = (SHUVCoorF){0, 0};
                buv = (SHUVCoorF){0, 0};
                cuv = (SHUVCoorF){0, 0};
            }
            
            
            
            //世界坐标变换
            SHVector3D ta = *_transform * a;
            SHVector3D tb = *_transform * b;
            SHVector3D tc = *_transform * c;
            
            
            //二维透视投影
            SHVector3D a2D = *_projectionTransform * ta;
            SHVector3D b2D = *_projectionTransform * tb;
            SHVector3D c2D = *_projectionTransform * tc;
            
            //获取二维屏幕坐标
            SHPoint pa = SHPointMake(a2D.x / a2D.w + centerPoint.x, a2D.y / a2D.w + centerPoint.y);
            SHPoint pb = SHPointMake(b2D.x / b2D.w + centerPoint.x, b2D.y / b2D.w + centerPoint.y);
            SHPoint pc = SHPointMake(c2D.x / c2D.w + centerPoint.x, c2D.y / c2D.w + centerPoint.y);
            
            //检查dirtyRect
            //        [self checkDirty:pa];
            //        [self checkDirty:pb];
            //        [self checkDirty:pc];
            
            //二维向量叉乘，用此方法判断三角形是顺时针还是逆时针，如果逆时针则跳过
            float s = [self crossProductWith:(SHPoint){pb.x - pa.x, pb.y - pa.y}
                                          p1:(SHPoint){pc.x - pa.x, pc.y - pa.y}];
            
            if(s > 0) continue;
            
            //三维向量取模，用来计算光线值
            float m = [self crossProWithV0:(SHVector3D){tb.x - ta.x, tb.y - ta.y, tb.z - ta.z, 1} v1:(SHVector3D){tc.x - ta.x, tc.y - ta.y, tc.z - ta.z, 1} center:centerPoint];
            
            //        if(m > 1) m = 1.0F;
            //        if(m < 0) m = 0.0F;
            
            //根据m来计算的光线，这个类取名容易引起困惑，实际上应该取名Material再引入场景内的灯光来计算，待修改
            sh::ILight *light = new sh::FakeLight(m);
            
            sh::Vertex3D *va = new sh::Vertex3D();
            va->pos = ta;
            va->screenPos = pa;
            va->u = auv.u;
            va->v = auv.v;
            
            sh::Vertex3D *vb = new sh::Vertex3D();
            vb->pos = tb;
            vb->screenPos = pb;
            vb->u = buv.u;
            vb->v = buv.v;
            
            sh::Vertex3D *vc = new sh::Vertex3D();
            vc->pos = tc;
            vc->screenPos = pc;
            vc->u = cuv.u;
            vc->v = cuv.v;
            
            
            //扫描线绘制三角形
                        sh::BasicDraw::drawPerspTriangle(*_renderDevice, va, vb, vc, *texture, *light);
            
//            sh::BasicDraw::drawLine(*_renderDevice, pa, pb, SHColorMake(0xFFFF0000));
//            sh::BasicDraw::drawLine(*_renderDevice, pb, pc, SHColorMake(0xFFFF0000));
//            sh::BasicDraw::drawLine(*_renderDevice, pc, pa, SHColorMake(0xFFFF0000));
            
        }
    }
    
    _renderDevice->update();
}

- (void) checkDirty:(SHPoint) p{
    if(p.x < dirtyRect.x) dirtyRect.x = p.x - 1;
    if(p.y < dirtyRect.y) dirtyRect.y = p.y - 1;
    if(p.x > dirtyRect.x + dirtyRect.w) dirtyRect.w = p.x - dirtyRect.x + 2;
    if(p.y > dirtyRect.y + dirtyRect.h) dirtyRect.h = p.y - dirtyRect.y + 2;
}

- (float) crossProductWith:(SHPoint) p0 p1:(SHPoint) p1{
    float s = p0.x * p1.y - p1.x * p0.y;
    
    return s;
}

- (float)crossProWithV0:(SHVector3D)v0 v1:(SHVector3D)v1 center:(CGPoint)cPoint {
    CGFloat t_x = v0.y * v1.z - v0.z * v1.y;
    CGFloat t_y = v0.z * v1.x - v0.x * v1.z;
    CGFloat t_z = v0.x * v1.y - v0.y * v1.x;
    
    CGFloat m = sqrt(t_x * t_x + t_y * t_y + t_z * t_z);
    //向量单位化
    t_x /= m;
    t_y /= m;
    //不开方,以减少运算量
    return t_x * t_x + t_y * t_y;
}


- (void)setRepresentedObject:(id)representedObject {
    [super setRepresentedObject:representedObject];

}

- (IBAction)fileButtonClick:(id)sender {
    
    NSOpenPanel* panel = [NSOpenPanel openPanel];
    [panel setCanChooseFiles:YES];
    [panel setAllowedFileTypes:@[@"3ds"]];
    
    [panel beginWithCompletionHandler:^(NSInteger result){
        if (result == NSFileHandlingPanelOKButton) {
            NSURL *_selectedDoc = [[panel URLs] objectAtIndex:0];
            
            NSString *absFilePath = _selectedDoc.absoluteString;
            
            if([absFilePath hasPrefix:@"file://"]){
                absFilePath = [absFilePath substringFromIndex:7];
            }
            
            sh::D3DSDecoder *decoder = new sh::D3DSDecoder();
            object = decoder->decode([absFilePath UTF8String]);
            delete decoder;
 
//            dirtyRect = SHRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height);

            _transform->m->toIdentity();
            [self performFrameUpdate];
            _renderDevice->update();
            
        }
        
    }];
    
    panel = nil;
}

@end

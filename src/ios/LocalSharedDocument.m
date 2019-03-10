//
//  LocalSharedDocument.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "LocalSharedDocument.h"
#import "CollaborateUtils.h"


@implementation LocalSharedDocument

+(LocalSharedDocument*)localSharedDocument:(NSURL*)url{
    LocalSharedDocument *doc = [[LocalSharedDocument alloc]initWithURL:url];
    
    return doc;
}

-(id)initWithURL:(NSURL*)url{
    self = [super init];
    
    
    _mainView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, 100, 100 )];
    _mainView.backgroundColor = UIColor.blueColor;
    _mainView.autoresizesSubviews = YES;
    
    
    _webview = [UIWebView new];
    [_webview loadRequest:[NSURLRequest requestWithURL:url]];
    _webview.scalesPageToFit = YES;
    [_mainView addSubview:_webview];
    _webview.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _webview.frame = _mainView.bounds;

    dispatch_async( dispatch_get_main_queue(), ^{
        [CollaborateUtils.Instance.api startSahringView:CollaborateUtils.Instance.currentCall.callID sharedVide:self.webview];
    });

    return self;
}

-(UIView*)view{
    return _mainView;
}

- (void)onWhiteboardState:(bool)bActive {
    if ( _annotationView != nil)
        [_annotationView onWhiteboardState:bActive];
}

- (void)setNewFrame {
    
}

-(BOOL)canAnnotate{
    return (_annotationView != nil);
}

-(BOOL)canScroll{
    return YES;
}

-(void)setEnableAnnotation:(BOOL)enableAnnotation{
    if ( _annotationView != nil ){
        _annotationView.enableAnnotation = enableAnnotation;
        _annotationView.userInteractionEnabled = _annotationView.enableAnnotation ;
        _webview.scrollView.scrollEnabled = !_annotationView.enableAnnotation;
    }
}

-(BOOL)enableAnnotation{
    return _annotationView.enableAnnotation;
}

-(void)setAnnotationStream:(ISptCallStream *)annotationStream{
    _annotationStream = annotationStream;
    if ( _annotationStream != nil ){
        //_touchView.annotation = annotationStream.getAnnotationData;
        _annotationView = annotationStream.view;
        [_mainView addSubview: _annotationView.view];
        _annotationView.userInteractionEnabled = NO;
        _annotationView.frame = _mainView.bounds;
        // _touchView.backgroundColor = [UIColor colorWithRed:1 green:0 blue:0 alpha:0.1];
    }else{
        if ( _annotationView != nil ){
            [_annotationView removeFromSuperview];
            _annotationView = nil;
        }
    }
}

@end

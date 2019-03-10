//
//  LocalSharedDocument.h
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CollaborateSpace/CollaborateSpace.h>


@interface LocalSharedDocument : NSObject <SptMediaView>
@property (nonatomic, retain) UIWebView *webview;
@property (nonatomic, retain) UIView *mainView;
@property (nonatomic, assign) BOOL annotating;
@property (nonatomic, retain) SptAnnotation *annotation;
@property (nonatomic, retain) ISptCallStream *annotationStream;
@property (nonatomic, retain) UIView <SptMediaView>*annotationView;

+(LocalSharedDocument*)localSharedDocument:(NSURL*)url;

@end

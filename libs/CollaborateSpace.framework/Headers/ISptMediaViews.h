//
//  ISptMediaViews.h
//  CollaborateSpace
//
//  Created by Pablo on 11/03/2019.
//  Copyright © 2019 ClearOne Inc. All rights reserved.
//

#import "ISptCallExt.h"
#import "ISpontaniaIMApiDelegate.h"


typedef NS_ENUM(NSUInteger, MediaViewType) {
    MediaViewTypeVideo,
    MediaViewTypeSharing,
    MediaViewTypeLocalSharing,
    MediaViewTypeWhiteboard,
    MediaViewTypeOfflineWhiteboard
};

@protocol MediaViewDelegate <NSObject>
@optional
-(void)onViewActive:(BOOL)active;
-(void)onAnnotationActive:(SptAnnotation*)annotation;
@end

@interface MediaView : UIView <ISpontaniaIMApiDelegate>
@property (nonatomic,assign) BOOL active;
@property (nonatomic,assign) BOOL connected;
@property (nonatomic, assign) CGRect rectCallControls;
@property (nonatomic, assign) BOOL callControlsVisible;
@property (readonly) MediaViewType type;

-(id<SptMediaView>) firstMediaView;
-(BOOL)containsStreaming:(ISptCallStream*)streaming;

@property (nonatomic, weak) id<MediaViewDelegate> delegate;


@property (nonatomic, retain) SptLocalAnnotation *localAnnotation;
@property (nonatomic, retain) SptAnnotation *annotation;
@property (nonatomic, retain) ISptCallStream *annotationStream;
-(NSArray *)getStreamingsNoLocalVideo:(BOOL)removeLocalVideo;

@property (nonatomic, retain) NSURL *url;
-(void)setEnableAnnotation:(BOOL)enableAnnotation;
@end

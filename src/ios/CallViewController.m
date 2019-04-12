//
//  CallViewController.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "CallViewController.h"
#import "DocSelectionController.h"
#import <CollaborateSpace/ISpontaniaIMApi.h>

@class MediaViewController;

@protocol MediaViewControllerDelegate <NSObject>
@required
-(void)onMediaViewControllerActive:(MediaViewController*)vc;
@end


@interface MediaViewController : UIViewController <MediaViewDelegate>
-(MediaView*)mediaView;
-(id)initWithMediaView:(MediaView*)mediaView;

@property (nonatomic, retain) UIPanGestureRecognizer *panGestureRecognizer;
@property (nonatomic, weak) id<MediaViewControllerDelegate> delegate;
@end

@implementation MediaViewController

-(id)initWithMediaView:(MediaView*)mediaView{
    self = [super init];
    self.view = mediaView;
    return self;
}

-(MediaView*)mediaView{
    return (MediaView*)self.view;
}

-(void)onViewActive:(BOOL)active{
    if ( _delegate != nil )
        [_delegate onMediaViewControllerActive:self];
}

/*
-(void)onAnnotationActive:(BOOL)enable{
    [self setPageLocked:(annotation!=nil)];
}*/

-(void)setPageLocked:(BOOL)pageLocked{
    if ( pageLocked ){
        MediaView *v = self.mediaView;
        
        if ( [v respondsToSelector:@selector(setEnableAnnotation:)])
            [v setEnableAnnotation:YES];
        if ( self.panGestureRecognizer == nil ){
            self.panGestureRecognizer = [UIPanGestureRecognizer new];
            self.panGestureRecognizer.cancelsTouchesInView = NO;
            [self.view addGestureRecognizer:self.panGestureRecognizer];
        }
    }else{
        if ( self.panGestureRecognizer != nil ){
            [self.view removeGestureRecognizer:self.panGestureRecognizer];
            self.panGestureRecognizer = nil;
        }
    }
}

@end


@interface CallPageViewController : UIPageViewController<UIPageViewControllerDataSource, MediaViewControllerDelegate>

@property (strong, nonatomic) MediaViewController *videoVC;
@property (strong, nonatomic) MediaViewController *localSharingVC;
@property (strong, nonatomic) MediaViewController *remoteSharingVC;
@property (strong, nonatomic) MediaViewController *whiteboardVC;
@property (strong, nonatomic) NSArray <UIViewController*> *arrayVC;
@property (strong, nonatomic) NSArray <UIViewController*> *arrayCurrentVisibleVC;

@end

@implementation CallPageViewController

-(void)viewDidLoad{
    [super viewDidLoad];
    self.dataSource = self;
    
    MediaViewController *(^createMediaVC)(MediaViewType ) = ^(MediaViewType type){
        MediaView *v = [CollaborateUtils.Instance.api createMediaView:CollaborateUtils.Instance.currentCall.callID
                                                  type:type];
        MediaViewController *vc = [[MediaViewController alloc]initWithMediaView:v];
        v.delegate = vc;
        vc.delegate = self;
        return vc;
    };
    _videoVC =createMediaVC( MediaViewTypeVideo );
    _localSharingVC =createMediaVC( MediaViewTypeLocalSharing );
    _remoteSharingVC =createMediaVC( MediaViewTypeSharing );
    _whiteboardVC =createMediaVC( MediaViewTypeWhiteboard );

    _arrayVC = @[_videoVC, _localSharingVC, _remoteSharingVC, _whiteboardVC];
    [self reloadViewControllers];
}


- (nullable UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerBeforeViewController:(UIViewController *)viewController{
    NSUInteger pos = [_arrayCurrentVisibleVC indexOfObject:viewController];
    
    if ( pos == NSNotFound )
        return _arrayCurrentVisibleVC.firstObject;
    
    if ( pos == 0 )
        return nil;
    
    return [_arrayCurrentVisibleVC objectAtIndex:pos-1];
}

- (nullable UIViewController *)pageViewController:(UIPageViewController *)pageViewController viewControllerAfterViewController:(UIViewController *)viewController{
    NSUInteger pos = [_arrayCurrentVisibleVC indexOfObject:viewController];
    
    if ( pos == NSNotFound )
        return _arrayCurrentVisibleVC.firstObject;
    
    if ( (pos+1) >= _arrayCurrentVisibleVC.count )
        return nil;
    
    return [_arrayCurrentVisibleVC objectAtIndex:pos+1];
}

-(void)onMediaViewControllerActive:(MediaViewController *)vc{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self reloadViewControllers];
    });
}

-(void)reloadViewControllers{
    NSArray *arrayActive = [_arrayVC filteredArrayUsingPredicate:[NSPredicate predicateWithBlock:^BOOL( UIViewController *vc, NSDictionary<NSString *,id> * _Nullable bindings) {
        return ((MediaView*)vc.view).active;
    }]];
    
    if ( arrayActive.count == 0 ){
        arrayActive = @[_videoVC];
    }
    
    
    if ( _arrayCurrentVisibleVC == nil || ![arrayActive isEqualToArray:_arrayCurrentVisibleVC] ){
        _arrayCurrentVisibleVC = arrayActive;
        
//        if ( _arrayCurrentVisibleVC.lastObject != self.viewControllers.firstObject )
        dispatch_async(dispatch_get_main_queue(), ^{
            self.dataSource = nil;
            self.dataSource = self;
            [self setViewControllers:@[self.arrayCurrentVisibleVC.lastObject] direction:UIPageViewControllerNavigationDirectionForward animated:YES completion:nil];
        });
    }
}

-(void)setPageLocked:(BOOL)pageLocked{
    [_localSharingVC setPageLocked:pageLocked];
    [_remoteSharingVC setPageLocked:pageLocked];
    [_whiteboardVC setPageLocked:pageLocked];
}

@end

@interface CallViewController ()
@property (nonatomic, retain) DocSelectorController *docSelection;
@property (nonatomic, retain) SptCallRequest *sharingRequest;
@property (strong, nonatomic) IBOutlet UIButton *buttonOptions;
@property (weak, nonatomic) CallPageViewController *pageViewController;
@property (nonatomic ,assign) BOOL enableAnnotation;
@property (retain, retain) SptAnnotation *annotation;
@property (retain, retain) ISptCallStream *streamAnnotation;
@property (strong, nonatomic) IBOutlet UIView *callButtonsView;
@property (strong, nonatomic) IBOutlet UIButton *buttonMic;
@property (strong, nonatomic) IBOutlet UIButton *buttonHangup;
@property (strong, nonatomic) IBOutlet UIButton *buttonVideo;

@end

@implementation CallViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    CollaborateUtils.Instance.callCallback = self;
    
    for ( UIViewController *vc in self.childViewControllers ){
        if ( [vc isKindOfClass:[CallPageViewController class]] ){
            _pageViewController = (CallPageViewController*)vc;
        }
    }
}

-(void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    [self updateLocalParticipantsServices];
}
-(void)viewDidLayoutSubviews{
    [super viewDidLayoutSubviews];
    //_pageViewController.view.frame = _containterView.bounds;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

-(void)onCallRequestUpdated:(SptCallRequest *)callRequest{
    if ( callRequest.state == eCallRequestStatePending ){
        switch ( callRequest.type ){
            case eCallRequestShareApplication:
            {
                _sharingRequest = callRequest;
                __block CallViewController *_self = self;
                dispatch_async(dispatch_get_main_queue(), ^{
                    _self.docSelection = [DocSelectorController openDocumentSelectionFromViewController:_self sender:_self.view andDelegate:_self];
                });
            }break;
            default:
                break;
        }
    }else{
        if ( callRequest.state == eCallRequestStateCancel ){
            switch ( callRequest.type ){
                case eCallRequestShareApplication:
                {
                    if ( _docSelection != nil )
                        [_docSelection cancel];
                }break;
                default:
                    break;
            }
        }
    }
}

-(void)OnDocumentSelected:(NSURL*)url{
    self.pageViewController.localSharingVC.mediaView.url = url;
}

-(void)OnDocumentSelectionCanceled{
    [CollaborateUtils.Instance.api answerCallRequest:_sharingRequest accept:NO];
}

-(void)onStreamAnnotationEnabled:(ISptCallStream *)stream enabled:(BOOL)enabled{
    SptAnnotation *annotation = [stream getAnnotationData];
    if ( annotation != nil ){
        [annotation setAnnotationTool:kAnnToolBrush];
        [annotation setAnnotationColor:YES setColor:UIColor.redColor];
        stream.view.enableAnnotation = YES;
    }
    
    [_pageViewController setPageLocked:(annotation!=nil)];
}

- (void)onStreamingStarted:(ISptCallStream *)stream {
   
    if ( _annotation == nil ){
        _annotation = [stream getAnnotationData];
        if ( _annotation != nil ){
            _streamAnnotation = stream;
            stream.view.enableAnnotation = YES;
            [_annotation setAnnotationTool:kAnnToolBrush];
            [_annotation setAnnotationColor:YES setColor:UIColor.redColor];
        }
    }
}

- (void)onStreamingStoped:(ISptCallStream *)stream {
    if ( _streamAnnotation != nil && _streamAnnotation.streamID == stream.streamID ){
        _streamAnnotation = nil;
        _annotation = nil;
    }
}
-(void)updateLocalParticipantsServices{
    ISptCallParticipantData *participant = [self.call getParticipantByID:kSPT_LOCAL_CALLPARTICIPANT_ID];
    if ( participant != nil ){
        _buttonMic.selected = !(participant.services.audioService & kSptServiceActive);
        _buttonVideo.selected = !(participant.services.videoService & kSptServiceActive);
    }
}

- (void)onCallParticipantUpdated:(ISptCallParticipantData *)participant{
    if ( participant.callParticipantID == kSPT_LOCAL_CALLPARTICIPANT_ID ){
        [self updateLocalParticipantsServices];
    }
}
- (IBAction)onMicPressed:(id)sender {
    [CollaborateUtils.Instance.api setCallServiceState:self.call.callID
                                           participant:kSPT_LOCAL_CALLPARTICIPANT_ID
                                             serviceID:eCallServiceAudio
                                                enable:_buttonMic.selected];
}


- (IBAction)onVideoPressed:(id)sender {
    [CollaborateUtils.Instance.api setCallServiceState:self.call.callID
                                           participant:kSPT_LOCAL_CALLPARTICIPANT_ID
                                             serviceID:eCallServiceVideo
                                                enable:_buttonVideo.selected];

}
- (IBAction)onHangupPressed:(id)sender {
    [CollaborateUtils.Instance.api hangUpCall:self.call.callID];
}

- (IBAction)onOptionsPressed:(id)sender {
    ISptCallParticipantData *participant = [self.call getParticipantByID:kSPT_LOCAL_CALLPARTICIPANT_ID];
    BOOL sharingActive = participant.services.sharingService & kSptServiceActive;
//    BOOL annotationActive = participant.services.whiteboardService & kSptServiceActive;

    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nil message:nil preferredStyle:UIAlertControllerStyleActionSheet];
//    [alertController addAction:[UIAlertAction actionWithTitle:(!annotationActive)?@"Start Annotation":@"Stop Annotation" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
//        [CollaborateUtils.Instance.api setCallServiceState:self.call.callID
//                                               participant:kSPT_LOCAL_CALLPARTICIPANT_ID
//                                                 serviceID:eCallServiceWhiteboard
//                                                    enable:!annotationActive];
//    }]];
    
    [alertController addAction:[UIAlertAction actionWithTitle:(!sharingActive)?@"Start Sharing":@"Stop Sharing" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        [CollaborateUtils.Instance.api setCallServiceState:self.call.callID
                                               participant:kSPT_LOCAL_CALLPARTICIPANT_ID
                                                 serviceID:eCallServiceSharing
                                                    enable:!sharingActive];
    }]];
    
    [alertController addAction:[UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:nil]];
    alertController.modalPresentationStyle = UIModalPresentationPopover;
    
    [self presentViewController:alertController animated:YES completion:nil];
}


@end

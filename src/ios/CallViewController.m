//
//  CallViewController.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "CallViewController.h"
#import "LocalSharedDocument.h"
#import "DocSelectionController.h"


@interface CallViewController ()
@property (strong, nonatomic) IBOutlet UIButton *buttonHangup;
@property(nonatomic, retain) NSMutableDictionary <NSNumber *,ISptCallStream *> *dictVideoStreamings;

@property (nonatomic, retain) DocSelectorController *docSelection;

@property (nonatomic, retain) SptCallRequest *sharingRequest;
@property (strong, nonatomic) IBOutlet UIButton *buttonAnnotate;

@property (strong, nonatomic) LocalSharedDocument *localSharedDocument;
@property (nonatomic, retain) id<SptMediaView> sharingMediaView;

@end

@implementation CallViewController

- (id)initWithCoder:(NSCoder *)aDecoder {

    if(self = [super initWithCoder:aDecoder]) {
        _seqID = kSPT_INVALID_MEETING_SEQUENCE_ID;
        _meetingID = kSPT_INVALID_MEETING_ID;
        _joinMeetingError = eNoError;
    }


    return self;
}


- (void)viewDidLoad {
    [super viewDidLoad];


    CollaborateUtils.Instance.callManagerCallback = self;

    UIAlertView *alert1 = [[UIAlertView alloc]initWithTitle:@"Testing"
                                      message:@"CallViewController - viewDidLoad1"
                                    delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];

    //

    //[alert1 show];

    UIButton *button = [UIButton buttonWithType:UIButtonTypeSystem];
    [button setTitle:@"Hangup" forState:UIControlStateNormal];
    [button sizeToFit];
  //  button.center = CGPointMake(320/2, 60);

    // Add an action in current code file (i.e. target)
    [button addTarget:self action:@selector(onCancel:)
     forControlEvents:UIControlEventTouchUpInside];

    [self.view addSubview:button];

    if ((_joinMeetingError == eNoError)&&(_seqID != kSPT_INVALID_MEETING_SEQUENCE_ID)&&(_meetingID != kSPT_INVALID_MEETING_ID))
    {
        //Start join meeting process
        [CollaborateUtils.Instance.api joinSchMeeting:_seqID
                                              meeting:_meetingID
                                              videoON:YES];
    }
    else if (_joinMeetingError != eNoError)
    {
        UIAlertView *alert = nil;
        switch (_joinMeetingError) {
            case eNoError:
                break;
            case eWaitingHost:
                alert = [[UIAlertView alloc]initWithTitle:@"Host not connected"
                                                  message:@"Host has to be connected to the meeting"
                                                 delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
                break;
            case eMeetingFinished:
                alert = [[UIAlertView alloc]initWithTitle:@"Meeting Finished"
                                                  message:@"Meeting has finished"
                                                 delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
                break;
            case eMeetingNotStarted:
                alert = [[UIAlertView alloc]initWithTitle:@"Meeting not started"
                                                  message:@"Meeting has not started yet"
                                                 delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
                break;
            case eNoMeetingFound:
                alert = [[UIAlertView alloc]initWithTitle:@"Error"
                                                  message:@"Meetimg not found"
                                                 delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
                break;
            case eMeetingCancelled:
                alert = [[UIAlertView alloc]initWithTitle:@"Meeting cancelled"
                                                  message:@"Meeting has been cancelled"
                                                 delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
                break;
        }

        if (alert != nil)
            [alert show];
    }

    //CollaborateUtils.Instance.callCallback = self;

    //CollaborateUtils.Instance.callCallback = self;
    //_dictVideoStreamings = [NSMutableDictionary dictionary];
    //[self updateCall];

  //  UIAlertView *alert2 = [[UIAlertView alloc]initWithTitle:@"Testing"
  //                                    message:@"CallViewController - viewDidLoad2"
  //                                   delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
//
//    [alert2 show];


}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}


-(void)onNewCall:(ISptCall*)call incoming:(BOOL)incoming{
    /**
     When a new call appears we present "Starting Call" view controller
     */
  //  if ( _startingCallViewController != nil ){
  //      [_startingCallViewController dismissViewControllerAnimated:NO completion:nil];
  //  }
  //  _startingCallViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"startingCallViewController"];
  //  _startingCallViewController.call = call;
  //  [self presentViewController:_startingCallViewController animated:YES completion:nil];
}

-(void)onCallEstablished:(ISptCall*)call {
    /**
     If the call is Established, we hide "Starting Call" view controller and show "In Call" view controller
     */

    //if ( _startingCallViewController != nil ){
    //    [_startingCallViewController dismissViewControllerAnimated:YES completion:nil];
    //}

  //  _callViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"callViewController"];
  //  _callViewController.call = call;

    CollaborateUtils.Instance.callCallback = self;
    _dictVideoStreamings = [NSMutableDictionary dictionary];
    self.call = call;
    [self updateCall];

  //  [self presentViewController:_callViewController animated:YES completion:nil];

}

-(void)onCallFinished:(ISptCall*)call{
    /**
     When the call is finished, we just hide all call viewcontrollers
     */

    //if ( _callViewController != nil ){
     //   [_callViewController dismissViewControllerAnimated:YES completion:nil];
   // }

    [self dismissViewControllerAnimated:YES completion:nil];
   // if ( _startingCallViewController != nil ){
   //     [_startingCallViewController dismissViewControllerAnimated:YES completion:nil];
   // }
}




-(void)setCall:(ISptCall*)call{
    _call = call;
    [self updateCall];
}

-(void)updateCall{
    for ( ISptCallStream *stream in _call.callActiveStreams ){
        [self addStream:stream];
    }
}

- (IBAction)onCancel:(id)sender {
    [CollaborateUtils.Instance.api hangUpCall:_call.callID];
}

-(void)onStreamingStarted:(ISptCallStream*)stream{
    [self addStream:stream];
}

-(void)onStreamingStoped:(ISptCallStream*)stream{
    if ( stream.streamType == eStreamTypeSharing && stream.participantID == kSPT_LOCAL_CALLPARTICIPANT_ID ){
        [self updateStreamingRects];
    }
    [self deleteStream:stream];
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

-(void)viewDidLayoutSubviews{
    [super viewDidLayoutSubviews];
    [self updateStreamingRects];
}

-(void)addStream:(ISptCallStream*)stream{
    if ( stream.streamType == eStreamTypeVideo ){
        if ( [_dictVideoStreamings objectForKey:@(stream.streamID)] == nil ){
            UIView *view = stream.view;
            [_dictVideoStreamings setObject:stream forKey:@(stream.streamID)];
            [self.view addSubview:view];
            [self.view sendSubviewToBack:view];
        }
        [self updateStreamingRects];
    }

    if ( stream.streamType == eStreamTypeWhiteboard || ( stream.streamType == eStreamTypeSharing && stream.participantID != kSPT_LOCAL_CALLPARTICIPANT_ID ) ){
        self.sharingMediaView = stream.view;
    }
}

-(void)deleteStream:(ISptCallStream*)stream{
    if ( [_dictVideoStreamings objectForKey:@(stream.streamID)] != nil ){
        [_dictVideoStreamings removeObjectForKey:@(stream.streamID)];
        [stream.view removeFromSuperview];
        [self updateStreamingRects];
    }

    if ( stream.streamType == eStreamTypeSharing || stream.streamType == eStreamTypeWhiteboard ){
        self.sharingMediaView = nil;
    }
}

-(void)updateStreamingRects{
    CGRect bounds = self.view.bounds;
    BOOL horizontal = (bounds.size.width > bounds.size.height);

    if ( _sharingMediaView.view == nil ){
        CGRect rects4[] = { { 0, 0, 0.5, 0.5 }, { 0.5, 0.5, 0.5, 0.5 }
                           , { 0.5, 0.0, 0.5, 0.5 }, { 0, 0.5, 0.5, 0.5 }};
        CGRect rects2[] = { { 0, 0, 1, 0.5 }, { 0.0, 0.5, 1, 0.5 } };
        CGRect rects1[] = { {  0, 0, 1, 1 } };

        CGRect rectLocal =  {  0.70, 0.70, 0.28, 0.28 };

        NSArray <ISptCallStream *>*arrayStreamings = _call.callActiveStreams;

        NSInteger iRemoteStreamings = arrayStreamings.count;

        for ( ISptCallStream *stream in arrayStreamings ){
            if ( stream.participantID == kSPT_LOCAL_CALLPARTICIPANT_ID ){
                iRemoteStreamings --;
            }
        }

        CGRect *pRects = nil;
        if ( iRemoteStreamings <= 1 )
            pRects = rects1;
        else
            if ( iRemoteStreamings == 2 )
                pRects = rects2;
            else
                pRects = rects4;

        NSInteger count = 0;
        for ( ISptCallStream *stream in _dictVideoStreamings.allValues ){
            UIView<SptMediaView> *view = stream.view;
            if ( view != nil ){
                CGRect r = bounds;
                CGRect rAssigned = {0};

                if ( iRemoteStreamings > 0 && stream.participantID == kSPT_LOCAL_CALLPARTICIPANT_ID ){
                    rAssigned = rectLocal;
                }else
                    if ( count >= 4 ){
                        view.hidden = YES;
                        continue;
                    }else{
                        rAssigned = pRects[count];
                        count ++;
                    }

                if ( horizontal ){
                   rAssigned = CGRectMake( rAssigned.origin.y, rAssigned.origin.x, rAssigned.size.height, rAssigned.size.width );
                }

                r.origin.x = r.size.width * rAssigned.origin.x;
                r.origin.y = r.size.height * rAssigned.origin.y;
                r.size.width = r.size.width * rAssigned.size.width;
                r.size.height = r.size.height * rAssigned.size.height;

                view.frame = r;
                view.hidden = NO;

                if ( stream.participantID == kSPT_LOCAL_CALLPARTICIPANT_ID ){
                    [self.view bringSubviewToFront:view];
                }else{
                    [self.view sendSubviewToBack:view];
                }
            }
        }

        [self.view bringSubviewToFront:_buttonHangup];
    }else{
        _sharingMediaView.view.frame = self.view.bounds;
        NSInteger count = 0;
        for ( ISptCallStream *stream in _dictVideoStreamings.allValues ){
            UIView<SptMediaView> *view = stream.view;
            if ( view != nil ){
                CGRect r = bounds;
                CGFloat length = ((horizontal)?(r.size.height):(r.size.width))*0.2;
                view.frame = CGRectMake( length * count, r.size.height - length, length, length);
                view.hidden = NO;

                [self.view sendSubviewToBack:view];
                count ++;
            }
        }

        [self.view sendSubviewToBack:_sharingMediaView.view];
    }

    [self.view bringSubviewToFront:_buttonHangup];
}

-(void)setSharingMediaView:(id<SptMediaView>)sharingMediaView{
    if ( sharingMediaView == nil && _sharingMediaView != nil ){
        [_sharingMediaView.view removeFromSuperview];
        _sharingMediaView = nil;
    }

    if ( sharingMediaView != nil && _sharingMediaView == nil ){
        _sharingMediaView = sharingMediaView;
        [self.view addSubview:_sharingMediaView.view];
    }

    [self updateStreamingRects];
}

-(void)OnDocumentSelected:(NSURL*)url{
    _localSharedDocument = [LocalSharedDocument localSharedDocument:url];
    self.sharingMediaView = _localSharedDocument;
}

-(void)OnDocumentSelectionCanceled{
    [CollaborateUtils.Instance.api answerCallRequest:_sharingRequest accept:NO];
}

- (IBAction)onAnnotatePressed:(id)sender {
    if ( _sharingMediaView != nil ){
        _sharingMediaView.enableAnnotation = !_sharingMediaView.enableAnnotation;
        _buttonAnnotate.selected = _sharingMediaView.enableAnnotation;
    }
}

-(void)onStreamAnnotationEnabled:(ISptCallStream *)stream enabled:(BOOL)enabled{
    _buttonAnnotate.hidden = !enabled;

    SptAnnotation *annotation = [stream getAnnotationData];
    if ( annotation != nil ){
        [annotation setAnnotationTool:kAnnToolBrush];
        [annotation setAnnotationColor:YES setColor:UIColor.redColor];

        if ( _localSharedDocument != nil ){
            _localSharedDocument.annotationStream = stream;
        }
    }
}
@end

//
//  MainViewController.m
//  TestCollaborateIOS
//
//  Copyright © 2019 ClearOne. All rights reserved.
//

#import "MainViewController.h"
#import "StartingCallViewController.h"
#import "CallViewController.h"

@interface MainViewController ()
@property (nonatomic, retain) StartingCallViewController *startingCallViewController;
@property (nonatomic, retain) CallViewController *callViewController;
@property (weak, nonatomic) IBOutlet UILabel *infoLabel;

@end

@implementation MainViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    /**
     We just have to set this object as callback for CallManager events
     */
    CollaborateUtils.Instance.callManagerCallback = self;
}


-(void)onNewCall:(ISptCall*)call incoming:(BOOL)incoming{
    /**
     When a new call appears we present "Starting Call" view controller
     */
    if ( _startingCallViewController != nil ){
        [_startingCallViewController dismissViewControllerAnimated:NO completion:nil];
    }
    _startingCallViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"startingCallViewController"];
    _startingCallViewController.call = call;
    [self presentViewController:_startingCallViewController animated:NO completion:nil];
}

-(void)onCallEstablished:(ISptCall*)call {
    /**
     If the call is Established, we hide "Starting Call" view controller and show "In Call" view controller
     */
    if ( _startingCallViewController != nil ){
        [_startingCallViewController dismissViewControllerAnimated:NO completion:nil];
    }
    
    _callViewController = [self.storyboard instantiateViewControllerWithIdentifier:@"callViewController"];
    _callViewController.call = call;
    [self presentViewController:_callViewController animated:NO completion:nil];
}

-(void)onCallFinished:(ISptCall*)call{
    /**
     When the call is finished, we just hide all call viewcontrollers
     */
    if ( _callViewController != nil ){
        [_callViewController dismissViewControllerAnimated:NO completion:nil];
    }
    
    if ( _startingCallViewController != nil ){
        [_startingCallViewController dismissViewControllerAnimated:NO completion:nil];
    }
}
-(void)onMeetingsSynchronized{
    //If we entered with a meeting Personal ID
    if ( CollaborateUtils.Instance.loginMeetingSeqID != kSPT_INVALID_MEETING_SEQUENCE_ID ){
        // now, we can get information form this meeting
        SptSchMeetingSequence *meetingSeq = [CollaborateUtils.Instance.api getSchMeetingSequenceByID:CollaborateUtils.Instance.loginMeetingSeqID];
        if ( meetingSeq != nil ){
            //In the case there is an active meeting we should join it
            if ( meetingSeq.currentMeeting != nil ){
                self.infoLabel.text = @"";
                [CollaborateUtils.Instance.api joinSchMeeting:meetingSeq.meetingSequenceID
                                                      meeting:meetingSeq.currentMeeting.meetingID
                                                      videoON:NO];
            } else {
                self.infoLabel.text = @"No meeting available";
            }
        }
        
        CollaborateUtils.Instance.loginMeetingSeqID = kSPT_INVALID_MEETING_SEQUENCE_ID;
    }
}
@end

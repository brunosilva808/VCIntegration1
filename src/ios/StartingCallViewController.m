//
//  StartingCallViewController.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "StartingCallViewController.h"

@interface StartingCallViewController ()
@property (strong, nonatomic) IBOutlet UILabel *labelTitle;
@property (strong, nonatomic) IBOutlet UILabel *labelParticipant;
@property (strong, nonatomic) IBOutlet UIImageView *imageParticipant;
@property (strong, nonatomic) IBOutlet UIButton *buttonAnswer;
@property (strong, nonatomic) IBOutlet UIButton *buttonCancel;
@property (strong, nonatomic) IBOutlet UIButton *buttonReject;
@property (assign, nonatomic) BOOL incommingCall;

@end

@implementation StartingCallViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self updateCall];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)setCall:(ISptCall *)call{
    _call = call;
    _incommingCall = (_call.callState == kCallStateRinging);
    [self updateCall];
}

-(void)updateCall{
    if ( !_incommingCall ){
        _buttonAnswer.hidden = YES;
        _buttonReject.hidden = YES;
        _buttonCancel.hidden = NO;
        _labelTitle.text = (_call.meeting!=nil)?@"Joining":@"Calling";
        
        NSMutableString *participantText = [NSMutableString string];
        for ( ISptCallParticipantData *participant in [_call getParticipants:YES] ){
            if ( participant.callParticipantID != kSPT_LOCAL_CALLPARTICIPANT_ID ){
                if ( participantText.length > 0 ){
                    [participantText appendString:@", "];
                }
                
                [participantText appendString:participant.displayName];
            }
        }
        _labelParticipant.text = participantText;
    }else{
        _buttonCancel.hidden = YES;
        _buttonAnswer.hidden = NO;
        _buttonReject.hidden = NO;
        _labelTitle.text = @"Incoming Call";
        _labelParticipant.text = _call.moderator.displayName;
    }
}
- (IBAction)onReject:(id)sender {
    [CollaborateUtils.Instance.api rejectCall:_call.callID];
}

- (IBAction)onAnswer:(id)sender {
    [CollaborateUtils.Instance.api acceptCall:_call.callID videoOn:(_call.callStartedType==kCallTypeVideo)];
}

- (IBAction)onCancel:(id)sender {
    [CollaborateUtils.Instance.api hangUpCall:_call.callID];
}

@end

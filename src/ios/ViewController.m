//
//  ViewController.m
//  DCourts
//
//  Created by Guest  on 09/03/2019.
//  Copyright © 2019 AB. All rights reserved.
//

#import "ViewController.h"
#import "CollaborateUtils.h"
#import "CallViewController.h"



@interface ViewController ()

//@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;
@property (nonatomic, assign) SptMeetingSeqID meetingSeqID;
@property (nonatomic, assign) SptMeetingID meetingID;
@property (nonatomic, assign) BOOL loginWithMeetingToken;
@property (nonatomic, assign) JoinMeetingError joinMeetingError;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    CollaborateUtils *instance = [CollaborateUtils Instance];

    CollaborateUtils.Instance.loginCallback = self;
    _meetingSeqID = kSPT_INVALID_MEETING_ID;

    //_activityIndicator.hidden = NO;

    NSString *server = @"collaboratespace.net";
    NSString *token = @"32453830";

    UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Testing"
                                      message:@"Inside ViewController"
                                     delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];
    NSLog(@"VC - before CollaborateUtils.Instance.api");
//    [alert show];
//
//   if ([server length] == 0)
//       [CollaborateUtils.Instance.api getTokenData:token server:nil];
//    else
       [CollaborateUtils.Instance.api getTokenData:token server:server];

    NSLog(@"VC - after CollaborateUtils.Instance.api");

}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)onLoginResult:(BOOL)loginOK error:(eSptConnectionResult)error{
    if ( loginOK ){
        // in case we are login with meeting token, wait for onMeetingsSynchronized
        if (!_loginWithMeetingToken)
        {
          //  _activityIndicator.hidden = YES;
            [self performSegueWithIdentifier:@"showMain" sender:self];
        }
    }else{
      //  _activityIndicator.hidden = YES;
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error connecting" message:@"Unable to login to the service" preferredStyle:UIAlertControllerStyleAlert ];
        [alert addAction:[UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleDefault handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

-(void)onGetTokenDataResult:(SptTokenDataResult *)tokenDataResult{
    NSString *error = nil;

    switch ( tokenDataResult.result ){
        case kSptTokenDataResultJoinMeeting:
            //It is a token to join meeting
            _loginWithMeetingToken = YES;
            _meetingSeqID = tokenDataResult.meetingSequenceID;
            [CollaborateUtils.Instance.api loginWithTokenDataResult:tokenDataResult];
            break;
        case kSptTokenDataResultLogin:
            //It is a token to login
            [CollaborateUtils.Instance.api loginWithTokenDataResult:tokenDataResult];
            break;
        case kSptTokenDataResultError:
            error = @"Error retrieving token data";
            //Any other error in the token patameters
            break;
        case kSptTokenDataResultServerNotReachable:
            error = @"Server not reachable";
            //Cannot reach server, try later?
            break;
        case kSptTokenDataResultInvalidToken:
            error = @"Invalid token";

            //Token is invalid, nothing else
            break;
    }

    if ( error != nil ){
      //  _activityIndicator.hidden = YES;
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error connecting"
                                                                       message:error
                                                                preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

-(void)onMeetingsSynchronized
{
    //Meetings are synchronized, in case we are in a login with meeting token process
    //we have to look for the meeting sequence and join active meeting if there is one.
    //in case we are not in a login with meeting token process, ignore

    NSLog(@"VC - onMeetingsSynchronized");
    if (_loginWithMeetingToken)
    {
      //  _activityIndicator.hidden = YES;
        SptSchMeetingSequence *meetingSeq = [CollaborateUtils.Instance.api getSchMeetingSequenceByID:_meetingSeqID];
        if (meetingSeq != nil)
        {
            UIAlertController *alert = nil;
            SptSchMeeting *currentMeeting = [meetingSeq currentMeeting];
            if (currentMeeting != nil)
            {
                //Check meeting is active
                switch (currentMeeting.schMeetingState) {
                    case kSptSchMeetingStateWaitingHost:
                        _joinMeetingError = eWaitingHost;
                        break;
                    case kSptSchMeetingStateActive:
                        //Join meetin
                        _meetingID = [currentMeeting meetingID];
                        break;

                    default:
                        break;
                }
            }
            else
            {
                SptSchMeeting *nextMeeting = [meetingSeq nextMeeting];
                if (nextMeeting != nil)
                {
                    switch (nextMeeting.schMeetingState) {
                        case kSptSchMeetingStateNone:
                        case kSptSchMeetingStateCreating:
                            break;
                        case kSptSchMeetingStateCreated:
                            _joinMeetingError = eMeetingNotStarted;
                            break;
                        case kSptSchMeetingStateFinished:
                            _joinMeetingError = eMeetingFinished;
                            break;

                        case kSptSchMeetingStateCancelled:
                            _joinMeetingError = eMeetingCancelled;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    SptSchMeeting *lastMeeting = [meetingSeq lastMeeting];
                    switch (lastMeeting.schMeetingState) {
                        case kSptSchMeetingStateFinished:
                            _joinMeetingError = eMeetingFinished;
                            break;

                        case kSptSchMeetingStateCancelled:
                            _joinMeetingError = eMeetingCancelled;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        else
        {
            _joinMeetingError = eNoMeetingFound;
        }

      //  UIStoryboard* sb = [UIStoryboard storyboardWithName:@"Main1" bundle:nil];

      //  UIViewController* _launchScreenViewController = [sb instantiateViewControllerWithIdentifier:@"CallViewController1"];
      NSLog(@"VC - onMeetingsSynchronized 2");
      CallViewController* _launchScreenViewController = [[CallViewController alloc] init];

      //[_launchScreenViewController setMeetingID:_meetingID];

      if (_loginWithMeetingToken && _meetingSeqID != kSPT_INVALID_MEETING_SEQUENCE_ID)
      {
          [_launchScreenViewController setMeetingID:_meetingID];
          [_launchScreenViewController setSeqID:_meetingSeqID];
          [_launchScreenViewController setJoinMeetingError:_joinMeetingError];
      }
      else
      {
          [_launchScreenViewController setMeetingID:kSPT_INVALID_MEETING_ID];
          [_launchScreenViewController setSeqID:kSPT_INVALID_MEETING_SEQUENCE_ID];
          [_launchScreenViewController setJoinMeetingError:eNoError];
      }

      //  UIViewController* _launchScreenViewController = [[CallViewController alloc] init];

      //  UIViewController* _launchScreenViewController = [[CallViewController alloc] init];
      //  _launchScreenStartAlpha = _launchScreenViewController.view.alpha;

      //   _launchScreenViewController.view.alpha = _launchScreenStartAlpha;
    //  [self.viewController addChildViewController:_launchScreenViewController];

      [self presentViewController:_launchScreenViewController animated:YES completion:nil];

     //    [appDelegate.window.rootViewController presentViewController:_launchScreenViewController animated:NO completion: nil];

      //  _launchScreenViewController.view.frame = self.viewController.view.frame;
      //  [self.viewController.navigationController pushViewController: _launchScreenViewController animated: NO];
      //  _launchScreenViewController.view.frame = self.viewController.view.frame;
      //    [self.viewController.view addSubview:_launchScreenViewController.view];
      //  [_launchScreenViewController didMoveToParentViewController:self.viewController];

        //[self performSegueWithIdentifier:@"showMain" sender:self];
    }
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ( [segue.identifier isEqualToString:@"showMain" ] ){
        CallViewController *callView = (CallViewController*)segue.destinationViewController;
        if (_loginWithMeetingToken && _meetingSeqID != kSPT_INVALID_MEETING_SEQUENCE_ID)
        {
            [callView setMeetingID:_meetingID];
            [callView setSeqID:_meetingSeqID];
            [callView setJoinMeetingError:_joinMeetingError];
        }
        else
        {
            [callView setMeetingID:kSPT_INVALID_MEETING_ID];
            [callView setSeqID:kSPT_INVALID_MEETING_SEQUENCE_ID];
            [callView setJoinMeetingError:eNoError];
        }
    }
}


@end

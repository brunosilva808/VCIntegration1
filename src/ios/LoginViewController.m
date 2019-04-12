//
//  LoginViewController.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "LoginViewController.h"
#import "AskblueUtils.h"

@interface LoginViewController ()

@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;

@end

@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    CollaborateUtils.Instance.loginCallback = self;
  
    [self onMeetingTokenGo:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)onLoginResult:(BOOL)loginOK error:(eSptConnectionResult)error{
    _activityIndicator.hidden = YES;
    
    if ( loginOK ){
        [self performSegueWithIdentifier:@"showMain" sender:self];
    }else{
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error connecting" message:@"Unable to login to the service" preferredStyle:UIAlertControllerStyleAlert ];
        [alert addAction:[UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleDefault handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

- (IBAction)onMeetingTokenGo:(id)sender {
    _activityIndicator.hidden = NO;
    
    AskblueUtils *instanceAB = [AskblueUtils Instance];
    [CollaborateUtils.Instance.api getTokenData:[NSString stringWithFormat:@"%@", [instanceAB myToken]]
                                         server:[NSString stringWithFormat:@"%@", [instanceAB myServer]]];
}

-(void)onGetTokenDataResult:(SptTokenDataResult *)tokenDataResult{
    NSString *error = nil;
    
    switch ( tokenDataResult.result ){
        case kSptTokenDataResultJoinMeeting:
        {
            CollaborateUtils.Instance.loginMeetingSeqID = tokenDataResult.meetingSequenceID;
        }
        case kSptTokenDataResultLogin:
            //Lets login with the given credentials
            [CollaborateUtils.Instance.api loginWithTokenDataResult:tokenDataResult];
            CollaborateUtils.Instance.loginMeetingSeqID = tokenDataResult.meetingSequenceID;
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
        _activityIndicator.hidden = YES;
        UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"Error connecting"
                                                                       message:error
                                                                preferredStyle:UIAlertControllerStyleAlert];
        [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleCancel handler:nil]];
        [self presentViewController:alert animated:YES completion:nil];
    }
}

@end

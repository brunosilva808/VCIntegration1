//
//  LoginViewController.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "LoginViewController.h"
#import "AskblueUtils.h"

@interface LoginViewController ()
//@property (strong, nonatomic) IBOutlet UITextField *editLogin;
//@property (strong, nonatomic) IBOutlet UITextField *editPassword;
@property (strong, nonatomic) IBOutlet UITextField *editServer;
@property (strong, nonatomic) IBOutlet UITextField *editServerToken;
//@property (strong, nonatomic) IBOutlet UIButton *buttonLogin;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *activityIndicator;
@property (nonatomic, assign) BOOL usingStoredCredentials;
//@property (strong, nonatomic) IBOutlet UIView *loginView;
//@property (strong, nonatomic) IBOutlet UIView *tokenView;
@property (strong, nonatomic) IBOutlet UITextField *editToken;
@property (strong, nonatomic) IBOutlet UIButton *buttonTokenGo;
@property (weak, nonatomic) IBOutlet UIButton *switchToLoginButton;

@end

@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];

    CollaborateUtils.Instance.loginCallback = self;



    _editToken.text = @"70556633";


    _editServerToken.text = @"collaboratespace.net";
//    _tokenView.hidden = YES;
//    _loginView.hidden = YES;

//    [self enableLoginButton];

//    if ( _usingStoredCredentials ){
//        [self onLoginPressed:nil];
//    }

    [self onTokenFieldsModified:nil];

    [self onMeetingTokenGo:nil];
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];

//    [self onSwitchToMeetingID:nil];
    [_switchToLoginButton setHidden:true];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//- (IBAction)onLoginPressed:(id)sender {
//    if ( !_usingStoredCredentials ){
//        SptLoginData *loginData = [SptLoginData loginDataWithData:YES email:_editLogin.text password:_editPassword.text sever:_editServer.text];
//        [CollaborateUtils.Instance.api setLoginData:loginData];
//    }
//
//    [CollaborateUtils.Instance.api connect];
//    _activityIndicator.hidden = NO;
//}

- (IBAction)onEditChanged:(id)sender {
    if ( _usingStoredCredentials ){
        _usingStoredCredentials = NO;
    }
//    [self enableLoginButton];
    if ( sender == _editServer )
        _editServerToken.text = _editServer.text;

}

//-(void)enableLoginButton{
//    _buttonLogin.enabled = (_editLogin.text.length > 0)
//                            && (_editPassword.text.length > 0)
//                            && (_editServer.text.length > 0);
//}

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

//- (IBAction)onSwitchToLogin:(id)sender {
//    [self show:@[_loginView] andHide:@[_tokenView]];
//}
//
//- (IBAction)onSwitchToMeetingID:(id)sender {
//    [self show:@[_tokenView] andHide:@[_loginView]];
//}

-(void)show:(NSArray<UIView*>*)viewsToShow andHide:(NSArray<UIView*>*)viewsToHide{
    for ( UIView *view in viewsToHide ){
        [UIView animateWithDuration:0.5 animations:^{
            view.alpha = 0.0F;
        }completion:^(BOOL finished) {
            view.hidden = YES;
            view.alpha = 1.0F;
        }];
    }

    for ( UIView *view in viewsToShow ){
        view.alpha = 0.0F;
        view.hidden = NO;
        [UIView animateWithDuration:0.5 animations:^{
            view.alpha = 1.0F;
        }];
    }
}
- (IBAction)onTokenFieldsModified:(id)sender {
    _buttonTokenGo.enabled = (_editToken.text.length > 0 && _editServerToken.text.length>0);

    if ( sender == _editServerToken )
        _editServer.text = _editServerToken.text;
}

- (IBAction)onMeetingTokenGo:(id)sender {
    _activityIndicator.hidden = NO;

//#ifdef
    [CollaborateUtils.Instance.api getTokenData:_editToken.text server:_editServerToken.text];
//#else
    AskblueUtils *instanceAB = [AskblueUtils Instance];
    [CollaborateUtils.Instance.api getTokenData:[NSString stringWithFormat:@"%@", [instanceAB myToken]]
                                         server:[NSString stringWithFormat:@"%@", [instanceAB myServer]]];
//#endif
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

/*


     -(void)OnTokenMgrError:(NSString *)error{
         [self.navigationController popToViewController:self animated:YES];
         UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"text_error_connecting".localized message:error delegate:nil cancelButtonTitle:@"text_ok".localized otherButtonTitles: nil];
         [alert show];

         [JoinWithTokenMgr.instance reset];
     }
     - (void)onGetTokenDataResult:(SptTokenDataResult *)tokenDataResult{
         NSString *error = nil;

         switch ( tokenDataResult.result ){
             case kSptTokenDataResultJoinMeeting:
                 _meetingSeq = tokenDataResult.meetingSequenceID;
             case kSptTokenDataResultLogin:
                 //Lets login with the given credentials
                 _connecting = YES;
                 [self.api loginWithTokenDataResult:tokenDataResult];
                 _meetingSeq = tokenDataResult.meetingSequenceID;
                 [self performSegueWithIdentifier: @"segueShowProgress" sender:self];
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
             UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"text_error_connecting".localized message:error delegate:nil cancelButtonTitle:@"text_ok".localized otherButtonTitles: nil];
             [alert show];
         }
     }
     -(void)onConnectionError:(eSptConnectionResult)eResult{
         [JoinWithTokenMgr.instance reset];
         if ( eResult == kSptIMConnect_OK )
             return ;
         if ( _connecting ){
             if ( eResult != kSptIMConnect_GDPR ){
                 [self hideActivity];

                 NSDictionary *textErrors = @{ @(kSptIMConnect_Error):@"Error connecting to service",
                                               @(kSptIMConnect_NetworkError):@"Network Error",
                                               @(kSptIMConnect_AuthError):@"Authentication Error",
                                               @(kSptIMConnect_CredentialsError):@"Invalid credentials",
                                               @(kSptIMConnect_ClientVersion):@"Version not supported"};
                 NSString *error = [textErrors objectForKey:@(eResult)] ;
                 if ( error == nil )
                     error = [textErrors objectForKey:@(kSptIMConnect_Error)];

                 dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                     UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"text_error_connecting".localized message:error delegate:nil cancelButtonTitle:@"text_ok".localized otherButtonTitles: nil];
                     [alert show];
                     if ( _viewControllerProgress != nil )
                         [self.navigationController popToViewController:self animated:YES];
                 });
             }
             _connecting = NO;
         }
     }
*/
@end

#import "VCIntegration.h"
#import "ViewController.h"

@implementation VCIntegration

//- (void)show:(CDVInvokedUrlCommand*)command
- (void) show:(NSMutableArray*)arguments withDict:(NSMutableDictionary*)options
{

  //  NSString* name = [[command arguments] objectAtIndex:0];
  //  NSString* msg = [NSString stringWithFormat: @"Hello, %@", name];

    NSString* serverName = [arguments objectAtIndex:0];
//    NSString* userMail = [[command arguments] objectAtIndex:1];
//    NSString* passWord = [[command arguments] objectAtIndex:2];
  //  NSString* personalID = [[command arguments] objectAtIndex:1];

    NSString* personalID = [arguments objectAtIndex:1];

    //NSLog(@"VC - VCIntegration1 %@", serverName);
  //  NSLog(@"VC - VCIntegration2 %@", userMail);
  //  NSLog(@"VC - VCIntegration3 %@", passWord);
  //  NSLog(@"VC - VCIntegration4 %@", personalID);


    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsString:msg];

   UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Testing"
                                     message:@"Im in the Cordova plugin"
                                    delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];

   //[alert show];

   _storyboardName = @"Main1";

   UIStoryboard* sb = [UIStoryboard storyboardWithName:_storyboardName bundle:nil];


//   _launchScreenViewController = [sb instantiateInitialViewController];



  //  self.sb = [UIStoryboard storyboardWithName:_storyboardName bundle:nil];
//   _launchScreenViewController = [sb instantiateInitialViewController];

   _launchScreenViewController = [[ViewController alloc] init];
   _launchScreenStartAlpha = _launchScreenViewController.view.alpha;

    _launchScreenViewController.view.alpha = _launchScreenStartAlpha;
    [self.viewController addChildViewController:_launchScreenViewController];

//    [appDelegate.window.rootViewController presentViewController:_launchScreenViewController animated:NO completion: nil];


  //  [self.viewController.navigationController pushViewController: _launchScreenViewController animated: YES];
    _launchScreenViewController.view.frame = self.viewController.view.frame;
    [self.viewController.view addSubview:_launchScreenViewController.view];
    [_launchScreenViewController didMoveToParentViewController:self.viewController];

    [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];


}

@end

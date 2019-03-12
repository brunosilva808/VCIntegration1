#import "VCIntegration.h"

@implementation VCIntegration

- (void)show:(CDVInvokedUrlCommand*)command
{

    NSString* name = [[command arguments] objectAtIndex:0];
    NSString* msg = [NSString stringWithFormat: @"Hello, %@", name];

    CDVPluginResult* result = [CDVPluginResult
                               resultWithStatus:CDVCommandStatus_OK
                               messageAsString:msg];

   UIAlertView *alert = [[UIAlertView alloc]initWithTitle:@"Testing"
                                     message:@"Im in the Cordova plugin"
                                    delegate:nil cancelButtonTitle:@"ok" otherButtonTitles: nil];

   //[alert show];

   _storyboardName = @"Main1";

   UIStoryboard* sb = [UIStoryboard storyboardWithName:_storyboardName bundle:nil];

  //  self.sb = [UIStoryboard storyboardWithName:_storyboardName bundle:nil];
   _launchScreenViewController = [sb instantiateInitialViewController];
   _launchScreenStartAlpha = _launchScreenViewController.view.alpha;

    _launchScreenViewController.view.alpha = _launchScreenStartAlpha;
    [self.viewController addChildViewController:_launchScreenViewController];
    _launchScreenViewController.view.frame = self.viewController.view.frame;
    [self.viewController.view addSubview:_launchScreenViewController.view];
    [_launchScreenViewController didMoveToParentViewController:self.viewController];

    [self.commandDelegate sendPluginResult:result callbackId:command.callbackId];


}

@end

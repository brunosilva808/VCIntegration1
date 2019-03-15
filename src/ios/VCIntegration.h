#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <CollaborateSpace/CollaborateSpace.h>
#import "ViewController.h"


@interface VCIntegration : CDVPlugin  {
    ViewController* _launchScreenViewController;
    NSString* _storyboardName;
//    NSString* serverName;
//    NSString* personalID;
    float _launchScreenStartAlpha;

}

- (void) show:(CDVInvokedUrlCommand*) command;

@end

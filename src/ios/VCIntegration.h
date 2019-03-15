#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <CollaborateSpace/CollaborateSpace.h>
#import "ViewController.h"

// <VCIntegrationDelegate>

@interface VCIntegration : CDVPlugin  {
    ViewController* _launchScreenViewController;
    NSString* _storyboardName;
    float _launchScreenStartAlpha;

}

- (void) show:(CDVInvokedUrlCommand*) command;

@end

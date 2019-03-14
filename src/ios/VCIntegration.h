#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import <CollaborateSpace/CollaborateSpace.h>


@interface VCIntegration : CDVPlugin  {
    UIViewController* _launchScreenViewController;
    NSString* _storyboardName;
    float _launchScreenStartAlpha;

}

- (void) show:(CUIDVInvokedUrlCommand*)command;

@end

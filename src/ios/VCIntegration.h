#import <Cordova/CDV.h>
#import <UIKit/UIKit.h>
#import "ViewController.h"
#import <CollaborateSpace/CollaborateSpace.h>


@interface VCIntegration : CDVPlugin  {
    UIViewController* _launchScreenViewController;
    NSString* _storyboardName;
    float _launchScreenStartAlpha;

}

//- (void) show:(NSMutableArray*)arguments withDict:(NSMutableDictionary*)options;
- (void) show:(CUIDVInvokedUrlCommand*)command;

@end

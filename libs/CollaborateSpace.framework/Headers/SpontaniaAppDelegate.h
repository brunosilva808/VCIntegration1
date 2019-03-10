/**
  SpontaniaAppDelegate.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne. All rights reserved.
*/

#import <UIKit/UIKit.h>
#import "ISpontaniaIMApi.h"


/**
 @class SpontaniaAppDelegate
 Application delegate base class
 In order to integrate with COLLABORATE Space SDK you have to inherit from this object
 */
@interface SpontaniaAppDelegate : UIResponder<UIApplicationDelegate>
{
    @protected
    ISpontaniaIMApi *m_sptAPI;
}

@property (strong, nonatomic) UIWindow *window;


-(BOOL)sptApplication:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions;
-(void)sptApplication:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo;
-(void)sptApplication:(UIApplication *)application didReceiveLocalNotification:(UILocalNotification *)notification;
-(void)sptApplication:(UIApplication *)application didReceiveCallNotification:(NSDictionary *)userInfo;

- (void)sptApplicationWillResignActive:(UIApplication *)application;
- (void)sptApplicationDidEnterBackground:(UIApplication *)application;
- (void)sptApplicationWillEnterForeground:(UIApplication *)application;
- (void)sptApplicationDidBecomeActive:(UIApplication *)application;
- (void)sptApplicationWillTerminate:(UIApplication *)application;


@end


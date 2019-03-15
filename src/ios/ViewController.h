//
//  ViewController.h
//  DCourts
//
//  Created by Guest  on 09/03/2019.
//  Copyright © 2019 AB. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CollaborateUtils.h"


@protocol VCIntegrationDelegate <NSObject>
@required
-(NSString *) onGetPersonalID;
-(NSString *) onGetServerName;
@end

@interface ViewController : UIViewController <CollaborateLoginCallback>

@property (nonatomic, assign) id<VCIntegrationDelegate> delegate;
@property (nonatomic, retain) NSString* serverName;
@property (nonatomic, retain) NSString* personalID;

@end

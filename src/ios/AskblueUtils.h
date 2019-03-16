//
//  CollaborateUtils.h
//  TestCollaborateIOS
//
//  Copyright © 2019 Askblue. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AskblueUtils : NSObject

+(AskblueUtils*)Instance;

@property (nonatomic, retain) NSString *myServer;
@property (nonatomic, retain) NSString *myToken;

@end

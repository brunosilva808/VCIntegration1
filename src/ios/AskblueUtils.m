//
//  CollaborateUtils.m
//  TestCollaborateIOS
//
//  Copyright © 2019 Askblue. All rights reserved.
//

#import "AskblueUtils.h"

@implementation AskblueUtils

+(AskblueUtils*)Instance{
    /**
     Here we maintain an static object for this class
     */
    static AskblueUtils *instance = nil;
    if ( instance == nil )
        instance = [[AskblueUtils alloc]init];

    return instance;
}

-(id)init{
    self = [super init];

    //Here we initialize askblue variables

    return self;
}

@end

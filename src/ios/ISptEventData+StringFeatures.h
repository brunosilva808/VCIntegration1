//
//  ISptEventData+StringFeatures.h
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import <CollaborateSpace/CollaborateSpace.h>

/**
 Just
 */
@interface ISptEventData (StringFeatures)
@property (readonly) NSString *text;
@property (readonly) NSString *contactText;
@property (readonly) NSString *textFull;
@property (readonly) NSString *dateText;
@property (readonly) BOOL notification;
@end


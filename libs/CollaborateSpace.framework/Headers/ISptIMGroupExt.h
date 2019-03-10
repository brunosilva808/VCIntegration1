//
//  ISptIMGroupExt.h
//  SptIMCoreIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.


#import <Foundation/Foundation.h>
#import "ISptTypes.h"


/**
 @class ISptGroupData
 Group of contacts data
 */
@interface ISptGroupData : NSObject

/**
 Groud unique ID
 */
@property (readonly) SptIMGroupID groupID;
/**
 Group display name
 */
@property (readonly) NSString * displayName;
/**
 NSArray of ISptContactData with the contacts that belong to the group
 */
@property (readonly) NSArray *contacts;

/**
 Check if a contact belong to the group

 @param contactID Contact ID
 @return YES in case contact belong to the group, NO otherwise
 */
-(BOOL)contactBelongTo:(TSptIMContactID)contactID;
@end


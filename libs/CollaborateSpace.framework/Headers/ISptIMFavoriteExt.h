/**
  ISptIMFavoriteExt.h
  SptIMCoreIOS

  Copyright © 2017 ClearOne Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ISptTypes.h"

@class ISptRoomData;
@class ISptContactData;
@class SptSchMeetingSequence;


/**
 @class ISptFavoriteData
 Favorite data
 */
@interface ISptFavoriteData : NSObject

/**
 Favorite type

 - eSptFavoriteTypeContact: Favorite is a contact
 - eSptFavoriteTypeRoom: Favorite is a room, chat or channel
 - eSptFavoriteTypeMeeting: Favorite is a meeting sequence
 */
typedef NS_ENUM(NSUInteger, eSptFavoriteType)
{
    eSptFavoriteTypeContact,
    eSptFavoriteTypeRoom,
    eSptFavoriteTypeMeeting,
};

/**
 Favorite unique ID
 */
@property (readonly) SptIMFavoriteID favoriteID;
/**
 Favorite display name, the display name depending on the type
 */
@property (readonly) NSString *displayName;
/**
 Favorite picture
 */
@property (readonly) UIImage *picture;
/**
 Room Data in case it is a room
 */
@property (readonly) ISptRoomData *roomData;
/**
 Contact data in case iot is a contact
 */
@property (readonly) ISptContactData *contactData;
/**
 Meeting sequence data in case of meeting sequence
 */
@property (readonly) SptSchMeetingSequence *meetingSequence;
/**
 Favorite type
 */
@property (readonly) eSptFavoriteType type;

@end


/**
  ISptIMContactExt.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "ISptTypes.h"
#import "ISptIMFavoriteExt.h"
#import "ISptContactBaseProtocol.h"

@class ISptRoomData;

@interface SptProfileField : NSObject

/*!
 @typedef eProfileFieldType
 @brief Profile field type
 @constant kTypePhone: Phone number
 @constant kTypeEmail: Email address
 @constant kTypeEndpoint: Endpoint address
 */
typedef NS_ENUM(NSUInteger, eProfileFieldType)
{
    kTypePhone  = 0,
    kTypeEmail,
    kTypeEndpoint,
    kTypeMax
};

/*!
 @typedef eFieldDescription
 @brief Profile field description
 @constant kTypeNone: No data
 @constant kTypeMobile: Mobile
 @constant kTypeWork: Work
 @constant kTypeHome: Home
 */
typedef NS_OPTIONS(NSUInteger, eFieldDescription)
{
    kTypeNone     = 0,
    kTypeMobile   = 1 << 0,
    kTypeWork     = 1 << 1,
    kTypeHome     = 1 << 2
};

/**
 Type of profile field
 */
@property (readonly) eProfileFieldType type;

/**
 Description of profile field
 */
@property (readonly) eFieldDescription decription;

/**
 Destination profile field
 */
@property (readonly) NSString *data;

/**
 Offline profile field
 */
@property (readonly) BOOL isOffline;

@end


/**
 @class ISptContactProfile
 Contact profile
 */
@interface ISptContactProfile : NSObject

/**
 Conatct name
 */
@property (readonly) NSString *name;
/**
 Conatct middle name
 */
@property (readonly) NSString *middleName;
/**
 Conatct last name
 */
@property (readonly) NSString *lastName;
/**
 Conatct display name
 */
@property (readonly) NSString *displayName;

/**
 Conatct comapany name
 */
@property (readonly) NSString *company;
/**
 Conatct work division
 */
@property (readonly) NSString *division;
/**
 Conatct work title
 */
@property (readonly) NSString *workTitle;
/**
 Conatct home address
 */
@property (readonly) NSString *homeAddress;
/**
 Conatct home city
 */
@property (readonly) NSString *homeCity;
/**
 Conatct home state
 */
@property (readonly) NSString *homeState;
/**
 Conatct home country
 */
@property (readonly) NSString *homeCountry;

/**
 Conatct birth day
 */
@property (readonly) NSDate *birthDay;
/**
 Conatct picture
 */
@property (readonly) UIImage *picture;
/**
 Conatct color
 */
@property (readonly) UIColor *color;

/**
 Get all phone numbers
 @result A array with all phone numbers
 */
@property (readonly) NSArray <SptProfileField*>*phoneNumbers;

/**
 Get all email address
 @result A array with all email address
 */
@property (readonly) NSArray <SptProfileField*>*emailAddresses;

@end


/**
 @class ISptLocalProfile
 @brief Class to encapsulate local user vCard
 
 The process to update local user vCard is to call to [ISpontaniaIMApi getLocalProfile] to retrieve current profile,
 change it and call to [ISpontaniaIMApi setContactProfile:] to store it
 */
@interface ISptModifyProfile : NSObject

/**
@typedef eModifiableField
@brief Modifiable profile fields
@constant eAllFieldsModifiables: All fields of the profile are modifiable
@constant eAllOfflineFieldsModifiables: Only offline profile fields are modifiable
 */
typedef NS_ENUM(NSUInteger, eModifiableField)
{
    eAllFieldsModifiables,
    eAllOfflineFieldsModifiables
};

/**
 Modifiable fields
 */
@property (readonly) eModifiableField modifiableFields;

/**
 Contact name
 */
@property (readwrite) NSString *name;
/**
 Contact middle name
 */
@property (readwrite) NSString *middleName;
/**
 Contact last name
 */
@property (readwrite) NSString *lastName;
/**
 Contact display name
 */
@property (readonly) NSString *displayName;
/**
 Contact compary name
 */
@property (readwrite) NSString *company;
/**
 Contact work division
 */
@property (readwrite) NSString *division;
/**
 Contact work title
 */
@property (readwrite) NSString *workTitle;
/**
 Contact home address
 */
@property (readwrite) NSString *homeAddress;
/**
 Contact home city
 */
@property (readwrite) NSString *homeCity;
/**
 Contact home state
 */
@property (readwrite) NSString *homeState;
/**
 Contact home country
 */
@property (readwrite) NSString *homeCountry;
/**
 Contact birthdday
 */
@property (readwrite) NSDate *birthDay;
/**
 Contact picture
 */
@property (readwrite) UIImage *picture;
/**
 Contact color
 */
@property (readwrite) UIColor *color;

/**
 Remove all profile fields of certain type
 @param eType Type of profile fields to remove
 @result YES in case of success, NO otherwise
 @note In case of eAllOfflineFieldsModifiables only offline fields will be removed
 */
-(BOOL)removeAllPhoneEmails:(eProfileFieldType)eType;

/**
 Remove profile field of certain type at a position
 @param eType Type of profile field to remove
 @param pos Position to remove
 @result YES in case of success, NO otherwise
 @note In case of eAllOfflineFieldsModifiables only offline fields will be removed
 */
-(BOOL)removePhoneEmail:(eProfileFieldType)eType
               position:(NSUInteger)pos;

/**
 Update a profile field of certain type at a position
 @param eType Type of profile field to remove
 @param pos Position to remove
 @param destination New destination, phone number, email or end point address
 @param description Description of the destination
 @result YES in case of success, NO otherwise
 @note In case of eAllOfflineFieldsModifiables only offline fields will be updated
 */
-(BOOL)updatePhoneEmail:(eProfileFieldType)eType
               position:(NSUInteger)pos
                   dest:(NSString *)destination
                   desc:(eFieldDescription)description;

/**
 Add a profile field of certain type
 @param eType Type of profile field to add
 @param destination Destination, phone number, email or end point address
 @param description Description of the destination
 @result YES in case of success, NO otherwise
 @note In case of eAllOfflineFieldsModifiables it is added as offline field
 */
-(BOOL)addPhoneEmail:(eProfileFieldType)eType
                dest:(NSString *)destination
                desc:(eFieldDescription)description;

/**
 Get all phone numbers
 @result A array with all phone numbers
 */
@property (readonly) NSArray <SptProfileField*>*phoneNumbers;

/**
 Get all email address
 @result A array with all email address
 */
@property (readonly) NSArray <SptProfileField*>*emailAddresses;


@end


/**
 @class ISptContactData
 Contact data
 */
@interface ISptContactData : NSObject<SptContactBase>

/**
 @typedef eContactType
 Contact type

 @constant kSptContactTypeIM: IM contact
 @constant kSptContactTypeCollaborate: COLLABORATE Pro room contact
 @constant kSptContactTypeOffline: Offline contact, created by local user
 */
typedef NS_ENUM(NSUInteger, eContactType)
{
    kSptContactTypeIM,
    kSptContactTypeCollaborate,
    kSptContactTypeOffline
};

/**
 @typedef eContactPresence
 Contact presence state

 @constant kSptPresenceOffLine: Offline
 @constant kSptPresenceDND: Do not disturb
 @constant kSptPresenceAway: Away
 @constant kSptPresenceInvisible: Invisible
 @constant kSptPresenceAvailable: Available
 @constant kSptPresenceCollaborateCall: In COLLABORATE Pro call
 @constant kSptPresenceSpontaniaCall: In COLLABORATE Space call
 */
typedef NS_ENUM(NSUInteger, eContactPresence)
{
    kSptPresenceOffLine,
    kSptPresenceDND,
    kSptPresenceAway,
    kSptPresenceInvisible,
    kSptPresenceAvailable,
    kSptPresenceCollaborateCall,
    kSptPresenceSpontaniaCall
};

/**
 @typedef eContactFriendShip
 @brief Friendship state
 @constant kStpContactFriendShipUnknown: Unknown
 @constant kStpContactFriendShipFriends: Friends can see precense each other
 @constant kStpContactFriendShipPendingRemoteAnswer: Waiting for answering friendship request
 @constant kStpContactFriendShipPendingLocalAnswer: Waiting my answer to a friendship request
 @constant kStpContactFriendShipPendingBoth: ocal and remote user has ask for presence each other
 @constant kStpContactFriendShipSubcribed: Local user is subscrubed to remote user presence
 @constant kStpContactFriendShipSubcribedPending: Local user is subscrubed to remote user presence and has to answer remote user requet
 @constant kStpContactFriendShipRemoteSubcribed: Remote user is subscrubed to local user presence
 @constant kStpContactFriendShipRemotePendingSubcribed: Remote user is subscrubed to local user presence and has to answer local user request
 @constant kStpContactFriendShipRosterOnly: User is in roster but without presence subcription or request
 */
typedef NS_ENUM(NSUInteger, eContactFriendShip)
{
    kStpContactFriendShipUnknown,
    kStpContactFriendShipFriends,
    kStpContactFriendShipPendingRemoteAnswer,
    kStpContactFriendShipPendingLocalAnswer,
    kStpContactFriendShipPendingBoth,
    kStpContactFriendShipSubcribed,
    kStpContactFriendShipSubcribedPending,
    kStpContactFriendShipRemoteSubcribed,
    kStpContactFriendShipRemotePendingSubcribed,
    kStpContactFriendShipRosterOnly
};

/**
 Get the list of rooms that contact belong to

 @param eFilter Filter to apply
 @return An NSArray of ISptRoomData with the rooms
 */
-(NSArray *)roomsCollection:(eSptRoomFilter)eFilter;

/**
 * Contact ID
 */
@property (readonly) TSptIMContactID contactID;


/**
 Contact type
 */
@property (readonly) eContactType contactType;

/**
 * Presence state
 */
@property (readonly) eContactPresence state;


/**
 Can chat with this contact
 */
@property (readonly) BOOL canChat;

/**
 Can make an audio call to this contact
 */
@property (readonly) BOOL canAudioCall;

/**
 Can make a video call to this contact
 */
@property (readonly) BOOL canVideoCall;

/**
 Can invite to a meeting to this contact
 */
@property (readonly) BOOL canInviteMeeting;

/**
 Can add to channel this contact
 */
@property (readonly) BOOL canAddToChannel;

/**
 Can remove this contact
 */
@property (readonly) BOOL canRemove;

/**
 Friendship status
 */
@property (readonly) eContactFriendShip friendShip;

/**
 Message associated with the state
 */
@property (readonly) NSString *stateMessage;

/**
 Presence request message
 */
@property (readonly) NSString *presenceRequestMessage;
/**
 An NSArray of NSNumber with the group IDs that contact belongs to
 */
@property (readonly) NSArray *groupIDs;
/**
 Get one 2 one room, in case there isn't it returns nil
 */
@property (readonly) ISptRoomData *one2OneRoom;

/**
 Get favorite ID, in case it is not in the favority list it returns kSPT_INVALID_FAVORITE_ID
 */
@property (readonly) SptIMFavoriteID favoriteID;


/**
 Contact profile
 */
@property (readonly) ISptContactProfile *profile;

/**
 Modifiable profile
 */
@property (readonly) ISptModifyProfile *modifiableProfile;


/**
 There was changed in the contact data from the last resset

 @param bReset Reset changes flag
 @return YES in case there was changes since last time it was reset, NO otherwise
 */
-(BOOL)changed:(BOOL)bReset;

@end


/**
 @class SptInviteContactsByEmail
 Invite contact by email.
 Invited contact will be added to your contact directory
 */
@interface SptInviteContactsByEmail : NSObject

/**
 Create object

 @return created instance
 */
+(instancetype)sptInviteContactsByEmailWithOutData;

/**
 Add a contact to the list of contacts to invite

 @param email Email address
 @param contactName Contact name
 @param contactSurname Contact surname
 @return YES in case was successfully added to the liust of contacts to invite, NO otherwise
 */
-(BOOL)addContact:(NSString *)email
             name:(NSString *)contactName
          surname:(NSString *)contactSurname;
@end


/**
 @class ISptProfileFieldRoster
 Profile field with contact data
 */
@interface ISptProfileFieldRoster : SptProfileField<SptContactBase>

/**
 Is contact in the favorite list
 @result YES in case it is in the favorite list NO otherwise
 */
@property (readonly)  BOOL isFavorite;
@end

/*!
  ISpontaniaIMApi.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne. All rights reserved.
*/


#import <Foundation/Foundation.h>
#import "ISptIMContactExt.h"
#import "ISptIMGroupExt.h"
#import "ISptIMRoomExt.h"
#import "ISpontaniaIMApiDelegate.h"
#import "ISptObjectsExt.h"
#import "ISptSchMeetingsExt.h"
#import "ISptCallExt.h"
#import "ISptIMRoomExt.h"


@class SptRoomManageEntryCollection;

/*!
 License rights class interface
 */
@interface SptLicenseData : NSObject

/*!
 Get the maximum number of participants in a call/meeting
 */
@property (readonly) NSUInteger maxCallParticipants;

/*!
 Get the maximum number of call/meetings that can be started at the same time where you are host
 */
@property (readonly) NSUInteger maxSimultaneosHost;

/*!
 Get the maximun numbet of simultaneos outgoing calls to an endpoint
 */
@property (readonly) NSUInteger maxEndPointOutboundCalls;

/*!
 Get the maximun numbet of simultaneos incomming calls from endpoint or PSTN
 */
@property (readonly) NSUInteger maxEndPointInboundCalls;

/*!
 Can I record meetings and calls
 */
@property (readonly) BOOL canRecord;

/*!
 Can I create webinars
 */
@property (readonly) BOOL canCreateWebinar;

/*!
 Can I create classrooms
 */
@property (readonly) BOOL canCreateClassroom;

/*!
 Can I create meetings
 */
@property (readonly) BOOL canCreateMeetings;

/*!
 Can I create channels
 */
@property (readonly) BOOL canCreateChannels;

/*!
 Can I create chats
 */
@property (readonly) BOOL canCreateChats;

/*!
 Can I call this user
 */
@property (readonly) BOOL canCreateCall;

/*!
 Can I record meetings at server
 */
@property (readonly) BOOL canRecordAtServer;

@end


/*!
 @class SptGDPRData
 GDPR agreement data
 */
@interface SptGDPRData : NSObject

/**
 IS GDPR agreement data pending to accept
 */
@property (readonly) BOOL isPending;

/**
 Get GDPR agreement
 @param language Language in 2 letters code: EN, ES, RU... nil in case default language
 @result GDPR agreement data in case of found in the requested language, nil otherwise
 */
-(NSString *)getAgreement:(NSString *)language;
@end

/*!
 @class ISptConnectionData
 Connection data, legacy mode
 */
@interface ISptConnectionData : NSObject

/*!
 Create instance with data

 @param store YES in case connection data is stored in device after successfully login, false otherwise
 @param serverAddress Server address
 @param serviceName Service name
 @param userName User name (JID)
 @param password Password
 @return object
 */
+(instancetype)connectionDataWithData:(BOOL)store
                               server:(NSString*)serverAddress
                          serviceName:(NSString*)serviceName
                             userName:(NSString*)userName
                             password:(NSString*)password;

/*!
 Presence server
 */
@property (readwrite) NSString *_Server;
/*!
 Service name
 */
@property (readwrite) NSString *_ServiceName;

/*!
User name
 */
@property (readwrite) NSString *_Username;
/*!
 Password
 */
@property (readwrite) NSString *_Password;
/*!
 Port
 */
@property (readwrite) NSInteger _port;
/*!
 Store cretentiasl
 */
@property (readwrite) BOOL      _storeCredentials;
@end


/*!
 @class SptLoginData
 Login data
 */
@interface SptLoginData : NSObject
/*!
 Use this object to login into the syste,

 @param store Store cretendials in the device after a successfull login, YES in case of strore, No not store
 @param emailAddress Email address to login
 @param password Password
 @param serverAddr Web server address, set it to nil in case you connect with cloud server
 @return created object
 */
+(instancetype)loginDataWithData:(BOOL)store
                           email:(NSString*)emailAddress
                        password:(NSString*)password
                           sever:(NSString *)serverAddr;

/*!
 Server address, in case of nil it connectrs with the cloud server
 */
@property (readwrite) NSString *_Server;
/*!
 Email address
 */
@property (readwrite) NSString *_EmailAddr;
/*!
 Password
 */
@property (readwrite) NSString *_Password;
/*!
 Store credentials in the system
 */
@property (readwrite) BOOL      _storeCredentials;
@end


/*!
 Make call
 */
@interface SptMakeCallData : NSObject
/*!
 Create a make call object with type

 @param callTYpe Call type, how you will connect to the call
 @return created object
 */
+(instancetype)makeCallDataWithType:(eCallType)callTYpe;

/*!
 Add a contact6 from your conbtact directory

 @param contactID Contact ID of the contact to add
 @return true in case of success, false in case of error
 */
-(bool)addIMParticipant:(TSptIMContactID)contactID;


/*!
 Add an endpoint to the call

 @param eType Type of endpoint
 @param endpointNumber End point address
 @param contactID In case endpoint belongs to a known contact, set contact ID to associate participant with the contact
 @return true in case of success, false in case of error
 */
-(bool)addEndpointParticipant:(eEndPointType)eType
                       number:(NSString *)endpointNumber
                      contact:(TSptIMContactID)contactID;


/*!
 Get call ID. Call ID will be available after performing mke call action
 */
@property (readonly) SptCallID callID;

@end


/*!
 Add participants to a call
 */
@interface SptCallAddParticipants : NSObject
/*!
 Create object

 @param callID Call ID where you want to add participants
 @return Created object
 */
+(instancetype)callAddParticipantsWithCallID :(SptCallID)callID;

/*!
 Add a contact6 from your conbtact directory
 
 @param contactID Contact ID of the contact to add
 @return true in case of success, false in case of error
 */
-(bool)addIMParticipant:(TSptIMContactID)contactID;

/*!
 Add an endpoint to the call
 
 @param eType Type of endpoint
 @param endpointNumber End point address
 @param contactID In case endpoint belongs to a known contact, set contact ID to associate participant with the contact
 @return true in case of success, false in case of error
 */
-(bool)addEndpointParticipant:(eEndPointType)eType
                       number:(NSString *)endpointNumber
                      contact:(TSptIMContactID)contactID;

@end



/*!
 Report video sizes to the COLLABORATE Space SDK
 */
@interface SptCallVideoSizes : NSObject

/*!
 Create object used to report video sizes

 @param callID Call ID
 @return Created object
 */
+(instancetype)callVideoSizeWithCallID :(SptCallID)callID;

/*!
 Add stream paint size

 @param streamID Stream ID
 @param size Size in pixels that the stream has in the screen
 */
-(void)addVideo:(SptCallStreamDataID)streamID andSize:(CGSize)size;
@end


/*!
 @class SptSchMeetingCreate
 Create a meeting
 */
@interface SptSchMeetingCreate : NSObject

/*!
 Create a meeting now

 @param nsTitle Meeting title
 @param nsDescription Meeting description
 @return Created object
 */
+(instancetype)sptSchMeetingCreateNow:(NSString *)nsTitle
                                        desc:(NSString *)nsDescription;

/*!
 Create a not repeat meeting

 @param nsTitle Meeting title
 @param nsDescription Meeting description
 @return Created object
 */
+(instancetype)sptSchMeetingCreateOneDay:(NSString *)nsTitle
                                    desc:(NSString *)nsDescription;

/*!
 Created a weekly repeat meeting

 @param daysOfWeek Days of the week where meeting is going to repeat
 @param nsTitle Meeting title
 @param nsDescription Meeting description
 @return Created object
 */
+(instancetype)sptSchMeetingCreateRepeatWeekly:(MeetingRepeatWeekly)daysOfWeek
                                         title:(NSString *)nsTitle
                                          desc:(NSString *)nsDescription;

/*!
 Create a day of moth repeat meeting

 @param nsTitle Meeting title
 @param nsDescription Meeting description
 @return Created object
 */
+(instancetype)sptSchMeetingCreateRepeatDayOfMonth:(NSString *)nsTitle
                                              desc:(NSString *)nsDescription;

/*!
 Created a day of the week of the month repeat meeting

 @param daysOfWeek Days of the week where meeting is going to repeat
 @param weeks Weeks of the month where meeting is going to repeat
 @param nsTitle Meeting title
 @param nsDescription Meeting description
 @return Created object
 */
+(instancetype)sptSchMeetingCreateRepeatWeekOfMonth:(MeetingRepeatWeekly)daysOfWeek
                                        weekOdMonth:(MeetingRepeatMonthlyWeek)weeks
                                              title:(NSString *)nsTitle
                                               desc:(NSString *)nsDescription;


/*!
 Create meeting error

 - kSchCreateNoError: Create meeting no error
 - kSchCreateEError: Create meeting generic error
 - kSchCreateEType: Create meeting error: type of meeting
 - kSchCreateEDuration: Create meeting error: duration
 - kSchCreateEStartDate: Create meeting error: start date
 - kSchCreateEFinishDate: Create meeting error: end date
 - kSchCreateEDays: Create meeting error: days of week
 - kSchCreateEWeeks: Create meeting error: weeks of month
 - kSchCreateEParticipants: Create meeting error: participants
 - kSchCreateEProperties: Create meeting error: properties
 */
typedef NS_ENUM(NSUInteger, SptSchResult)
{
    kSchCreateNoError,
    kSchCreateEError,
    kSchCreateEType,
    kSchCreateEDuration,
    kSchCreateEStartDate,
    kSchCreateEFinishDate,
    kSchCreateEDays,
    kSchCreateEWeeks,
    kSchCreateEParticipants,
    kSchCreateEProperties
};


/*!
 Get create meeting error
 */
@property (readonly) SptSchResult error;
/*!
 Create meeting progress, a value for 0 till 100 with the creation progress
 */
@property (readonly) NSUInteger progress;

/*!
 Days of week to repeat meeting
 */
@property (readonly) MeetingRepeatWeekly repeatWeekly;
/*!
 Weeks of month to repeat meeting
 */
@property (readonly) MeetingRepeatMonthlyWeek repeatWeekofMonth;

/*!
 Set meeting properties

 @param properties Meetings properties
 @param nsPassword Meeting password, nil in case no password
 @return YES in case of success, NO otherwise
 */
-(BOOL)setProperties:(MeetingSequenceProperties)properties
            password:(NSString *)nsPassword;

/*!
 Set meeting dates and duration

 @param startDate Meeting start date
 @param endDate Meeting finish date, it must be set in case of repeat meeting
 @param ianaTimeZone IANA time zone of start and end date
 @param duration Meeting duration
 @return YES in case of success, NO otherwise
 */
-(BOOL)setDates:(NSDate *)startDate
  repeatEndDate:(NSDate *)endDate
       timeZone:(NSString*)ianaTimeZone
           time:(NSDateComponents*)duration;

/*!
 Add a contact from your contact dirrectory

 @param contactID Contact ID of the conatct to add
 @return YES in case of success, NO otherwise
 */
-(BOOL)addIMParticipant:(TSptIMContactID)contactID;

/*!
 Add a COLLABORATE Pro room to the meeting

 @param contactID Contact ID of the COLLABORATE Pro room to add
 @return YES in case of success, NO otherwise
 */
-(BOOL)addCollaborateRoom:(TSptIMContactID)contactID;

/*!
 Add a participant by email

 @param email Email address of the contact to add
 @return YES in case of success, NO otherwise
 */
-(BOOL)addEMailParticipant:(NSString *)email;

/*!
 Attach a file to the meeting. In case of repeat meeting it will be added to the first meeting

 @param filePath File path
 @return Fila ID in case of success
 */
-(SptFileID)addFile:(NSURL*)filePath;


/*!
 Attach a file to the meeting

 @param file File object to add
 @return Fila ID in case of success
 */
-(SptFileID)addSptFile:(SptFile*)file;


/*!
 Add an agenga dield to the meeting. In case of repeat meeting agenda is added to the first meeting

 @param agendaField Agenda field to add
 @return YES in case of success, NO otherwise
 */
-(BOOL)addToAgenda:(NSString *)agendaField;

@end



/*!
 @class ISpontaniaIMApi
 @brief COLLABORATE Space SDK main class
 */
@interface ISpontaniaIMApi : NSObject


/*!
 Connection state

 - kSptIMConnectionStateDisconnected: Disconnected
 - kSptIMConnectionStateConnecting: Connecting
 - kSptIMConnectionStateConnected: Connected
 - kSptIMConnectionStateDisconnecting: Disconnecting
 - kSptIMConnectionStateReconnecting: Reconnecting
 */
typedef NS_ENUM(NSUInteger, eSptConnectionState)
{
    kSptIMConnectionStateDisconnected,
    kSptIMConnectionStateConnecting,
    kSptIMConnectionStateConnected,
    kSptIMConnectionStateDisconnecting,
    kSptIMConnectionStateReconnecting
};


/*!
 Method result

 - kSptIMResultOk: success
 - kSptIMResultProcessig: Action is going to be done asynchronously
 - kSptIMResultError: Error performing action
 - kSptIMResultEParams: Error in params
 */
typedef NS_ENUM(NSUInteger, eSptResult)
{
    kSptIMResultOk,
    kSptIMResultProcessig,
    kSptIMResultError,
    kSptIMResultEParams,
    kSptIMResultERights,
    kSptIMResultELicense
};

/*!
 Create Spontania SDK with delegate

 @param delegate Inherit from ISpontaniaIMApiDelegate to receive COLLABORATE Space SDK notifications
 @return created instance
 */
+(instancetype)spontaniaIMApiWithDelegate:(id<ISpontaniaIMApiDelegate>)delegate;

/*!
 Get license data. You have to be connected to get this info.
 */
-(SptLicenseData *) getLicense;

/*!
 Are there credentials stored in the device

 @return YES in case there are credentials stored in the device, false otherwise
 */
-(BOOL) hasCredentials;


/*!
 Stored email address, in case there are credentials stoted in the device

 @return Stored email address, used for login
 */
-(NSString *)getStoredAccountEmail;

/*!
 Get GDPR data
 
 @return GDPR agreement data object
 */
-(SptGDPRData *)getGDPRData;

/*!
  Answer GDPR agreement
 
 @param accept YES in case accept GDPR agreement
 @return It returns an enumerate with the result
 */
-(eSptResult)answerGDPRAgreement:(BOOL)accept;

/*!
 Resolve token data
 
 @param token Token
 @param serverAddress Server address where resolve token
 @return It returns an enumerate with the result
 */
-(eSptResult)getTokenData:(NSString *)token
                   server:(NSString *)serverAddress;

/*!
 Login with token data result
 
 @param tokenDataResult Token data result object
 @return It returns an enumerate with the result
 */
-(eSptResult)loginWithTokenDataResult:(SptTokenDataResult *)tokenDataResult;

/*!
 Forget credentials stored in mobile
 
 @return It returns TRUE in case of success, FALSE otherwise
 */
-(BOOL) forgetCredentials;


/*!
 Create a new account. Yuo must be disconnected to call this method
 
 @param accountData Object with the account data
 @return It returns an enumerate with the result
 */
-(eSptResult) createAccount:(SptLoginData*)accountData;


/*!
 Recovery password
 
 @param email Email of the account to recover password
 @param serverAddr Server address. In case you are in the cloud account set it to nil
 @return It returns an enumerate with the result
 */
-(eSptResult) recoverPassword:(NSString*)email
                       server:(NSString*)serverAddr;


/*!
 Get cloud storage details
 
 @return It returns an object with the cloud storage details.
 @note You must be connected to get this info
 */
-(ISptCloudStorage*) getCloudStorageDetails;


/*!
 Get PSTN call credit
 
 @return It returns an object with the PSTN call credit data
 @note You must be connected to get this info
 */
-(ISptPSTNCallCredit*) getPSTNCallCredit;

/*!
 Get contact from his contact ID
 
 @param tContactID Contact ID of the contact to be retrieved
 @return It returns a ISptContactData with the contact data, nil in case not found
 */
-(ISptContactData *)getContactByID:(TSptIMContactID) tContactID;

/*!
 Get the list of contacts in your contact directory
 @return It returns a NSArray of ISptContactData objects with contacts in your local directory
 */
-(NSArray<ISptContactData *> *)getRosterContacts:(eContactFilterSort)eFilter;

/*!
 Get a collection with a cretain profile field of all the contact in your local contact
 
 @param type Field to retrieve
 @result A NSArray of ISptProfileFieldRoster with fields of required eProfileFieldType of all the contacts in your contact list
 */
-(NSArray<ISptProfileFieldRoster *> *)getContactsProfileFields:(eProfileFieldType)type;



/*!
 Get the list of COLLABORATE Space Pro rooms in your local directory

 @return An NSArray of ISptContactData objects with COLLABORATE Pro contacts in your local directory
 */
-(NSArray *)getCollaborateRooms;


/*!
 Get the list of contacts that can be invited to a meeting

 @param meetingSeqID Meeting ID to get the list of contacts, in case you are creating a meeting set kSPT_INVALID_MEETING_SEQUENCE_ID
 to retrieve all the contacts that can be invited to a meeting
 @param eFilter Bit combination with filter and sort contacts
 @return An NSArray of ISptContactData objects with invitable contacts
 */
-(NSArray *)getInvitableMeetingContacts:(SptMeetingSeqID) meetingSeqID
                                 filter:(eContactFilterSort)eFilter;


/*!
 Get the list of invitavble      rooms to a meeting

 @param meetingSeqID Meeting sequence ID to retrieve list
 @param eFilter Bit combination with filter and sort contacts
 @return NSArray of ISptContactData with COLLABORATE Pro rooms you can add, in case you are creating
         a meeting set kSPT_INVALID_MEETING_SEQUENCE_ID to retrieve all the COLLABORATE Pro rooms that can be invited to a meeting
 */
-(NSArray *)getInvitableMeetingCollaborateRooms:(SptMeetingSeqID)meetingSeqID
                                         filter:(eContactFilterSort)eFilter;


/*!
 Get invitable contacts to a room
 
 @param roomID Room ID where you want to get the invitable contacts, set it to
        kSPT_INVALID_IM_ROOM_ID in case you want to get all contacts.
 @param eFilter Bit combination with filter and sort contacts
 @return It returns an NSArray of ISptContactData
 */
-(NSArray *)getInvitableRoomContacts:(SptIMRoomID)roomID
                              filter:(eContactFilterSort)eFilter;

/*!
 Get group from his ID
 
 @param tGroupID Group ID to retrieve
 @return It returns a pointer to ISptGroupData, nil in case it doesn't exist.
 */
-(ISptGroupData *)getGroupByID:(SptIMGroupID) tGroupID;

/*!
 Get the collection of the groups
 
 @return It returns a NSArray of ISptGroupData with the list of groups
 */
-(NSArray *)getRosterGroups;


/*!
 Retrieve last search result
 
 @return It returns a SptSearchContacts object
 */
-(SptSearchContacts *)getLastSearchResult;

/*!
 Retrieve last search channel result
 
 @return It returns a SptSearchChannels object
 */
-(SptSearchChannels *)getLastChannelSearchResult;

/*!
 Get the list of contacts with pending presence request
 
 @return It returns a NSArray of ISptContactData with pending presence request
 */
-(NSArray *)getPendigPresenceRequest;

/*!
 Get the list of rooms.
 
 @param eFilter Filter to apply
 @return It returns a NSArray of ISptRoomData objects with the list of room applying filter.
 */
-(NSArray *)getRooms:(eSptRoomFilter)eFilter;

/*!
 Get the list of channels where I can inviate a contact
 
 @param contactID contact to be invited
 @return It returns a sorted by favorite and name NSArray of SptIMRoom
 */
-(NSArray *)getInvitableChannels:(TSptIMContactID)contactID;


/*!
 Get room by ID
 
 @param roomID Room ID to retrieve
 @return It returns an ISptRoomData object with the room data, nil in case room not found
 */
-(ISptRoomData *)getRoomByID:(SptIMRoomID)roomID;

/*!
 Get a one to one room from contact ID
 
 @param tContactID Contact ID to retrieve one to one room
 @return It returns a ISptRoomData object with the room data, nil in case there is not room created.
 */
-(ISptRoomData *)getOne2OneRoomByContactID:(TSptIMContactID) tContactID;


/*!
 Get room from the room ID received in the push notification

 @param pushPrivData room ID received in the push notification
 @return Room object in case of room found, nil in case room not found
 */
-(ISptRoomData *)getRoomFromPushNotification:(NSString *)pushPrivData;


/*!
 Set connection data
 
 @param connectionData Object with connection data, pass is to NULL in case you want to connect with stored credentials
 @return It returns an enumerate with the result
 */
-(eSptResult)setConnectionData:(ISptConnectionData *)connectionData;


/*!
 Set login dara
 
 @param loginData Object with login data,
 @return It returns an enumerate with the result
 */
-(eSptResult)setLoginData:(SptLoginData *)loginData;

/*!
 Connect to the server
 
 @return It returns an enumerate with the result
 */
-(eSptResult)connect;

/*!
 Disconnect from the server
 
 @return It returns an enumerate with the result
 */
-(eSptResult)disconnect;

/*!
 Set local user presence
 
 @param presence PResence to be set
 @param presenceMessage Presence message
 @return It returns an enumerate with the result
 */
-(eSptResult)setPresence:(eContactPresence)presence
               stateText:(NSString *)presenceMessage;

/*!
 Create a group
 
 @param groupName Name of the group to create
 @param contactList NSArray of NSNumbers with the contact IDs to add to the group
 @return It returns an enumerate with the result
 */
-(eSptResult)createGroup:(NSString *)groupName
                contacts:(NSArray *)contactList;


/*!
 Remove a group
 
 @param groupID Group ID to be removed
 @return It returns an enumerate with the result
 */
-(eSptResult)removeGroup:(SptIMGroupID)groupID;

/*!
 Add a contact to a group
 
 @param contactID Contact ID to be added
 @param groupID Group ID where contact will be added
 @return It returns an enumerate with the result
 */
-(eSptResult)addContactToGroup:(TSptIMContactID)contactID
                         group:(SptIMGroupID)groupID;

/*!
 Remove a contact from a group
 
 @param contactID Contact ID to be removed
 @param groupID Group ID where contact will be removed
 @return It returns an enumerate with the result
 */
-(eSptResult)removeContactToGroup:(TSptIMContactID)contactID
                         group:(SptIMGroupID)groupID;

/*!
 Ask for friendship
 
 @param contactID Contact ID of the contact to ask for friendship
 @return It returns an enumerate with the result
 */
-(eSptResult)askForFriendShip:(TSptIMContactID)contactID;

/*!
 Answer a friendship request
 
 @param contactID Contact ID of the user who requesr friendship
 @param bAccept YES in case accept friendship, NO in case reject
 @return It returns an enumerate with the result
 */
-(eSptResult)answerFrienship:(TSptIMContactID)contactID
                      accept:(BOOL)bAccept;


/*!
 Remove a contact from local user roster
 
 @param contactID Contact ID of the contact to be removed
 @return It returns an enumerate with the result
 */
-(eSptResult)removeContact:(TSptIMContactID)contactID;

/*!
 Search for new contacts at server directory
 
 @param search String to look for.
 @return It returns an enumerate with the result
 */
-(eSptResult)searchContacts:(SptSearchContacts *)search;

/*!
 Get local user vCard
 
 @return It returns an object with local user vCard
 */
-(ISptModifyProfile *)getLocalUserProfile;

/*!
 Set local user vCard or stores private information for a given remote user
 
 @param vCard vCard object to be set
 @return It returns an enumerate with the result
 */
-(eSptResult)setContactProfile:(ISptModifyProfile *)vCard;


/**
 * Get an object to create an offline contact
 * @return It returns an ISpModifyProfile object
 */
-(ISptModifyProfile *)createISptModifiableProfile;


/*!
 Create offline contact
 
 It creates a contact in the local user directory with a phone number, email or endpoint address
 @param contact Profile of the contact to create
 @return IIt returns an ISpModifyProfile object
 */
-(eSptResult)createOfflineContact:(ISptModifyProfile *)contact;

/*!
 Create an one to one room
 
 @param tContactID ContactID to create the room
 @return It returns the room ID of the room that is going to be created
 */
-(SptIMRoomID)createRoomOne2One:(TSptIMContactID)tContactID;


/*!
 Create a multi user room
 
 @param participantIDs NSArray with NSNumbers with the contact IDs of the contacts to add
 @return It returns an enumerate with the result
 */
-(SptIMRoomID)createRoom:(NSArray *)participantIDs;


/*!
 Join to a public room.
 
 @param roomID Room Id of the room you want to join.
 @return It returns an enumerate with the result
 */
-(eSptResult)joinPublicChannel:(SptIMRoomID) roomID;

/*!
 Leave a room
 
 @param roomID Room ID of the room to leave
 @return It returns an enumerate with the result
 */
-(eSptResult)leaveRoom:(SptIMRoomID)roomID;

/*!
 Add contacts to an existing MUC room
 
 @param roomID Room ID wehere contacts will be added
 @param participantIDs NSArray with NSNumbers with the contact IDs of the contacts to add
 @return It returns an enumerate with the result
 */
-(eSptResult)addContactsToRoom:(SptIMRoomID)roomID
                  participants:(NSArray *)participantIDs;


/*!
 Block a contact in a channel. Chack canIBlockParticipants in the channecl to check you
 have rights to call this method
 
 @param roomID room ID
 @param contactID contact ID to be blocked
 @return It returns an enumerate with the result
 */
-(eSptResult)blockContactInRoom:(SptIMRoomID)roomID
                        conatct:(TSptIMContactID)contactID;

/*!
 Promote one 2 one room to multiuser chat room. A new room is created with the participant of the one 2 one room
 
 @param roomID One 2 one room ID
 @param participantIDs NSArray of participants IDs
 @return It returns the new room ID
 */
-(SptIMRoomID)promoteOne2OneRoom2Muc:(SptIMRoomID) roomID
                        participants:(NSArray *)participantIDs;

/*!
 Send a text message to a room
 
 @param roomID Room ID wehere message will be sent
 @param textMessage Message to send
 @return It returns an enumerate with the result
 */
-(eSptResult)sendMessage:(SptIMRoomID)roomID
                 message:(NSString *)textMessage;


/*!
 Send a private test message in a room
 
 @param roomID Room ID wehere message will be sent
 @param textMessage Message to send
 @param contactIDs NSArray of NSNumbers with the addressed contacts IDs, they must belong to the chat room
 @return It returns an enumerate with the result
 */
-(eSptResult)sendMessagePrivate:(SptIMRoomID)roomID
                        message:(NSString *)textMessage
                      addressed:(NSArray*)contactIDs;


/*!
 Send a file to a room
 
 @param roomID Room ID wehere message will be sent
 @param fileFullPath Full path of the file to send
 @param textMessage Message to send
 @return It returns an enumerate with the result
 */
-(eSptResult)sendFile:(SptIMRoomID)roomID
             filePath:(NSURL *)fileFullPath
              message:(NSString*)textMessage;


/*!
 Do I have the right to remove a file

 @param fileID File ID to check
 @return YES in case you have the right, false otherwise
 */
-(BOOL)canIRemoveFile:(SptFileID)fileID;


/*!
 Remove an event in a room

 @param roomID Room ID where is the event to remove
 @param eventID Event ID to remove
 @return It returns an enumerate with the result
 */
-(eSptResult)removeEvent:(SptIMRoomID) roomID
                   rvent:(SptIMEventID) eventID;

/*!
 Remove a event file in a room

 @param fileID File ID
 @return It returns an enumerate with the result
 */
-(eSptResult)removeEventFile:(SptFileID) fileID;


/*!
 Notify to the COLLABORATE Space SDK that you have started to write in a chat room

 @param roomID Room ID of the room where you have started to write
 @param startWriting YES in case start to write, false in case stop writing
 @return An enumerate with the result
 */
-(eSptResult)notifyWritingInRoom:(SptIMRoomID)roomID
             writing:(BOOL)startWriting;



/*!
 Update room notes

 @param updateNotes Object with the notes to update
 @return An enumerate with the result
 */
-(eSptResult)updateRoomNotes:(SptRoomManageEntryCollection *)updateNotes;

/*!
 Send a file to a room
 
 @param roomID Room ID wehere message will be sent
 @param fileFullPath Full path of the file to send (original path)
 @param nsData Data to be sent
 @param textMessage Message to send
 @return An enumerate with the result
 */
-(eSptResult)sendPicture:(SptIMRoomID)roomID
                filePath:(NSURL *)fileFullPath
                    data:(NSData *)nsData
                 message:(NSString*)textMessage;


/*!
 @brief Create a Channel
 
 Call this method when you want to create a new channel.
 @param participantIDs NSArray with NSNumbers with the contact IDs of the contacts to add
 @param channelName Display name of the channel
 @param channelDescription Channel description
 @param publicChannel YES in case public channel, NO private channel
 @param channelImage Image of the channel
 @return Room ID that is going to be created
 */
-(SptIMRoomID)createChannel:(NSArray *)participantIDs
                       name:(NSString *)channelName
                description:(NSString *)channelDescription
                     public:(BOOL)publicChannel
                    picture:(UIImage *)channelImage;


/*!
 @brief Set channel data. Call this method to change channel title, description or picture

 @param channelData Object with the channel data to set
 @return An enumerate with the result.
 */
-(eSptResult)setChannelData:(ISptChannelData *)channelData;


/*!
 Load more events in memory in a room.
 Not all the events are loaded in memory in a room, in case you want to navigate through the
 chat history you have to call this method in roder to load the history

 @param roomID Room ID
 @return An enumerate with the result
 */
-(eSptResult)loadMoreRoomEvents:(SptIMRoomID)roomID;


/*!
 Search in all messages in the application
 
 @param searchEvent Search object
 @return An enumerate with the result
 */
-(eSptResult)searchEvents:(SptSearchEvents *)searchEvent;

/*!
 After searching for events, in case you want to load chat history till an event found
 in the search call this method.
 
 Tipically this is used when you present the seach result in the screen and the user clicks on a
 message, in order to show the message in the chat you have to load the chat history till the message.

 @param searchedEvent Searched message to load chat history
 @return An enumerate with the result
 */
-(eSptResult)loadEventsFromSearch:(SptSearchedEventData*)searchedEvent;


/*!
 Add a contact to favorite list
 
 @param contactID ID of the contact to add
 @return An enumerate with the result
 */
-(eSptResult)addContactToFavorites:(TSptIMContactID)contactID;


/*!
 Add a channel to favorite list
 
 @param roomID ID of the channel/chat to add
 @return An enumerate with the result
 */
-(eSptResult)addChannelToFavorites:(SptIMRoomID)roomID;

/*!
 Search for public channesls
 
 @param searchChannel Search object, In case you want to get more results over
        a previous search, pass again the same search object
 @return An enumerate with the result
 */
-(eSptResult)searchPublicChannels:(SptSearchChannels *)searchChannel;

/*!
 Add a channel to favorite list
 
 @param meetingSeqID ID of the meeting to add
 @return An enumerate with the result
 */
-(eSptResult)addMeetingSequenceToFavorites:(SptMeetingSeqID)meetingSeqID;


/*!
 Remove from favorites
 
 @param favoriteID favorite ID to be removed
 @return An enumerate with the result
 */
-(eSptResult)removeFromFavorites:(SptIMFavoriteID)favoriteID;


/*!
 Register to receive push notifications

 @param nsPushNotification Token to receive messages push notifications
 @param nsPushVoIPNotification Token to receeive calls push notifications
 */
-(void)registerPushNotifications:(NSString *)nsPushNotification
                            voip:(NSString *)nsPushVoIPNotification;


/*!
 Favorite filter

 - kSptIMFavoriteAll: Retrieve all favorites
 - kSptIMFavoriteContact: Retrieve contacts in the favorite list
 - kSptIMFavoriteRooms: Retrieve rooms in the favorite list
 - kSptIMFavoriteMeetings: Retrieve meetings in the favorite list
 */
typedef NS_ENUM(NSUInteger, eSptFavoriteFilter)
{
        kSptIMFavoriteAll,
        kSptIMFavoriteContact,
        kSptIMFavoriteRooms,
        kSptIMFavoriteMeetings
};

/*!
 Get favorites

 @param eFilter Filter to applay
 @return An NSArray of ISptFavoriteData with the requested favorites
 */
-(NSArray *)getFavorites:(eSptFavoriteFilter)eFilter;


/*!
 * Connection state
 */
@property (readonly) eSptConnectionState connectionState;

/*!
 * Search available
 */
@property (readonly) BOOL searchAvailable;

/*!
 Local profile required. YES is profile is not set for logged user
 */
@property (readonly) BOOL localProfileRequired;


/*!
 Get call phone rate
 
 @param phoneNumber Phone number to retrieve the cost in E.164 format
 @return An enumerate with the result
 */
-(eSptResult)getPhoneRate:(NSString *)phoneNumber;

/*!
 Get call phone rate for all the phone number of a contact
 
 @param contactID Contact ID to retrieve the phone rate
 @return An enumerate with the result
 */
-(eSptResult)getContactPhoneRate:(TSptIMContactID) contactID;

/*!
 Can I make calls
 
 @return YES in case you can make calls, false otherwise
 */
@property (readonly) BOOL canIMakeCalls;

/*!
 Get call data from call ID
 
 @param callID Call ID to get call dara
 @return A call data object in case of success, nil in case not found
 */
-(ISptCall*)getActiveCallByID:(SptCallID)callID;

/*!
 Get call data from call Identifier
 
 @param callIdentifier Call identifier
 @return A call data object in case of success, nil in case not found
 */
-(ISptCall*)getActiveCallByCallIdentifier:(NSString *)callIdentifier;


/*!
 Get the list of devices present in the device

 @param type Type of device to retrieve
 @return An NSArray of SptDeviceData with the list of available devices
 */
-(NSArray *)getDevices:(SptDeviceType)type;


/*!
 Get a device from its ID

 @param tDeviceID Device ID
 @return Device data in case of found, nil in case not found
 */
-(SptDeviceData *)getDeviceByID:(SptDeviceID)tDeviceID;

/*!
 Get current microphone device used in calls/meetings
 */
@property (readonly) SptDeviceData *currentMicDevice;


/*!
 Get current speaker device used in calls/meetings
 */
@property (readonly) SptDeviceData *currentSpkDevice;


/*!
 Get current camera device used in calls/meetings
 */
@property (readonly) SptDeviceData *currentVideoDevice;


/*!
 Set camera device to be used in calls/meetings

 @param deviceID Device unique ID
 @return An enumerate with the result
 */
-(eSptResult)setVideoDevice:(SptDeviceID)deviceID;


/*!
 Set audio devices to be used in calls/meetings

 @param micDeviceID Microphone unique device ID
 @param spkDeviceID Speaker unique device ID
 @return An enumerate with the result
 */
-(eSptResult)setAudioDevices:(SptDeviceID)micDeviceID
                     speaker:(SptDeviceID)spkDeviceID;

/*!
 Mute/unmute speaker
 
 @param mute YES to mute NO unmute
 @return It returns an enumerate with the result
 @note To set mute state you must be connected to a call/meeting and it only applies to the current call
 */
-(eSptResult)muteSpeaker:(BOOL)mute;


/*!
 Set speaker render route
 
 @param deviceID Speaker device ID
 @param eRenderRoute render route to set
 @return It returns an enumerate with the result
 @note When call/meeting finishes, render route is automatically set to speaker.
 */
-(eSptResult)setSpeakerRenderRoute:(SptDeviceID)deviceID
                       renderRoute:(SptAudioDeviceRenderRoute)eRenderRoute;


/*!
 Join to a meeting
 
 @param joinMeeting Object with the meeting data to join
 @return It returns the call ID in case of success, or kSPT_INVALID_CALLID in case of error
 */
-(SptCallID)joinMeeting:(ISptJoinMeetingData *)joinMeeting;

/*!
 Hang up a call
 
 @param callID Call ID
 @return An enumerate with the result
 */
-(eSptResult)hangUpCall:(SptCallID)callID;


/*!
 End a call for all participants.

 @param callID Call ID of the call to finish
 @return An enumerate with the result
 */
-(eSptResult)endCallForAll:(SptCallID)callID;

/*!
 Hang a call participant

 @param callID Call ID
 @param participantID Call participant ID to be hung
 @return An enumerate with the result
 @note check the right to hang a participant calling
 */
-(eSptResult)hangCallParticipant:(SptCallID)callID
                     participant:(SptCallParticipantID)participantID;


/*!
 Set call service state for you or other participant

 @param callID Call ID
 @param participantID Participant ID that you want to set the service state
 @param service Service to set
 @param active YES in case active service, NO in case deactive
 @return An enumerate with the result
 */
-(eSptResult)setCallServiceState:(SptCallID)callID
                     participant:(SptCallParticipantID)participantID
                         serviceID:(eCallService)service
                          enable:(BOOL)active;



/*!
 Make a call

 @param makeCallData Make call object with the call details
 @return An enumerate with the result
 */
-(eSptResult)makeCall:(SptMakeCallData *)makeCallData;


/*!
 Make a call over a chat/channel

 @param eType Type of call, how you are going to connect to the call, with video active or onluy with audio
 @param roomID Room ID where you want to start the call
 @return In case of success it returns the call ID, kSPT_INVALID_CALL_ID in case of error
 */
-(SptCallID)makeRoomCall:(eCallType)eType
                     room:(SptIMRoomID)roomID;


/*!
 Reapeat a call from a call history.

 @param eType Type of call, how you are going to connect to the call, with video on or off
 @param callID Call history ID.
 @return In case of success it returns the call ID, kSPT_INVALID_CALL_ID in case of error
 */
-(SptCallID)makeCallHistoryCall:(eCallType)eType
                           callHistoryID:(SptCallID)callID;

/*!
 Accept an incomming call
 
 @param callID Call ID of the call to answer
 @param bVideoOn true in case of answer with video, false to answer with audio only
 @return An enumerate with the result
 */
-(eSptResult)acceptCall:(SptCallID)callID
                videoOn:(bool)bVideoOn;

/*!
 Decline an incoming call
 
 @param callID Call ID of the call to decline
 @return An enumerate with the result
 */
-(eSptResult)rejectCall:(SptCallID)callID;


/*!
 Add participants to a call

 @param participants Objuect with the participants to add
 @return An enumerate with the result
 */
-(eSptResult)addParticipantsToCall:(SptCallAddParticipants *)participants;


/*!
 Report to COLLABORATE Space SDK the size of the streams in the screen.
 It is usefull to receive the quality of the streams according to the size that is being painted.

 @param callID Call ID
 @param videoListSizes Object with the size of the streams on the screen
 @return An enumerate with the result
 */
-(eSptResult)reportVideoPaintSize:(SptCallID)callID videoListSizes:(SptCallVideoSizes*)videoListSizes;

/*!
 Pass moderation role to other participant

 @param callID Call ID
 @param participantID Participant ID that is going to receive moderation role
 @return An enumerate with the result
 */
-(eSptResult)promoteToModerator:(SptCallID)callID
                    participant:(SptCallParticipantID)participantID;


/*!
 Start/stop meeting recording
 
 @param callID Call ID
 @param bStart true in case start recording, fase in case stop
 @return An enumerate with the result
 @note It starts/stops recording at server
 */
-(eSptResult)recordCall:(SptCallID)callID
                  start:(BOOL) bStart;

/*!
 Answer a pending call request

 @param callRequest Call request object to answer
 @param bAccept YES in case accept call request, NO in case decline
 @return An enumerate with the result
 */
-(eSptResult)answerCallRequest:(SptCallRequest*)callRequest
                        accept:(bool)bAccept;


 /*!
  Send a private message in a call chat

  @param callID Call ID
  @param message Body of the message to send
  @param addressedIDs NSArray with the addressed participant IDs
  @return An enumerate with the result
  */
 -(eSptResult)sendCallChatPrivateMessage:(SptCallID)callID
                                     chat:(NSString *)message
                                     addressed:(NSArray *)addressedIDs;

/*!
 Send a public message in a call char

 @param callID Call ID
 @param message Body of the message to send
 @return An enumerate with the result
 */
-(eSptResult)sendCallChatPublicMessage:(SptCallID)callID
                                   chat:(NSString *)message;


/*!
 Start sharing a view

 @param callID Call ID wehre view is going to be shared
 @param view View to share
 @return An enumerate with the result
 */
-(eSptResult)startSahringView:(SptCallID)callID
                   sharedVide:(UIView *)view;


/*!
 Create a file object

 @param fileURL File url
 @return Created file object, nil in case error
 */
-(SptFile *)createSptFile:(NSURL *)fileURL;


/*!
 Schedule a new meeting

 @param meeting Meeting yo create
 @return An enumerate with the result
 */
-(eSptResult)scheduleMeeting:(SptSchMeetingCreate *)meeting;


/*!
 Get an NSArray with all meeting sequences

 @return An NSArray with all meeting sequences
 */
-(NSArray<SptSchMeetingSequence *> *)getMeetigsSequences;


/*!
 Get a meeting sequence data by its ID

 @param seqID Meeting sequence ID
 @return Meeting sequence data in case of found, nil in case not found
 */
-(SptSchMeetingSequence *)getSchMeetingSequenceByID:(SptMeetingSeqID)seqID;

/*!
 Set you attend state in a meeting sequence

 @param seqID Meeting sequence ID where you are going to set your attend state
 @param attentState Attend state to set
 @return An enumerate with the result
 */
-(eSptResult)setShcMeetingAttendState:(SptMeetingSeqID)seqID
                             attState:(SptSchPartState)attentState;


/*!
 Manage meeting sequence participants
 You have to have rigths to call this method. You can add and remove participants in a meeting sequence

 @param newParticipants Participanrs to add and remove
 @return An enumerate with the result
 */
-(eSptResult)manageSchMeetingParticipants:(SptSchManageParticipants *)newParticipants;


/*!
 Update meeting summary, notes or agenda.
 You can add, remove and modify notes and agenda

 @param summaryChanges Object with modifications
 @return An enumerate with the result
 */
-(eSptResult)updateMeetingSummary:(SptSchManageEntryCollection *)summaryChanges;


/*!
 Change meeting sequence properties.
 You have to have rights to call this method

 @param newProperties Object with the properties to set
 @return An enumerate with the result
 */
-(eSptResult)manageSchMeetingProperties:(SptSchManageProperties*)newProperties;

/*!
 Manage meeting files.
 Check your rigths in order to know what operations can you make.

 @param manageFiles Object with the file changes, Added files and/or remove files
 @return An enumerate with the result
 */
-(eSptResult)manageSchMeetingFiles:(SptSchManageFiles*)manageFiles;

/*!
 Finish a meeting that is in active state.
 You need rights to call this method

 @param seqID Meeting sequence ID
 @param meetingID Meeting ID to finish
 @return An enumerate with the result
 */
-(eSptResult)finishMeeting:(SptMeetingSeqID)seqID
                   meeting:(SptMeetingID)meetingID;

/*!
 Cancel meeting

 @param seqID Meeting sequence ID
 @param meetingID Meeting ID
 @return An enumerate with the result
 */
-(eSptResult)cancelMeeting:(SptMeetingSeqID)seqID
                   meeting:(SptMeetingID)meetingID;

/*!
 Cancel all pending meetings in a meeting sequence

 @param seqID Meeting sequence ID
 @return An enumerate with the result
 */
-(eSptResult)cancelMeetingSequence:(SptMeetingSeqID)seqID;



/*!
 Change the date and duration of a meeting
 
 @param seqID Meeting sequence ID
 @param meetingID Meeting ID
 @param startDate New start date
 @param ianaTimeZone Time zone in IANA format, in case of nil local time zone is set
 @param duration New duration
 @return An enumerate with the result
 @note In case of meeting sequence with more than one meeting, meeting can not overlaped other meeting inside the
 sequence and cannot be later than next meeting or earlier than previous meeting
 */
-(eSptResult)changeMeetingDateDuration:(SptMeetingSeqID)seqID
                               meeting:(SptMeetingID)meetingID
                                 start:(NSDate *)startDate
                              timeZone:(NSString*)ianaTimeZone
                                  time:(NSDateComponents*)duration;


/*!
 Change the title of a meeting sequence
 
 @param seqID Sequence ID
 @param title New title to set
 @return An enumerate with the result
 @note You need rigths in order to change the meeting title
 */
-(eSptResult)changeMeetingTile:(SptMeetingSeqID)seqID
                      newTitle:(NSString *)title;

/*!
 Join to a meeting.
 Meeting have to be in active state in order to join.

 @param seqID Meeting sequence ID
 @param meetingID Meeting ID
 @param videoON Join with video in case of YES, video off in case of NO
 @return Call ID assigned to the call. kSPT_INVALID_CALL_ID in case of error
 */
-(SptCallID)joinSchMeeting:(SptMeetingSeqID)seqID
                    meeting:(SptMeetingID)meetingID
                    videoON:(BOOL)videoON;


/*!
 Download a file

 @param fileID File ID of the file to download
 @return An enumerate with the result
 */
-(eSptResult)downloadFile:(SptFileID)fileID;


/*!
 Get call history

 @return Call history
 */
-(SptCallHistoryCollection *)getCallHistoryCollection;


/*!
 Load more calls in the call history

 @return An enumerate with the result
 */
-(eSptResult)callHistoryLoadMore;


/*!
 Invite new contacts by email

 @param contactList Object with the contacts to invide
 @return An enumerate with the result
 */
-(eSptResult)inviteContactsByEmail:(SptInviteContactsByEmail *)contactList;



/*!
 Update ToDos, in a meeting, chat, channel or personal ToDos

 @param updateToDos Object with the updated ToDos
 @return An enumerate with the result
 */
-(eSptResult)updateToDos:(SptModifyToDoCollection *)updateToDos;


/*!
 Get personal ToDos

 @return An NSArray of SptToDo with all personal ToDos
 */
-(NSArray *)getPersonalToDos;
    
    

/*!
 Get file object by its ID

 @param fileID File ID to retrieve
 @return File data in case of success, nil in case not found
 */
-(SptFile*)getFileByID:(SptFileID)fileID;

/*!
 Get a collection with all files in chats, channels and meetings

 @return A collection with all files
 */
-(SptFileCollection *)getAllFiles;


/*!
 Search files

 @param searchPattern Pattern to search files in the file name
 @return A file collection with the found files
 @note This method can take time, don't call it from the UI thread
 */
-(SptFileCollection *)serachFiles:(NSString *)searchPattern;


/*!
 Get normalized name

 @param toNormalize String to normalize
 @return Normalized string
 */
+(NSString *)getNormalizedString:(NSString *)toNormalize;

/*!
 Sends DTMF codes to a call participant
 
 @param callID String to normalize
 @param participantID Destination participant ID
 @param dtmf One or more DTMF charecter
 @return An enumerate with the result
 */
-(eSptResult)sendDMTFStringToParticipant:(SptCallID)callID participantID:(SptCallParticipantID)participantID dmtf:(NSString *)dtmf;

/*!
 Accepts a call also if the api is not connected or has not received the incomming call event yet
 
 @param identifier  The global identifier of the call
 @param accept     Whatever the call should be accepted or not
 @param bVideoOn     Enter with audio/video
 @return An enumerate with the result
 */
-(eSptResult)acceptCallFromIdentifier:(NSString*)identifier accept:(BOOL)accept videoOn:(bool)bVideoOn;


/*!
 if the user can manually change the password
 */
@property (readonly) BOOL canIChangePassword;

/*!
 Change the user password
 
 @param oldPassword Current password to validate first
 @param newPassword  New password to set
 @return An enumerate with the result
 */
-(eSptResult)changePassword:(NSString*)oldPassword newPassword:(NSString*)newPassword;

/*!
 * In case of connection error, call this method to get the specific error
 * It returns the specific connetion error.
 */
@property (readonly) eSptConnectionResult lastConnectionError;

@end



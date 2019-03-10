/**
  ISpontaniaIMApiDelegate.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import "ISptIMContactExt.h"
#import "ISptIMGroupExt.h"
#import "ISptIMRoomExt.h"
#import "ISptCallExt.h"
#import "ISptObjectsExt.h"
#import "ISptDevices.h"
#import "ISptSchMeetingsExt.h"

@class SptSchMeetingCreate;


/**
 @class SptSearchContacts
 Search contact at server directory
 */
@interface SptSearchContacts : NSObject
/**
 Create instance

 @param searchText Pattern to search for contacts
 @return created instance
 */
+(instancetype)searchContactsWithString:(NSString *) searchText;
/**
 Total number of contacts found at the server
 */
@property (readonly) NSUInteger totalFound;
/**
 Current number of retrieved contactsa
 */
@property (readonly) NSUInteger retrievedContacts;
/**
 An NSArray of ISptContactData with the contacts currently retrieved
 */
@property (readonly) NSArray *contactsFound;
/**
 Search pattern
 */
@property (readonly) NSString *searchText;
/**
 Is there a search in progress
 */
@property (readonly) BOOL inProgess;
@end

/**
 Search for public channels at server directory
 */
@interface SptSearchChannels : NSObject

/**
 Create instance

 @param searchText Search pattern
 @return created instance
 */
+(instancetype)searchChannelsWithString:(NSString *) searchText;

/**
 Total number of public channels found at the server
 */
@property (readonly) NSUInteger totalFound;

/**
 Currently retrieved channels number
 */
@property (readonly) NSUInteger retrievedChannels;

/**
 An NSArray of ISptRoomData with the retrieved channels
 */
@property (readonly) NSArray *channelsFound;

/**
 Search pattern
 */
@property (readonly) NSString *searchText;

/**
 Is search currently in progress
 */
@property (readonly) BOOL inProgess;

@end


/******************************************************************************/

/**
 @class SptContactPhoneRateResult
 Contact phone rate result
 */
@interface SptContactPhoneRateResult : NSObject

/**
 Contact ID
 */
@property (readonly)    TSptIMContactID contactID;

/**
 Get call phone rate
 
 @param phoneNumber Phone number to retrieve the call rate
 @result Call rate in $/min
 */
-(NSString *)getPhoneRate:(NSString *)phoneNumber;

@end

/******************************************************************************/

/**
 @class SptTokenDataResult
 
 Token data result
 */
@interface SptTokenDataResult : NSObject

/**
 Token data result
 
 - kSptTokenDataResultLogin: It is a login token
 - kSptTokenDataResultJoinMeeting: It is a meeting token
 - kSptTokenDataResultError: Generic error
 - kSptTokenDataResultServerNotReachable: Server not reachabel
 - kSptTokenDataResultInvalidToken: Token is invalid
 */
    typedef NS_ENUM(NSUInteger, eSptTokenDataRes)
    {
        kSptTokenDataResultLogin,
        kSptTokenDataResultJoinMeeting,
        kSptTokenDataResultError,
        kSptTokenDataResultServerNotReachable,
        kSptTokenDataResultInvalidToken,
    };

/**
 Token data result
 */
@property (readonly) eSptTokenDataRes result;

/**
 You are already logged with the user associated to the token
 */
@property (readonly) BOOL contactAlreadyLogged;

/**
 In case of meeting token, get meeting sequence ID
 */
@property (readonly) SptMeetingSeqID meetingSequenceID;

/**
 Get token
 */
@property (readonly) NSString *token;

/**
 Get server where token was resolved
 */
@property (readonly) NSString *server;
@end



/*!
 Change password result
 
 - kSptIMChangePasswordResOK: success
 - kSptIMChangePasswordResError: Generic error
 - kSptIMChangePasswordResInvalidCurrentPassword: Current password does not match
 - kSptIMChangePasswordResInvalidNewPassword: New password does not fit the password rules
 */
typedef NS_ENUM(NSUInteger, eSptChangePasswordResult)
{
    kSptIMChangePasswordResOK = 0,
    kSptIMChangePasswordResError,
    kSptIMChangePasswordResInvalidCurrentPassword,
    kSptIMChangePasswordResInvalidNewPassword
};

@class SptLicenseData;
@class SptLoginData;

/**
 @protocol ISpontaniaIMApiDelegate
 Protocol to receive COLLABORATE Space SDK notifications
 */
@protocol ISpontaniaIMApiDelegate <NSObject>


/**
 Connection result

 - kSptIMConnect_OK: No error
 - kSptIMConnect_Error: Generic error
 - kSptIMConnect_NetworkError: Error, server no reachable
 - kSptIMConnect_AuthError: Error, authentication problem
 - kSptIMConnect_CredentialsError: Error, wrong credentials
 - kSptIMConnect_ClientVersion: Error, you need to update application in order to connect
 - kSptIMConnect_GDPR: Error, GDPR agreement is pending, accept it and connect
 */
typedef NS_ENUM(NSUInteger, eSptConnectionResult)
{
    kSptIMConnect_OK,
    kSptIMConnect_Error,
    kSptIMConnect_NetworkError,
    kSptIMConnect_AuthError,
    kSptIMConnect_CredentialsError,
    kSptIMConnect_ClientVersion,
    kSptIMConnect_GDPR,
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
/**
 Connected to the server
 */
-(void)onConnected;

/**
 Create account result

 - kSptCreateAccount_OK: Account created
 - kSptCreateAccount_Error: Create account error, generic
 - kSptCreateAccount_NetworkError: Create account error, server not reachable
 - kSptCreateAccount_Exist: Create account error, account already exists
 */
typedef NS_ENUM(NSUInteger, eSptCreateAccountResult)
{
    kSptCreateAccount_OK,
    kSptCreateAccount_Error,
    kSptCreateAccount_NetworkError,
    kSptCreateAccount_Exist
};


/**
 Create account result

 @param eResult Create account result
 @param loginData Data with the account
 */
-(void)onAccountCreatedResult:(eSptCreateAccountResult)eResult
                        login:(SptLoginData*)loginData;


/**
 Recover password result

 - kSptPasswordRecovery_OK: Recover password success
 - kSptPasswordRecovery_Error: Recover password error
 - kSptPasswordRecovery_NetworkError: Recover password error, server not reachable
 */
typedef NS_ENUM(NSUInteger, eSptPasswordRecoveryResult)
{
    kSptPasswordRecovery_OK,
    kSptPasswordRecovery_Error,
    kSptPasswordRecovery_NetworkError
};

/**
 Repover password result

 @param eResult Recover password result
 @param email Email address sent in the recover password request
 */
-(void)onPasswordRecoveryResult:(eSptPasswordRecoveryResult)eResult
                           mail:(NSString *)email;
/**
 Connection error
 
 @param eResult Connection error
 */
-(void)onConnectionError:(eSptConnectionResult)eResult;

@optional
/**
 Local profile required

 @param bRequired YES in case local profile is not set, NO in case it is not required
 */
-(void)onLocalProfileRequired:(BOOL)bRequired;

/**
 Disconnected from the server
 */
-(void)onDisconnected;

@optional
/**
 Cloud storage updated

 @param cloudStorage Call storage data
 */
-(void)onCloudStorageUpdated:(ISptCloudStorage *)cloudStorage;

@optional
/**
 Call credit updated

 @param pstnCredit Credit data
 */
-(void)onCallCreditUpdated:(ISptPSTNCallCredit *)pstnCredit;


/**
 Contact directory updated
 
 @param rosterList A NSArray of ISptContactData object with contact directory
 */
-(void)onRosterList:(NSArray *)rosterList;

/**
 Contact removed from the contact directory
 
 @param contactData Contact removed from the contact directory
 */
-(void)onContactRosterRemoved:(ISptContactData *)contactData;

/**
 Contact added to the contact directory
 
 @param contactData Contact added to the contact directory
 */
-(void)onContactRosterAdded:(ISptContactData *)contactData;

/**
 Contact data updated
 
 @param contactData Contact who has been updated
 */
-(void)onContactUpdated:(ISptContactData *)contactData;

/**
 Presence request received
 
 @param contactData Contact data of the contact who asked for friendship
 */
-(void)onContactPresenceRequest:(ISptContactData *)contactData;

/**
 Contact group created
 
 @param groupData Group data
 */
-(void)onGroupCreated:(ISptGroupData *)groupData;

/**
 Contact added to a group
 
 @param contactID Contact ID who were added
 @param groupData Group data of the updated group
 */
-(void)onGroupContactAdded:(NSNumber*)contactID
                     group:(ISptGroupData *)groupData;

/**
 Contact removed from a group
 
 @param contactID Contact ID who were removed
 @param groupData Group data of the updated group
 */
-(void)onGroupContactRemoved:(NSNumber *)contactID
                       group:(ISptGroupData *)groupData;

/**
 Group removed
 
 @param groupData Group data of the removed group
 */
-(void)onGroupRemoved:(ISptGroupData *)groupData;

/**
 Search service available
 */
-(void)onSearchAvailable;

@optional
/**
 Search for contact at server directory result received
 
 @param searchContact SptSearchContacts with the contacts found
 */
-(void)onSearchResult:(SptSearchContacts *)searchContact;

@optional
/**
 Contact in the last search result updates
 
 @param contactData Object with the updated contact data
 */
-(void)onSearchedContactUpdated:(ISptContactData *)contactData;

@optional
/**
 Search public channel result received
 
 @param searchChannel searcg channel obeject
 */
-(void)onSearchChannelResult:(SptSearchChannels *)searchChannel;

/**
 Local user profile stored
 
 @param localVCard Stored local user profile
 */
-(void)onLocalProfileStored:(ISptModifyProfile *)localVCard;

/**
 Error storing local user profile
 
 @param localVCard Profile that reports error
 */
-(void)onLocalProfileError:(ISptModifyProfile *)localVCard;

/**
 Chat room created
 
 @param contactID NSNumber with the contact ID who created the room
 @param roomCreatedData Roon data of the created room
 */
-(void)onRoomCreated:(NSNumber *)contactID
            roomData:(ISptRoomData*)roomCreatedData;

/**
 Conatct joined to a room
 
 @param contactID Contact ID of the contact who has joined
 @param roomJoinedData room Data object
 */
-(void)onRoomJoined:(NSNumber *)contactID
            roomData:(ISptRoomData*)roomJoinedData;

/**
 Conatct left a room
 
 @param contactID Contact ID of the contact who has left the room
 @param roomJoinedData room Data object
 */
-(void)onRoomLeft:(NSNumber *)contactID
           roomData:(ISptRoomData*)roomJoinedData;


/**
 Room has been updated check [ISptRoomData getUpdatedFields]
 */
-(void)onRoomUpdated:(ISptRoomData*)roomData;

/**
 Event received in a room
 
 @param contactID Contact ID of the contact who produce the event
 @param eventData event data object
 */
-(void)onEventChatReceived:(NSNumber *)contactID
                   message:(ISptEventData*)eventData;

/**
 Event sent to the room
 
 @param eventData event data object
 */
-(void)onEventChatSent:(ISptEventData*)eventData;

/**
 A file is going to be sent to a chat room
 
 @param eventFileData eventFile data
 */
-(void)onEventChatFileSending:(ISptEventData*)eventFileData;

/**
 Event updated
 
 @param eventData Event with updated data
 */
-(void)onEventUpdated:(ISptEventData*)eventData;


/**
 Response to downloadFile, when the file is downloaded this method is called
 
 @param eventData Event with updated data
 */
-(void)onEventFileDownloaded:(ISptEventData *)eventData;

@optional
/**
 List of participant that currently are writing in a chat/channel has been updated
 
 @param room Room where it has been updated
 */
-(void)onRoomWritingUpdated:(ISptRoomData*)room;

@optional
/**
 More room history loaded, this event is an answer of loadMoreRoomEvents
 
 @param room Room where it has been updated
 */
-(void)onRoomMoreHistoryLoaded:(ISptRoomData*)room;

/**
 Channel data have been updated
 
 @param roomData Updated room
 */
-(void)onChannelDataUpdated:(ISptRoomData*)roomData;


/**
 Room history has been synchronized with the server
 
 @param roomData Synchronized room data
 */
-(void)onRoomSynchronized:(ISptRoomData*)roomData;

/**
 A contact, chat/channel or meeting has been added to the favorite list
 @param favoriteData favorite added data
 */
-(void)onFavoriteAdded:(ISptFavoriteData *)favoriteData;

/**
 A contact, chat/channel or meeting has been removed from the favorite list
 @param favoriteData favorite removed data
 */
-(void)onFavoriteRemoved:(ISptFavoriteData *)favoriteData;

@optional
/**
 Device list updated

 @param deviceList An NSArray of SptDeviceData with the list of devices
 */
-(void)onDeviceListUpdated:(NSArray *)deviceList;


@optional
/**
 Device updated

 @param deviceData Device data of the updated device
 */
-(void)onDeviceUpdated:(SptDeviceData *)deviceData;

@optional
/**
 Video device set

 @param deviceData Video device data set
 */
-(void)onVideoDeviceSet:(SptDeviceData *)deviceData;

@optional
/**
 Audio devices set

 @param deviceMic Microphone device data
 @param deviceSpk Speaker device data
 */
-(void)onAudioDevicesSet:(SptDeviceData *)deviceMic
                 speaker:(SptDeviceData *)deviceSpk;

@optional
/**
 Call connected to the media server
 
 @param callID Call ID
 @param callDataObj call data object
 */
-(void)onCallEventConnected:(SptCallID)callID
                   calldata:(ISptCall*)callDataObj;

@optional
/**
 Call disconnected
 
 @param callID Call ID
 @param callDataObj call data object
 */
-(void)onCallEventDisconnected:(SptCallID)callID
                      calldata:(ISptCall*)callDataObj;

@optional
/**
 Call state updated
 
 @param callID Call ID
  @param callDataObj call data object
 */
-(void)onCallEventStateUpdated:(SptCallID)callID
                      calldata:(ISptCall*)callDataObj;


@optional
/**
 Call reconnecting to the media server
 
 @param callID Call ID
 @param callDataObj call data object
 */
-(void)onCallEventReconnecting:(SptCallID)callID
                      calldata:(ISptCall*)callDataObj;


@optional
/**
 A participant has connected to the call
 
 @param callID Call ID
 @param callParticipantObj participoant object interface
 */
-(void)onCallEventParticipantConnected:(SptCallID)callID
                       callParticipant:(ISptCallParticipantData*)callParticipantObj;

@optional
/**
 A participant has disconnected from the call
 
 @param callID Call ID
 @param callParticipantObj participoant object interface
 */
-(void)onCallEventParticipantDisconnected:(SptCallID)callID
                          callParticipant:(ISptCallParticipantData*)callParticipantObj;

@optional
/**
 Call participant data updated (state, services, display name, ...)
 
 @param callID Call ID
 @param callParticipantObj participoant object interface
 */
-(void)onCallEventParticipantUpdated:(SptCallID)callID
                          callParticipant:(ISptCallParticipantData*)callParticipantObj;

@optional
/**
 A stream has started
 
 @param callID Call ID
 @param streamObj stream data object
 */
-(void)onCallEventStreamStarted:(SptCallID)callID
                     streamData:(ISptCallStream*)streamObj;

@optional
/**
 A stream has finished
 
 @param callID Call ID
 @param streamObj stream data object
*/
-(void)onCallEventStreamStopped:(SptCallID)callID
                     streamData:(ISptCallStream*)streamObj;


@optional
/**
 Stream updated (frame received)
 
 @param callID Call ID
 @param streamObj stream data object
*/
-(void)onCallEventStreamNewFrame:(SptCallID)callID
                     streamData:(ISptCallStream*)streamObj;

@optional
/**
 An stream has updated its properties (PTZ control allowed, shared video)
 
 @param callID Call ID
 @param streamObj stream data object
*/
-(void)onCallEventStreamPropertiesUpdated:(SptCallID)callID
                      streamData:(ISptCallStream*)streamObj;

@optional
/**
 An annotation has been created over a stream
 
 @param callID Call ID
 @param streamObj stream data object
 */
-(void)onCallEventAnnotationOverStreamStarted:(SptCallID)callID
                                  streamData:(ISptCallStream*)streamObj;

@optional
/**
 An annotation has been stoped over a given stream
 
 @param callID Call ID
 @param streamObj stream data object
 */
-(void)onCallEventAnnotationOverStreamStoped:(SptCallID)callID
                                  streamData:(ISptCallStream*)streamObj;

@optional
/**
 The speaking state of a stream has been updated
 
 @param callID Call ID
 @param streamObj stream data object
*/
-(void)onCallEventStreaSpeakUpdated:(SptCallID)callID
                               streamData:(ISptCallStream*)streamObj;


@optional
/**
 Call recording state updated

 @param callID Call ID
 @param callDataObj Call data
 */
-(void)onCallEventRecordingStateUpdated:(SptCallID)callID
                               calldata:(ISptCall*)callDataObj;



@optional
/**
 Call request updated

 @param callID Call ID
 @param callRequest Updated call request
 */
-(void)onCallRequestUpdated:(SptCallID)callID
                    request:(SptCallRequest*)callRequest;


@optional
/**
 Recommended painted list updated

 @param callID Call ID
 @param recommendedPaintList Recommended painted list data
 */
-(void)onCallEventRecommendedPaintListUpt:(SptCallID)callID
                                paintlist:(SptCallRecommendedPaintList*)recommendedPaintList;


/**
 Incoming call
 
 @param callID Call ID
 @param callDataObj call data object
 */
@optional
-(void)onCallEventIncomingCall:(SptCallID)callID
                      calldata:(ISptCall *)callDataObj;



@optional
/**
 A participant has changed his speaking state

 @param callID Call ID
 @param callParticipantObj Participant data
 */
-(void)onCallEventParticipantSpeakingUpt:(SptCallID)callID
                      participant:(ISptCallParticipantData*)callParticipantObj;


@optional
/**
 The list of participant that are speaking has been updated

 @param callID Call ID
 @param sortedSpkList NSArray of ISptCallParticipantData sorted by main spekers
 */
-(void)onCallEventParticipantSpeakingListUpt:(SptCallID)callID
                             participantList:(NSArray*)sortedSpkList;


@optional
/**
 Private call chat updated

 @param callID Call ID
 @param callChat Call chat data
 */
-(void)onCallEventPrivateChatUpt:(SptCallID)callID
                            chat:(SptCallChat*)callChat;

@optional
/**
 Public call chat updated.
 A public call chat has been created.

 @param callID Call ID
 @param callChat Call chat data
 */
-(void)onCallEventPublicChatUpt:(SptCallID)callID
                            chat:(SptCallChat*)callChat;


@optional
/**
 Chat received in a call

 @param callID Call ID
 @param callChatEvent Received call chat event
 */
-(void)onCallEventChatReceived:(SptCallID)callID
                     event:(SptCallChatEvent*)callChatEvent;

@optional
/**
 Chat send in a call

 @param callID Call ID
 @param callChatEvent Sent chat event
 */
-(void)onCallEventChatSend:(SptCallID)callID
                     event:(SptCallChatEvent*)callChatEvent;

@optional
/**
 Call chat event updated

 @param callID Call ID
 @param callChatEvent Updated call chat evernt
 */
-(void)onCallEventChatUpdated:(SptCallID)callID
                     event:(SptCallChatEvent*)callChatEvent;

@optional
/**
 Sending a file in the call chat

 @param callID Call ID
 @param callChatEvent Call chat event data
 */
-(void)onCallEventChatFileSending:(SptCallID)callID
                        event:(SptCallChatEvent*)callChatEvent;

@optional
/**
 File downloaded

 @param callID Call ID
 @param callChatEvent Chat call event data
 */
-(void)onCallEventChatFileDownloaded:(SptCallID)callID
                            event:(SptCallChatEvent*)callChatEvent;


@optional
/**
 Send sharing stopped.
 You stopped sharing view

 @param callID Call ID
 */
-(void)onCallEventSendSharingStopped:(SptCallID)callID;


@optional
/**
 Default manage services updated

 @param callID Call ID
 @param callDataObj Call data
 */
-(void)onCallEventDefaultManageServicesUpdated:(SptCallID)callID
                                      calldata:(ISptCall *)callDataObj;


@optional
/**
 Call connectivity updated

 @param callID Call ID of the updated call
 */
-(void)onCallEventConnectivityUpdated:(SptCallID)callID;


@optional
/**
 Meetings data synchronized with server.
 It is received after connec to the server when meetings are synchronized.
 In case of reconnection meetings are also synchronized
 */
-(void)onSchMeetingsSynchronized;

@optional
/**
 Meeting created successfully

 @param meetingSeq Created meeting
 */
-(void)onSchMeetingCreated:(SptSchMeetingSequence*)meetingSeq;

@optional
/**
 Create meeting error

 @param meetingCreate Meeting that report error in creation
 */
-(void)onSchMeetingCreateError:(SptSchMeetingCreate*)meetingCreate;

@optional
/**
 Meeting sequence create progress

 @param meetingCreate Creating meeting sequence that has update its creation progress
 */
-(void)onSchMeetingCreateProgress:(SptSchMeetingCreate*)meetingCreate;

@optional
/**
 Meeting sequence updated.
 Check flags to know waht fields has been updated

 @param meetingSeq Meeting sequence data
 */
-(void)onSchMeetingUpdated:(SptSchMeetingSequence*)meetingSeq;


/**
 Cakk history event

 - kCallHistoryEventLoaded: Call history loaded from local database
 - kCallHistoryEventSynchronized: Call history synchronized with server data
 - kCallHistoryEventLoadedMore: More call history loaded in memory
 - kCallHistoryEventLoadedMoreError: Error loading more call history
 */
typedef NS_ENUM(NSUInteger, eSptCallHistoryEvent)
{
    kCallHistoryEventLoaded,
    kCallHistoryEventSynchronized,
    kCallHistoryEventLoadedMore,
    kCallHistoryEventLoadedMoreError
};

@optional
/**
 Call histroy event

 @param event Reported event
 */
-(void)onCallHistoryReport:(eSptCallHistoryEvent)event;


@optional
/**
 Invide contact by email result

 @param success YES in case of success, NO in case of error
 */
-(void)onContactsInvitedByEmailResult:(BOOL)success;


@optional
/**
 Personal ToDos updated

 @param personalToDos An NSArray of SptToDo with personal ToDos
 */
-(void)onPersonalToDosUpdated:(NSArray *)personalToDos;


@optional
/**
 Search event result. Data is available in the search event object
 */
-(void)onSearchEventsResult;


@optional
/**
 Load chat history from a search event result result

 @param searchedEventRes search event result used to load room history
 */
-(void)onLoadSeaechedEventRes:(SptLoadSearchedEventRes*)searchedEventRes;
    

@optional
/**
 File ipdated

 @param fileData Updated file data
 */
-(void)onFileUpdated:(SptFile*)fileData;

@optional
/**
License Updated
 
 @param license New updated license
 */
-(void)onLicenseUpdated:(SptLicenseData*)license;

@optional
/**
 Token data result
 
 @param tokenDataResult Token data result
 */
-(void)onGetTokenDataResult:(SptTokenDataResult *)tokenDataResult;

@optional

/**
 Password change result
 
 @param result with ok or the error code
 */
-(void)onChangePasswordResult:(eSptChangePasswordResult)result;


@optional

/**
 Phone call rate result
 
 @param phoneNumber Phone number
 @param rate Call rate in $/min
*/
-(void)onPhoneCallRateResult:(NSString *)phoneNumber
                        cost:(NSString *)rate;

@optional

/**
 Contact phone call rate result
 
 @param result an SptContactPhoneRateResult object with the call rates
 */
-(void)onContactPhoneCallRateResult:(SptContactPhoneRateResult*)result;


@optional
/**
 Calls has been synchronized
 
 */
-(void)onCallsSynchronized;

@end

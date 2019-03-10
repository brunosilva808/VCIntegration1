/*!
  SptIMRoomExt.h
  SptIMCoreIOS
  @framework COLLABORATESapce

  Copyright © 2018 ClearOne. All rights reserved.
*/

#import "ISptTypes.h"
#import "ISptIMFavoriteExt.h"
#import "ISptFileExt.h"

@class ISptContactData;
@class SptEntryCollection;

/*!
 @class ISptChannelData
 Channel data
 Use this object to modify channel data
 */
@interface ISptChannelData : NSObject

/*!
 Channel display name
 */
@property (readwrite) NSString* channelName;
/*!
 Channel description
 */
@property (readwrite) NSString* channelDescription;
/*!
 Channel picture
 */
@property (readwrite) UIImage *channelPicture;
/*!
 Public channel
 */
@property (readwrite) BOOL publicChannel;
/*!
 Room ID
 */
@property (readonly)  SptIMRoomID roomID;

@end



/*!
 @class ISptEventData
 Event data
 */
@interface ISptEventData : NSObject

/*!
 Event type
 
 - kSptEventTypeInvalid: Invalid event type
 - kSptEventTypeChatMessage: Chat message
 - kSptEventTypeFile: File message
 - kSptEventNotificationTitleUpd: Channel title updated
 - kSptEventNotificationDescUpd: Channel description updated
 - kSptEventNotificationPublic: Channel changes to public
 - kSptEventNotificationAddedParts: Contact added to the chat
 - kSptEventNotificationJoinedPart: Contact joined to a public channel
 - kSptEventNotificationLeaveParts: Contact left the chat
 - kSptEventNotificationOutcastParts: Host expelled a contact
 - kSptEventNotificationCallStarted: Call startted over the chat
 - kSptEventNotificationCallNoAnswer: Call finished. Call was not answered. You are the caller
 - kSptEventNotificationCallMissed: Call finished, You didn0t answer an incomming call
 - kSptEventNotificationCallFinished: Call finished. Call was established
 - kSptEventNotificationCallError: Call finished. There was an error during the call
 */
typedef NS_ENUM(NSUInteger, eSptEventType)
{
    kSptEventTypeInvalid,
    kSptEventTypeChatMessage,
    kSptEventTypeFile,
    kSptEventNotificationTitleUpd,
    kSptEventNotificationDescUpd,
    kSptEventNotificationPublic,
    kSptEventNotificationAddedParts,
    kSptEventNotificationJoinedPart,
    kSptEventNotificationLeaveParts,
    kSptEventNotificationOutcastParts,
    kSptEventNotificationCallStarted,
    kSptEventNotificationCallNoAnswer,
    kSptEventNotificationCallMissed,
    kSptEventNotificationCallFinished,
    kSptEventNotificationCallError
};

/*!
 Event state

 - kSptEventStateUnknown: Unknown state
 - kSptEventStateError: Error sending event
 - kSptEventStateReceived: Event received
 - kSptEventStateSent: Event sent
 - kSptEventStateSending: Event sending
 - kSptEventStateUploading: Uploading file to the cloud
 - kSptEventStateDownloading: Downloading file from the cloud
 - kSptEventStateDownloaded: File downloaded
 - kSptEventStateDeleted: File uploaded
 */
typedef NS_ENUM(NSUInteger, eSptEventState)
{
    kSptEventStateUnknown,
    kSptEventStateError,
    kSptEventStateReceived,
    kSptEventStateSent,
    kSptEventStateSending,
    kSptEventStateUploading,
    kSptEventStateDownloading,
    kSptEventStateDownloaded,
    kSptEventStateDeleted
};

/*!
 Event update flags

 - kEventUpdatedProgress: Upload/download progress updated
 - kEventUpdatedThumbnail: File thumbnail updated
 - kEventUpdatedState: Event state updated
 */
typedef NS_OPTIONS(NSUInteger, eEventUpdatedFields)
{
    kEventUpdatedProgress  = 1 << 0,
    kEventUpdatedThumbnail = 1 << 1,
    kEventUpdatedState     = 1 << 2
};

/*!
 Event ID
 */
@property (readonly) SptIMEventID eventID;
/*!
 Room ID
 */
@property (readonly) SptIMRoomID roomID;
/*!
 Type of event
 */
@property (readonly) eSptEventType eventType;
/*!
 Contact data who produce the event
 */
@property (readonly) ISptContactData *contact;
/*!
 Messahe
 */
@property (readonly) NSString *message;
/*!
 Time in local device time zone
 */
@property (readonly) NSDate *time;
/*!
 State of the evemt
 */
@property (readonly) eSptEventState state;
/*!
 In case of file, file data
 */
@property (readonly) SptFile *file;
/*!
 In case of kSptEventNotificationAddedParts or kSptEventNotificationOutcastParts an NSArray of ISptContactData with
 the list of participants added or expelled
 */
@property (readonly) NSArray *contactCollection;
/*!
 Milliseconds to the epoch when event was created
 */
@property (readonly) uint64_t utcTimeEpochMilliseconds;

/*!
 Is it a private event
 */
@property (readonly) BOOL isPrivate;
/*!
 NSArray of ISptContactData with the addressed contacts in case private chat
 */
@property (readonly) NSArray *addressedContact;

/*!
 Get updated fields from the last time they were reset

 @param reset Reset updated fields
 @return A bit combination with the updated fields
 */
-(eEventUpdatedFields)getUpdatedFields:(BOOL)reset;

@end


/*!
 @class SptSearchedEventData
 Found event in event search
 */
@interface SptSearchedEventData : NSObject
/*!
 Event type
 */
@property (readonly) eSptEventType eventType;
/*!
 Part of the message body with the match
 */
@property (readonly) NSString *message;
/*!
 Event date in local time
 */
@property (readonly) NSDate *time;
/*!
 Event date in milliseconds to the epoch
 */
@property (readonly) uint64_t utcTimeEpochMilliseconds;
/*!
 Room ID
 */
@property (readonly) SptIMRoomID roomID;
/*!
 Meeting sequence ID in case event belong to a meeting
 */
@property (readonly) SptMeetingSeqID seqID;
/*!
 Meeting ID in case event belong to a meeting
 */
@property (readonly) SptMeetingID meetingID;

/*!
 Contact who produce the event
 */
@property (readonly) ISptContactData *contact;
/*!
 In case it contains a file, file data
 */
@property (readonly) SptFile *file;
/*!
 Is it a private event
 */
@property (readonly) BOOL isPrivate;
/*!
 In case of private event, NSArray of ISptContactData with the addressed contacts
 */
@property (readonly) NSArray *addressedContact;
@end



/*!
 @class SptSearchEventsConfig
 Configure search results in a event search
 */

@interface SptSearchEventsConfig : NSObject
/*!
 Create instance

 @param eventsPerPage Number of events to retrieve per page
 @param beforeMatch String to add before the match, for example "<b>"
 @param afterMatch String to add after the match, for example "</b>"
 @param aroundMatch String to add around the part of the body retrieved, for example "..."
 @param maxWordsPerEvent Max words to retrieve around a match
 @return created instance
 */
+(instancetype)searchedEventsConfigWithData:(NSUInteger)eventsPerPage
                          insertBeforeMatch:(NSString *)beforeMatch
                           insertAfterMatch:(NSString *)afterMatch
                          insertAroundMatch:(NSString *)aroundMatch
                                   maxWords:(NSUInteger)maxWordsPerEvent;

/*!
 Events per page
 */
@property (readonly) NSUInteger eventsPerPage;
/*!
 String to inset before the match
 */
@property (readonly) NSString *beforeMatch;
/*!
 String to insert after the match
 */
@property (readonly) NSString *afterMatch;
/*!
 String to insert at the beginning and at the end of the retrieved part of the message
 */
@property (readonly) NSString *aroundMatch;
/*!
 Max words to retrieve per match
 */
@property (readonly) NSUInteger maxWordsPerEvent;
@end


/*!
 Search for events
 */
@interface SptSearchEvents : NSObject
/*!
 Create instance

 @param searchText text pattern to seach
 @param searchConfig CSearch configuration
 @return created instance
 */
+(instancetype) searchEventsWithData:(NSString *)searchText
                              condig:(SptSearchEventsConfig*)searchConfig;

/*!
 Get event found by position

 @param position Position to retrieve the event starting at 0
 @return Searched event data
 */
-(SptSearchedEventData *)eventByPosition:(NSUInteger)position;


/*!
 Search text pattern
 */
@property (readonly) NSString *searchText;


/*!
 Search state

 - kSearchStatePrepared: Search is created but not performed yet
 - kSearchStateSearching: Search in progress
 - kSearchStateFound: Search results, there are more pages
 - kSearchStateFinish: Search finished, there isn't more pages
 - kSearchStateError: Error in search
 */
typedef NS_ENUM(NSUInteger, eSptSearchEventsState)
{
    kSearchStatePrepared    = 0,
    kSearchStateSearching   ,
    kSearchStateFound       ,
    kSearchStateFinish      ,
    kSearchStateError
};


/*!
 Search state
 */
@property (readonly) eSptSearchEventsState state;
/*!
 Are there more result to retrieve
 */
@property (readonly) BOOL areThereMore;
/*!
 Current number of events loaded
 */
@property (readonly) NSUInteger currentFound;
/*!
 Search result config
 */
@property (readonly) SptSearchEventsConfig *searchConfig;

@end



/*!
 @class SptLoadSearchedEventRes
 Load events history in a room till an event found in the search event result
 */
@interface SptLoadSearchedEventRes : NSObject
/*!
 Searched event, got from a search result
 */
@property (readonly) SptSearchedEventData *searchedEvent;
/*!
 Corresponding event in the room
 */
@property (readonly) ISptEventData * eventData;

@end


/*!
 @class ISptRoomData
 Room data
 */
@interface ISptRoomData : NSObject

/*!
 Room type

 - kSptRoomTypeOne2One: One 2 one room
 - kSptRoomTypeMultiUser: Multi user chat room
 - kSptRoomTypeChannel: Channel room
 - kSptRoomTypeMeeting: Meeting room
 */
typedef NS_ENUM(NSUInteger, eSptRoomType)
{
    kSptRoomTypeOne2One,
    kSptRoomTypeMultiUser,
    kSptRoomTypeChannel,
    kSptRoomTypeMeeting
};

/*!
 Room state

 - kSptRoomStateUnknown: Unknown room state
 - kSptRoomStateDisconnected: Disconnected
 - kSptRoomStateCreating: Creating the room
 - kSptRoomStateJoining: You are joining to this room
 - kSptRoomStateConnected: Connected to the server
 - kSptRoomStateClosed: Closed
 - kSptRoomStateFound: It is a room received in a public channel search
 */
typedef NS_ENUM(NSUInteger, eSptRoomState)
{
    kSptRoomStateUnknown = 0,
    kSptRoomStateDisconnected,
    kSptRoomStateCreating,
    kSptRoomStateJoining,
    kSptRoomStateConnected,
    kSptRoomStateClosed,
    kSptRoomStateFound
};

/*!
 Room ID
 */
@property (readonly) SptIMRoomID roomID;
/*!
 Room state
 */
@property (readonly) eSptRoomState roomState;
/*!
 Is it synchronized with the server
 */
@property (readonly) BOOL synchronized;
/*!
 Creation date in local time
 */
@property (readonly) NSDate *creationDate;
/*!
 NSArray of ISptContactData with the participants
 */
@property (readonly) NSArray *participants;
/*!
 NSArray of ISptContactData with the blocked participants.
 You need to be channel admin to get this list
 */
@property (readonly) NSArray *blockedParticipants;
/*!
 Admin of the channel
 */
@property (readonly) ISptContactData *admin;
/*!
 Number of participants
 */
@property (readonly) NSUInteger numParticipants;
/*!
 Number of events in the room
 */
@property (readonly) NSUInteger numEvents;
/*!
 Number of events loaded in the room
 */
@property (readonly) NSUInteger numLoadedEvents;
/*!
 Can I load more events
 */
@property (readonly) BOOL canLoadMoreEvents;
/*!
 Last event in the room
 */
@property (readonly) ISptEventData *lastEvent;
/*!
 Last event readed in the room
 */
@property (readonly) ISptEventData *lastReadEvent;
/*!
 Last event not readed in the room
 */
@property (readonly) ISptEventData *firstUnreadEvent;

/*!
 Get a dictionary with the events sorted by time separated by days
 */
@property (readonly) NSDictionary *datedEvents;
/*!
 An NSArray of ISptEventData with the events
 */
@property (readonly) NSArray *events;
/*!
 An NSArray of NSString with the display name of the participants
 */
@property (readonly) NSArray *contactNames;
/*!
 Room type
 */
@property (readonly) eSptRoomType roomType;
/*!
 Get the fist remote contact in the participant list. IT is usefull in case of
 One 2 one room
 */
@property (readonly) ISptContactData * remoteContact;

/*!
 Room display name, in case of one 2 one the display name of the other contact,
 in case multiuser chat room the display name of the participants separate by commas,
 in case of channel, the channel name
*/
@property (readonly) NSString *displayName;

/*!
 The display name normalized, usefull to compare
 */
@property (readonly) NSString *normalizedDisplayName;
/*!
 In case of channel, channel description
 */
@property (readonly) NSString *description;
/*!
 In case of one 2 one room the picture of the other participant, in case of channel,
 the channel picture
 */
@property (readonly) UIImage *picture;

/*!
 Channel data, use returned object in case you want to chnge channel info
 */
@property (readonly) ISptChannelData* channelData;

/*!
 Get favorite ID
 */
@property (readonly) SptIMFavoriteID favoriteID;

/*!
 Can I add participants to the room
 */
@property (readonly) BOOL canIAddParticipants;
/*!
 Can I change channel data
 */
@property (readonly) BOOL canIChangeChannelData;

/*!
 Can I start a call over the room
 */
@property (readonly) BOOL canIStartCall;
/*!
 Can I send files to this room
 */
@property (readonly) BOOL canISendFiles;
/*!
 Can I send private messages to this room
 */
@property (readonly) BOOL canISendPrivateMessages;
/*!
 Can I block participants in this room
 */
@property (readonly) BOOL canIBlockParticipants;
/*!
 NSArray of ISptContactData with the contacts that are currently writing in this room
 */
@property (readonly) NSArray *contactsWriting;

/*!
 Can I remove an event

 @param eventID Event ID to check
 @return YES in case you can remove, NO otherwise
 */
-(BOOL)canIRemoveEvent:(SptIMEventID)eventID;

/*!
 Get an NSArray of events after an event

 @param eventID Event ID to get events after it
 @return NSArray of ISptEventData with events after eventID
 */
-(NSArray *)getEventsFrom:(SptIMEventID)eventID;


/*!
 Get the number of unread events

 @param bReset Reset
 @return Number of unread events
 */
-(NSUInteger)getPendingEvents:(BOOL)bReset;

/*!
 Get a collection with all files attached to the chat

 @return Collection with all files attached to the chat
 */
-(SptFileCollection *)getFiles;

/*!
 Room updated flags

 - kRoomNoChanges: No changes
 - kRoomChannelData: Channel data updated
 - kRoomData: Room data updated, created date
 - kRoomState: Room state updated
 - kRoomParticipants: Participants updated
 - kRoomNotes: Notes updated
 - kRoomToDos: ToDos updated
 */
typedef NS_OPTIONS(NSUInteger, eSptRoomUpdatedFields)
{
    kRoomNoChanges          = 0,
    kRoomChannelData        = 1 << 0,
    kRoomData               = 1 << 1,
    kRoomState              = 1 << 2,
    kRoomParticipants       = 1 << 3,
    kRoomNotes              = 1 << 4,
    kRoomToDos              = 1 << 5,
    kRoomCall               = 1 << 6
};

/*!
 Get updated fields from last time they were reset

 @param reset Reset updated fields
 @return updated fields
 */
-(eSptRoomUpdatedFields) getUpdatedFields:(BOOL)reset;

/*!
 Get notes
 */
@property (readonly) SptEntryCollection *notes;
/*!
 An NSArray of SptToDo with the ToDos in the room
 */
@property (readonly) NSArray *toDos;

/*!
 Can I nodify a ToDo

 @param entryID Entry ID of the ToDo to chack
 @return YES in case you can modify, NO otherwise
 */
-(BOOL)canIModifyToDo:(SptEntryID)entryID;

/*!
 Call over room state
 
 - kRoomCallNoCall: There is not any active call over this room
 - kRoomCallCanConnect: There is an active call over this room and you can connect
 - kRoomCallConnectedInOtherDevice: There is an active call over this room and you are connected to this call in other device
 - kRoomCallConnected: There is an active call over this room and you are connected to this call in this device
 */
typedef NS_ENUM(NSUInteger, eSptActiveCallRoom) {
    kRoomCallNoCall = 0,
    kRoomCallCanConnect,
    kRoomCallConnectedInOtherDevice,
    kRoomCallConnected
};

/**
 Active call over this room state
 */
@property (readonly) eSptActiveCallRoom callState;

/**
 In case of active call over this room, get call ID
 */
@property (readonly) SptCallID callID;

@end


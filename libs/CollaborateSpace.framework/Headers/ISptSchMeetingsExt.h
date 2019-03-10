/**
  ISptSchMeetingsExt.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

#import "ISptTypes.h"
#import "ISptIMContactExt.h"
#import "ISptFileExt.h"
#import "ISptEntryExt.h"
#import "ISptIMRoomExt.h"


/**
 @class SptSchParticipant
 Meeting participant
 */
@interface SptSchParticipant : NSObject<SptContactBase>

/**
 Type of participant

 - kSptSchIMParticipant: IM contact
 - kSptSchEMailParticipant: Email
 - kSptSchCollaborateRoom: COLLABORATE Pro room
 */
typedef NS_ENUM(NSUInteger, SptParticipantType)
{
    kSptSchIMParticipant,
    kSptSchEMailParticipant,
    kSptSchCollaborateRoom
};

/**
 Participant state

 - kSptSchPartStateUnknown: Unknown state
 - kSptSchPartStateInvited: Invited, participant has not aanswered invitation yet
 - kSptSchPartStateMaybe: MAybe.
 - kSptSchPartStateAccepted: Accepted
 - kSptSchPartStateDeclined: Declined
 - kSptSchPartStateCancelled: Host has spelled this participant
 */
typedef NS_ENUM(NSUInteger, SptSchPartState)
{
    kSptSchPartStateUnknown,
    kSptSchPartStateInvited,
    kSptSchPartStateMaybe,
    kSptSchPartStateAccepted,
    kSptSchPartStateDeclined,
    kSptSchPartStateCancelled
};

/**
 Type of participant
 */
@property (readonly) SptParticipantType participantType;
/**
 Contact ID
 */
@property (readonly) TSptIMContactID contactID;
/**
 Contact data
 */
@property (readonly) ISptContactData *imContact;
/**
 Participant state
 */
@property (readonly) SptSchPartState state;
/**
 Is the host of the meeting
 */
@property (readonly) BOOL isHost;

@end


/**
 @class SptSchParticipantCollection
 Meeting participant collection
 */
@interface SptSchParticipantCollection : NSObject

/**
 Number of participants
 */
@property (readonly) NSUInteger numParticipants;
/**
 Number of COLLABORATE Pro room
 */
@property (readonly) NSUInteger numCollaborateRooms;
/**
 NSArray of SptSchParticipant with the participants
 */
@property (readonly) NSArray<SptSchParticipant*> *participants;
/**
 NSArray of SptSchParticipant with the COLLABORATE Pro rooms
 */
@property (readonly) NSArray<SptSchParticipant *> *collaborateRooms;

/**
 Get participant data by its contact ID

 @param contactID Contact ID
 @return Participant data
 */
-(SptSchParticipant *)participantByContactID:(TSptIMContactID)contactID;
/**
 Host participant
 */
@property (readonly) SptSchParticipant *host;
/**
 Local participant
 */
@property (readonly) SptSchParticipant *localParticipant;
@end

/**
 @class SptSchMeeting
 Meeting data
 */
@interface SptSchMeeting : NSObject

/**
 Meeting state

 - kSptSchMeetingStateNone: Unknown meeting state
 - kSptSchMeetingStateCreating: Meeting is being created
 - kSptSchMeetingStateCreated: Meeting is created
 - kSptSchMeetingStateWaitingHost: Meeting should be started by its start date but host doesn't connect yet
 - kSptSchMeetingStateActive: Meeting is active, you can connect
 - kSptSchMeetingStateFinished: Meeting finished
 - kSptSchMeetingStateCancelled: Meeting cancelled
 */
typedef NS_ENUM(NSUInteger, SptSchMeetingState)
{
    kSptSchMeetingStateNone,
    kSptSchMeetingStateCreating,
    kSptSchMeetingStateCreated,
    kSptSchMeetingStateWaitingHost,
    kSptSchMeetingStateActive,
    kSptSchMeetingStateFinished,
    kSptSchMeetingStateCancelled
};

/**
 Meeting sequence ID
 */
@property (readonly) SptMeetingSeqID meetingSeqID;
/**
 Meeting ID
 */
@property (readonly) SptMeetingID meetingID;
/**
 Meeting state
 */
@property (readonly) SptSchMeetingState schMeetingState;

/**
 Meeting title
 */
@property (readonly) NSString *meetingTitle;
/**
 Meeting normalized title
 */
@property (readonly) NSString *meetingNormalizedTitle;
/**
 Meeting description
 */
@property (readonly) NSString *meetingDescription;

/**
 Meeting start date in local time
 */
@property (readonly) NSDate *startDate;

/**
 Meeting duration
 */
@property (readonly) NSDateComponents *duration;

/**
 Meeting agenda
 */
@property (readonly) SptEntryCollection *agenda;
/**
 Meeting notes
 */
@property (readonly) SptEntryCollection *notes;

/**
 Room associated to the meeting
 */
@property (readonly) ISptRoomData *room;

/**
 Meeting host
 */
@property (readonly) SptSchParticipant *host;
/**
 Meeting participants
 */
@property (readonly) SptSchParticipantCollection *participants;

/**
 Files attached to the meeting
 */
@property (readonly) SptFileCollection *files;

/**
 Get recordings attached to the meeting
 */
@property (readonly) SptFileCollection *recordings;

/**
 Can I add files
 */
@property (readonly) BOOL canIAddFiles;

/**
 Can I remove a file

 @param fileID File ID to check
 @return YES in case you can remove the file, NO  otherwise
 */
-(BOOL)canIRemoveFile:(SptFileID)fileID;



/**
 Meeting updated files

 - kNoUpdated: No updateds
 - kDurationUpdated: Duration updated
 - kDateUpdated: Date updated
 - kStateUpdated: State updated
 - kAgendaUpdated: Agenda updated
 - kNotesUpdated: Notes updated
 - kFilesUpdated: Files updated
 - kFilesUpdatedThumbnails: Thumbnail files updated
 - kLastChatMessages: Last chat updated
 - kFileDownloaded: File downloaded
 - kFileProgress: Upload/download file progress updated
 - kToDosUpdated: ToDos updated
 */
typedef NS_OPTIONS(NSUInteger, MeetingUpdatedFields)
{
    kNoUpdated              = 0,
    kDurationUpdated        = (1 << 0),
    kDateUpdated            = (1 << 1),
    kStateUpdated           = (1 << 2),
    kAgendaUpdated          = (1 << 3),
    kNotesUpdated           = (1 << 4),
    kFilesUpdated           = (1 << 5),
    kFilesUpdatedThumbnails = (1 << 6),
    kLastChatMessages       = (1 << 7),
    kFileDownloaded         = (1 << 8),
    kFileProgress           = (1 << 9),
    kToDosUpdated           = (1 << 10),
    kParticpantsUpdated     = (1 << 11),
    kParticpantsStateUpdated =(1 << 12)
};

/**
 Get the updated fields from the last reset
 
 @param bReset In case of true, updated fields are reset
 @result It returns a bit combination of eMeetingUpdatedFields with the updated fields
 */
-(MeetingUpdatedFields)getUpdatedInfo:(BOOL)bReset;

/**
 Last participant who makes a change iun the meeting
 */
@property (readonly) SptSchParticipant *lastUpdateParticipant;
/**
 Date of the last updated in local time
 */
@property (readonly) NSDate *lastUpdateDate;

/**
 Get last chat message in the meeting
 
 @result It returns a collection with the last chat messages in the meeting
*/
@property (readonly) NSArray<ISptEventData *> *lastChatMessages;


/**
 NSArray od SptToDo with the ToDos collection
 */
@property (readonly) NSArray<SptToDo *> *toDos;

/**
 Can I modify a ToDo

 @param entryID Entry ID of the ToDo to check
 @return YES in case you can modify, false otherwise
 */
-(BOOL)canIModifyToDo:(SptEntryID)entryID;

@end


/**
 @class SptSchMeetingSequence
 Meeting sequence
 */
@interface SptSchMeetingSequence : NSObject

/**
 Meeting sequence state

 - kMeetingSeqUnknown: Unknown state
 - kMeetingSeqAlive: There is at least one future or active meeting in the sequence
 - kMeetingSeqFinished: All meetings in the sequence are finished
 - kMeetingSeqCancelled: Sequence has been cancelled
 */
typedef NS_ENUM(NSUInteger, MeetingSequenceState)
{
    kMeetingSeqUnknown,
    kMeetingSeqAlive,
    kMeetingSeqFinished,
    kMeetingSeqCancelled
};


/**
 Meeting sequence type

 - kSptRepeatMeetingNow: Meeting now
 - kSptRepeatMeetingDay: Meeting one day
 - kSptRepeatMeetingWeekly: Meeting repeat weekly
 - kSptRepeatMeetingMonthlyWeek: Meeting repeat day in the week of the month
 - kSptRepeatMeetingMonthlyDay: Meeting repeat day of the month
 - kSptRepeatMeetingUnknown: Unknown type
 */
typedef NS_ENUM(NSUInteger, MeetingSequenceType)
{
    kSptRepeatMeetingNow,
    kSptRepeatMeetingDay,
    kSptRepeatMeetingWeekly,
    kSptRepeatMeetingMonthlyWeek,
    kSptRepeatMeetingMonthlyDay,
    kSptRepeatMeetingUnknown
};


/**
 Day of the week

 - kSptRepeatNoneDay: None
 - kSptRepeatMonday: Monday
 - kSptRepeatTuesday: Tuesday
 - kSptRepeatWednesday: Wednesday
 - kSptRepeatThursday: Thursday
 - kSptRepeatFriday: Friday
 - kSptRepeatSaturday: Saturday
 - kSptRepeatSunday: Sunday
 - kSptRepeatWeekdays: Weekdays Monday-Friday
 - kSptRepeatEveryday: Everyday
 */
typedef NS_OPTIONS(NSUInteger, MeetingRepeatWeekly)
{
    kSptRepeatNoneDay   = 0,
    kSptRepeatMonday    = (1 << 0),
    kSptRepeatTuesday   = (1 << 1),
    kSptRepeatWednesday = (1 << 2),
    kSptRepeatThursday  = (1 << 3),
    kSptRepeatFriday    = (1 << 4),
    kSptRepeatSaturday  = (1 << 5),
    kSptRepeatSunday    = (1 << 6),
    kSptRepeatWeekdays  = 0x1F,
    kSptRepeatEveryday  = 0x7F
};


/**
 Week of the month

 - kSptRepeatMonthNone: None
 - kSptRepeatFirstInMonth: First week of the month
 - kSptRepeatSecondInMonth: Second week of the month
 - kSptRepeatThirdInMonth: Third week of the month
 - kSptRepeatFourthInMonth: Fourth week of the month
 - kSptRepeatLastInMonth: Last week of the month
 - kSptRepeatEveryWeek: Every week
 */
typedef NS_OPTIONS(NSUInteger, MeetingRepeatMonthlyWeek)
{
    kSptRepeatMonthNone       = 0,
    kSptRepeatFirstInMonth    = (1 << 0),
    kSptRepeatSecondInMonth   = (1 << 1),
    kSptRepeatThirdInMonth    = (1 << 2),
    kSptRepeatFourthInMonth   = (1 << 3),
    kSptRepeatLastInMonth     = (1 << 4),
    kSptRepeatEveryWeek       = 0x1F
};

/**
 Meeting sequence properties

 - kSptSchPropertiesJoinBeforeHost: Join before host
 - kSptSchPropertiesAudioServiceAllow: Participants can manage audio service
 - kSptSchPropertiesVideoServiceAllow: Participants can manage video service
 - kSptSchPropertiesTextServiceAllow: Participants can manage text service
 - kSptSchPropertiesSharingServiceAllow: Participants can manage sharing service
 - kSptSchPropertiesControlServiceAllow: Participants can manage remote control service
 - kSptSchPropertiesWhiteboardServiceAllow: Participants can manage whiteboard/annotation service
 - kSptSchPropertiesFileServiceAllow: Participants can manage file transfer service
 - kSptSchPropertiesAllActive: Particicipants can manage all services
 */
typedef NS_OPTIONS(NSUInteger, MeetingSequenceProperties)
{
    kSptSchPropertiesJoinBeforeHost         = (1 << 0),
    kSptSchPropertiesAudioServiceAllow      = (1 << 1),
    kSptSchPropertiesVideoServiceAllow      = (1 << 2),
    kSptSchPropertiesTextServiceAllow       = (1 << 3),
    kSptSchPropertiesSharingServiceAllow    = (1 << 4),
    kSptSchPropertiesControlServiceAllow    = (1 << 5),
    kSptSchPropertiesWhiteboardServiceAllow = (1 << 6),
    kSptSchPropertiesFileServiceAllow       = (1 << 7),
    kSptSchPropertiesAllActive              = 0xFF
};

/**
 Meeting sequence ID
 */
@property (readonly) SptMeetingSeqID meetingSequenceID;
/**
 Meeting sequence state
 */
@property (readonly) MeetingSequenceState state;


/**
 Meeting sequence repeat type
 */
@property (readonly) MeetingSequenceType type;
/**
 Meeting sequence start date
 */
@property (readonly) NSDate *startDate;
/**
 Meeting sequence end date. Available in case repeat meeting
 */
@property (readonly) NSDate *endDate;
/**
 Repeat meeting, days of week
 */
@property (readonly) MeetingRepeatWeekly daysOfWeek;
/**
 Repeat meeting, weeks of month
 */
@property (readonly) MeetingRepeatMonthlyWeek weeksOfMonth;

/**
 Meeting title
 */
@property (readonly) NSString *title;
/**
 Normalized meeting title
 */
@property (readonly) NSString *normalizedTitle;
/**
 Meeting description
 */
@property (readonly) NSString *description;

/**
 Meeting properties
 */
@property (readonly) MeetingSequenceProperties meetingsProperties;

/**
 Host participant
 */
@property (readonly) SptSchParticipant *host;
/**
 Local participant
 */
@property (readonly) SptSchParticipant *localParticipant;
/**
 Participant collection
 */
@property (readonly) SptSchParticipantCollection *participants;

/**
 Next meeting in case exists, nil in case there isn't
 */
@property (readonly) SptSchMeeting *nextMeeting;
/**
 Last meeting done in case exists, nil other case
 */
@property (readonly) SptSchMeeting *lastMeeting;
/**
 Current meeting in active state, nil in case there isn't any
 */
@property (readonly) SptSchMeeting *currentMeeting;

/**
 Get meeting by meeting ID

 @param meetingID Meeting ID
 @return Meeting data
 */
-(SptSchMeeting *)getMeetingByID:(SptMeetingID)meetingID;
/**
 An NSArray of SptSchMeeting with all meetings in the sequence
 */
@property (readonly) NSArray<SptSchMeeting*> *allMeetings;

/**
 Am I host
 */
@property (readonly)  BOOL amIHost;
/**
 Can I set attend state
 */
@property (readonly)  BOOL canISetAttend;
/**
 Can I change participants, add or remove
 */
@property (readonly)  BOOL canIChangeParticipants;
/**
 Can I change meetings date/duration
 */
@property (readonly)  BOOL canIChangeMeetings;
/**
 Can I change meeting title
 */
@property (readonly)  BOOL canIChangeTitle;
/**
 Can I change meeting properties
 */
@property (readonly)  BOOL canIManageProperties;
/**
 Can I cancel meeting sequence
 */
@property (readonly)  BOOL canICancelSequence;
/**
 Can I cancel a meeting

 @param meetingID Meeting ID
 @return YES in case you can cancel, NO otherwise
 */
-(BOOL)canICancelMeeting:(SptMeetingID)meetingID;

/**
 Meeting sequence update flags

 - kNoChanges: No changes
 - kParticipants: Participants added or removed
 - kParticipantsState: Participant state updated
 - kSeqState: Meeting sequence state updated
 - kSeqProperties: Meeting sequence properties updated
 - kMeetings: Meetings updated
 - kChatRoom: Meeting sequence associated chat room updated (room set)
 - kMeetingsChat: Meeting sequence chat updated (chat received)
 - kMeetingTitle: Meeting sequence title updated
 */
typedef NS_OPTIONS(NSUInteger, MeetingSeqChanges)
{
    kNoChanges          = 0,
    kParticipants       = (1 << 0),
    kParticipantsState  = (1 << 1),
    kSeqState           = (1 << 2),
    kSeqProperties      = (1 << 3),
    kMeetings           = (1 << 4),
    kChatRoom           = (1 << 5),
    kMeetingsChat       = (1 << 6),
    kMeetingTitle       = (1 << 7)
};

/**
 Get updated fields since the last reset

 @param reset YES in case reset, NO otherwise
 @return Updated fields from the last reset
 */
-(MeetingSeqChanges)getUpdatedFileds:(BOOL)reset;

/**
 Favorite ID
 */
@property (readonly) SptIMFavoriteID favorityID;
/**
 Room data associated to the meeting sequence
 */
@property (readonly) ISptRoomData *room;
@end


/**
 @class SptSchManageParticipants
 Manage meeting participants
 */
@interface SptSchManageParticipants : NSObject
/**
 Create with meeting sequence

 @param seqID Meeting sequence
 @return created instance
 */
+(instancetype) withSchMeetingSequenceID:(SptMeetingSeqID)seqID;
/**
 Add contacts

 @param contactID Contact ID
 @return YES in case added, NO otherwise
 */
-(BOOL)addIMParticipant:(TSptIMContactID)contactID;
/**
 Add participant by email

 @param emailAddress email address
 @return YES in case added, NO otherwise
 */
-(BOOL)addIEmailParticipant:(NSString *)emailAddress;

/**
 Add COLLABORATE Pro room

 @param contactID COLLABORATE Pro room contact ID
 @return YES in case added, NO otherwise
 */
-(BOOL)addCollaborateRoom:(TSptIMContactID)contactID;
/**
 Remove a participant

 @param participant Participant data
 @return YES in case removed, NO otherwise
 */
-(BOOL)removeParticipant:(SptSchParticipant *)participant;
@end


/**
 @class SptSchManageProperties
 Manage meeting sequence properties
 */
@interface SptSchManageProperties : NSObject
/**
 Create instance with data

 @param seqID Meeting sequence ID
 @param meetingProperties Meeting sequence properties to set
 @param password Meeting sequence password, nil in case no password
 @return Created instance
 */
+(instancetype) withData:(SptMeetingSeqID)seqID
              properties:(MeetingSequenceProperties)meetingProperties
                password:(NSString *)password;
@end



/**
 @class SptSchManageFiles
 Manage Meeting files
 */
@interface SptSchManageFiles : NSObject
/**
 Create instamce with meeting

 @param seqID Meeting sequence ID
 @param meetingID Meeting ID
 @return created instance
 */
+(instancetype) withSchMeeting:(SptMeetingSeqID)seqID
                       meeting:(SptMeetingID)meetingID;
/**
 Add file

 @param fullPath File path
 @return YES in case added, NO otherwise
 */
-(BOOL)addFile:(NSURL *)fullPath;

/**
 Remove a file

 @param fileID File ID
 @return YES in case removed, NO otherwise
 */
-(BOOL)removeFile:(SptFileID)fileID;

@end


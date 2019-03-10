/**
  ISptCallExt.h
  SptIMCoreIOS
  @framework COLLABORATESapce

  Copyright © 2019 ClearOne Inc. All rights reserved.
  @charset utf-8
*/

#import "ISptTypes.h"
#import "ISptIMContactExt.h"
#import "ISptIMRoomExt.h"
#import "ISptFileExt.h"
#import "ISptAnnotationData.h"
#import "ISptFileExt.h"

@class SptSchMeeting;
@class SptSchMeetingSequence;



/**
 @class SptCallChat
 Call chat data
 */
@interface SptCallChat : NSObject


/**
 Get event by its ID

 @param eventID Event ID
 @return Event data, nil in case not found
 */
-(ISptEventData *)getEventByID:(SptIMEventID)eventID;

/**
 Get unread events

 @param reset YES in case reset unread events, NO otherwise
 @return Number of unread events
 */
-(NSUInteger) getPendingEvents:(BOOL)reset;

/**
 Get a collection with all files attached to the chat

 @return Collection with all files attached to the chat
 */
-(SptFileCollection *)getFiles;

/**
 Get an NSArray of events after an event
 
 @param eventID Event ID to get events after it
 @return NSArray of ISptEventData with events after eventID
 */
-(NSArray *)getEventsFrom:(SptIMEventID)eventID;

/**
 Call ID
 */
@property (readonly) SptCallID callID;

/**
 In case of private chat, call participant ID
 */
@property (readonly) SptCallParticipantID callParticipantID;

/**
 Room ID in case it is an ISptRoomData
 */
@property (readonly) SptIMRoomID roomID;

/**
 Is it a public chat
 */
@property (readonly) BOOL isPublicChat;

/**
 Get room data in case it is an ISptRoomData
 */
@property (readonly) ISptRoomData *roomData;

/**
 Get an NSArray of ISptEventData with all events in the room
 */
@property (readonly) NSArray *events;

/**
 Get a dictionary with alll events sorted by time separated by days
 */
@property (readonly) NSDictionary *datedEvents;

@end


/**
 @class SptCallChatEvent
 Chat event data
 */
@interface SptCallChatEvent : NSObject
/**
 Call chat data
 */
@property (readonly) SptCallChat *callChat;
/**
 Caqll chat event
 */
@property (readonly) ISptEventData *callChatEvent;
@end

/**
 Call participant services
 */
@interface ISptCallParticipantServices : NSObject

/**
 Service state

 - kSptServiceDeActive: Service deactive
 - kSptServiceActive: Service active
 - kSptServiceForbidden: Service forbidden in session
 - kSptServiceCanManage: I can manage this service
 */
typedef NS_OPTIONS(NSUInteger, ParticipantService)
{
    kSptServiceDeActive     =   0,
    kSptServiceActive       =   1 << 0,
    kSptServiceForbidden    =   1 << 1,
    kSptServiceCanManage    =   1 << 2,
};

/**
 Can I send moderation to this participant
 */
@property (readonly) bool canGiveModeration;
/**
 Audio service state
 */
@property (readonly) ParticipantService audioService;
/**
 Video service state
 */
@property (readonly) ParticipantService videoService;
/**
 Sharing service state
 */
@property (readonly) ParticipantService sharingService;
/**
 Remote control service state
 */
@property (readonly) ParticipantService remoteControlService;
/**
 Text service state
 */
@property (readonly) ParticipantService textService;
/**
 Whiteboard/annotation service state
 */
@property (readonly) ParticipantService whiteboardService;
/**
 File transfer service state
 */
@property (readonly) ParticipantService fileTransferService;
@end


/**
 @class ISptCallParticipantData
 Call participant data
 */
@interface ISptCallParticipantData : NSObject<SptContactBase>

/**
 Call participant state

 - kCallPartStateCreating: Participant is creating the call
 - kCallPartStateInvited: Participant is invited to the call
 - kCallPartStateRinging: Participant is ringing
 - kCallPartStateAccepted: Participant accepted the call
 - kCallPartStateConnecting: Participant is connecting to the media server
 - kCallPartStateConnected: Participant is connected to the call
 - kCallPartStateDisconnected: Participant is disconnected
 - kCallPartStateHangUp: Participant was expelled by host
 - kCallPartStateNoAnswer: Participant disconnected. No answer.
 - kCallPartStateDecline: Participant disconnected. Call declibed.
 - kCallPartStateBusy: Participant disconnected. Participant busy in other call.
 - kCallPartStateError: Participant disconnected. Error in call.
 - kCallPartStateUnknown: Unknown state.
 */
typedef NS_ENUM(NSUInteger, eCallParticipantState)
{
    kCallPartStateCreating = 0,
    kCallPartStateInvited,
    kCallPartStateRinging,
    kCallPartStateAccepted,
    kCallPartStateConnecting,
    kCallPartStateReconnecting,
    kCallPartStateConnected,
    kCallPartStateDisconnected,
    kCallPartStateHangUp,
    kCallPartStateNoAnswer,
    kCallPartStateDecline,
    kCallPartStateBusy,
    kCallPartStateError,
    kCallPartStateUnknown
};

/**
 Participant role

 - kSptParticipantRoleModerator: Participant is moderator
 - kSptParticipantRoleParticipant: Normal participant
 */
typedef NS_ENUM(NSUInteger, eParticipantRole)
{
    kSptParticipantRoleModerator    =   0,
    kSptParticipantRoleParticipant  =   1
};

/**
 End point type

 - kSptEndPointTypeUnknown: Unknown type
 - kSptEndPointTypePSTN: PSTN phone number
 - kSptEndPointTypeSIP: SIP endpoint
 - kSptEndPointTypeH323: H.323 endpoint
 */
typedef NS_ENUM(NSUInteger, eEndPointType)
{
    kSptEndPointTypeUnknown = 0,
    kSptEndPointTypePSTN    = 1,
    kSptEndPointTypeSIP     = 2,
    kSptEndPointTypeH323    = 3
};

/**
 Call ID
 */
@property (readonly) SptCallID callID;
/**
 Call participant ID
 */
@property (readonly) SptCallParticipantID callParticipantID;
/**
 IS it an IM contact
 */
@property (readonly) BOOL isIMContact;
/**
 In case it is an IM contact, contact data
 */
@property (readonly) ISptContactData *imContact;
/**
 In case of endpoind. endpoint address
 */
@property (readonly) NSString *endPointAddress;
/**
 Endpoint type
 */
@property (readonly) eEndPointType endPointType;
/**
 Participant role
 */
@property (readonly) eParticipantRole role;
/**
 Participant state
 */
@property (readonly) eCallParticipantState state;
/**
 Participant current service state
 */
@property (readonly) ISptCallParticipantServices* services;

/**
 Is participant speaking
 */
@property (readonly) BOOL isSpeaking;
/**
 Can receive chat messages
 */
@property (readonly) BOOL canReciveChat;
/**
 Is recording call/meeting
 */
@property (readonly) BOOL isRecording;
/**
 Can receive DTMF codes
 */
@property (readonly) BOOL canReciveDTMF;
/**
 DTMF codes sent to this participant
 */
@property (readonly) NSString *dtmfCodesSent;

@end

/**
 @protocol SptMediaView
 Set paint area in a view
 */
@protocol SptMediaView

/**
 View
 */
@property (readonly) UIView *view;

/**
 Change in the state of the whiteboard
 @param bActive true in case whiteboard is active, false deactive
 */
-(void)onWhiteboardState:(bool)bActive;

/**
 Set a frame
 */
-(void)setNewFrame;

/**
 Can I scroll
 */
@property (readonly) BOOL canScroll;

/**
 Can I annotate
 */
@property (readonly) BOOL canAnnotate;

/**
 Enable/disable annotation
 */
@property (assign, nonatomic) BOOL enableAnnotation;

@end

/**
 Call stream data
 */
@interface ISptCallStream : NSObject

/**
 Type of stream

 - eStreamTypeUnknown: Unknown type
 - eStreamTypeAudio: Audio
 - eStreamTypeVideo: Video
 - eStreamTypeSharing: Sharing
 - eStreamTypeWhiteboard: Whiteboard
 */
typedef NS_ENUM(NSUInteger, eStreamType)
{
    eStreamTypeUnknown       = 0,
    eStreamTypeAudio         = 1,
    eStreamTypeVideo         = 2,
    eStreamTypeSharing       = 3,
    eStreamTypeWhiteboard    = 4
};

/**
 Participant ID that is generating this stream
 */
@property (readonly) SptCallParticipantID participantID;
/**
 Stream ID
 */
@property (readonly) SptCallStreamDataID  streamID;
/**
 Stream type
 */
@property (readonly) eStreamType streamType;
/**
 Is speaking the participant who is generating this stream
 */
@property (readonly) BOOL isSpeaking;
/**
 Available PTZ control
 */
@property (readonly) BOOL availablePTZControl;
/**
 This stream is flag as important
 */
@property (readonly) BOOL isSharedVideo;
/**
 This stream is an application/desktop sharing that I can remote control
 */
@property (readonly) BOOL isSharingControllable;
/**
 IS it a media file shared by me
 */
@property (readonly) BOOL isMediaFile;
/**
 View where stream will be painted
 */
@property (readonly) UIView<SptMediaView>*view;
/**
 Size of the stream in pixels
 */
@property (readonly) CGSize mediaSize;

/**
 Has an annotation active
 */
@property (readonly) bool hasAnnotation;
/**
 In casae it has an annotation active or it is a whiteboard stream, get annotation data

 @return Annotation data
 */
-(SptAnnotation *)getAnnotationData;

@end

/**
 @class SptCallRequest
 Call request
 */
@interface SptCallRequest : NSObject

/**
 Call request typr

 - eCallRequestUnknown: Unknown type
 - eCallRequestAcceptModeration: Modetator is transferring moderation to you
 - eCallRequestTransferModeration: You are the moderator and you are transferring moderation
 - eCallRequestAcceptRemoteControl: A user has requested remote control
 - eCallRequestShareApplication: You have sharing service active, set view to share
 */
typedef NS_ENUM(NSUInteger, eCallRequestType)
{
    eCallRequestUnknown                  = 0,
    eCallRequestAcceptModeration         = 1,
    eCallRequestTransferModeration       = 2,
    eCallRequestAcceptRemoteControl      = 3,
    eCallRequestShareApplication         = 4
};

/**
 Call request state

 - eCallRequestStateUnknown: Unknown state
 - eCallRequestStatePending: WAiting for your answer
 - eCallRequestStateTimeOut: Time out
 - eCallRequestStateCancel: Cancelled
 - eCallRequestStateAccepted: Accepted
 - eCallRequestStateDeclined: Devlined
 - eCallRequestStateWaitingAnswer: Waiting for remote contact answer
 - eCallRequestStateError: error
 */
typedef NS_ENUM(NSUInteger, eCallRequestState)
{
    eCallRequestStateUnknown        = 0,
    eCallRequestStatePending        = 1,
    eCallRequestStateTimeOut        = 2,
    eCallRequestStateCancel         = 3,
    eCallRequestStateAccepted       = 4,
    eCallRequestStateDeclined       = 5,
    eCallRequestStateWaitingAnswer  = 6,
    eCallRequestStateError          = 7,
};

/**
 Type of call request
 */
@property (readonly) eCallRequestType type;
/**
 Call ID
 */
@property (readonly) SptCallID callID;
/**
 Call participant ID who send request
 */
@property (readonly) ISptCallParticipantData *callParticipant;
/**
 Call request state
 */
@property (readonly) eCallRequestState state;

@end

/**
 @class SptCallStatisticsPackets
 Call packet statistics
 */
@interface SptCallStatisticsPackets : NSObject

/**
 Number of video packets lost
 */
@property (readonly) NSUInteger videoPackectLost;
/**
 Number of video packets recovered
 */
@property (readonly) NSUInteger videoPackectRecover;
/**
 Percent of video packets lost
 */
@property (readonly) float videoPacketLostPercent;

/**
 Audio packets aout of order
 */
@property (readonly) NSUInteger audioPacketOutOfOrder;
/**
 Audio packets lost
 */
@property (readonly) NSUInteger audioPacketLost;
/**
 Percent of audio packets lost
 */
@property (readonly) float audioPacketLostPercent;

@end

/**
 @class SptCallStatistics
 Call statistics
 */
@interface SptCallStatistics : NSObject

/**
 Get packet statistics

 @param bReset YES in case reset, NO otherwise
 @return Packet statistics data
 */
-(SptCallStatisticsPackets *)getPacketStatistics:(BOOL)bReset;

/**
 Send bandwisth in kbps
 */
@property (readonly) NSUInteger sendBandWidth;

/**
 Received bandwidth in kbps
 */
@property (readonly) NSUInteger downloadBandWidth;


/**
 An NSArray of NSNumber with the last values
 */
@property (readonly) NSArray *uploadBandwidthLastValues;
/**
 An NSArray of NSNumber with the last values
 */
@property (readonly) NSArray *downloadBandwidthLastValues;


/**
 Total number of bytes sent during the call
 */
@property (readonly) NSUInteger totalBytesUpload;
/**
 Total number of bytes received during the call
 */
@property (readonly) NSUInteger totalBytesDownload;



@end


/**
 @class SptCallRecommendedPaintList
 Recommended painting list
 */
@interface SptCallRecommendedPaintList : NSObject

/**
 Get first position changed in the list since last reset

 @param reset Reset data
 @return First position changed in the list since lst reset
 */
-(NSUInteger)getFirstPositionChanged:(BOOL)reset;
/**
 Call ID
 */
@property (readonly) SptCallID callID;
/**
 NSArray of ISptCallStream sorted by priority
 */
@property (readonly) NSArray *sortedList;
@end


/**
 @class ISptCall
 Call Data
 */
@interface ISptCall : NSObject

/**
 Type of call

 - kCallTypeUnknown: Unknown type of call
 - kCallTypeAudio: Audio call
 - kCallTypeVideo: Video call
 */
typedef NS_ENUM(NSUInteger, eCallType)
{
    kCallTypeUnknown    = 0,
    kCallTypeAudio      = 1,
    kCallTypeVideo      = 2
};

/**
 Call state

 - kCallStateUnknown: Call state Unknown
 - kCallStateCreating: Call state creating. Local user is starting the call
 - kCallStateRinging: Call state ringing. Incoming call
 - kCallStateAccepted: Call state accepted. In an incoming call, local user has answered the call
 - kCallStateConnecting: Call state connecting. Connecting to the media server
 - kCallStateWaitingParticipants: Call state waiting participants. You are the caller and you are wainting for other participants answer the call
 - kCallStateConnected: Call state connected. You are connected to the call
 - kCallStateConnectedInOtherDevice: Call state connected in other device, you have answered the call from other device
 - kCallStateDisconnecting: Call state disconnecting. You are disconnecting
 - kCallStateDisconnected: Call state disconnected
 - kCallStateRejected: Call state rejected. You has rejected the call
 - kCallStateError: Call state error. Error in call
 */
typedef NS_ENUM(NSUInteger, eCallState)
{
    kCallStateUnknown = 0,
    kCallStateCreating,
    kCallStateRinging,
    kCallStateAccepted,
    kCallStateConnecting,
    kCallStateWaitingParticipants,
    kCallStateReconnecting,
    kCallStateConnected,
    kCallStateConnectedInOtherDevice,
    kCallStateDisconnecting,
    kCallStateDisconnected,
    kCallStateRejected,
    kCallStateError
};

/**
 Call error

 - kSptCallErrorNoError: No error detected in call
 - kSptCallErrorGeneric: Generic error, no additional data
 - kSptCallErrorInvalidPassword: Invalid password
 - kSptCallErrorInvalidParams: Invalid params
 - kSptCallErrorModeratorNotConnected: Moderator not connected in meeting and is required to start it
 - kSptCallErrorSessionID: Session ID not found
 - kSptCallErrorServer: Server not found
 - kSptCallErrorSessionFull: The session is full
 - kSptCallErrorCredentialsRequired: Session needs cretentials to login
 - kSptCallErrorNoLicence: No available licence
 - kSptCallErrorNameInUse: Name in use, try agin with other name
 - kSptCallErrorAlreadyConnected: You are already connected in other meeting
 - kSptCallErrorModeratorInSession: Connection error, There is already a moderator connected to the sessionhe session in you language
 - kSptCallErrorNotAuthorized: You are not authorized to get into this meeting
 - kSptCallErrorMeetingTime: Meeting is not active at current time
 - kSptCallErrorNetwork: Network error
 - kSptCallErrorModeratorPassword: You are the first user in session and you must be moderator so password is required
 - kSptCallErrorVersion: Your client version is out of date and cannot be used to connect.
 - kSptCallErrorExpired: Meeting is finished
 - kSptCallErrorHostInUse: Your host is in use in other meeting or call
 - kSptCallErrorTempUnavailable: Meeting temporaly unavailable
 */
typedef NS_ENUM(NSUInteger, eCallError)
{
    kSptCallErrorNoError                =   0,
    kSptCallErrorGeneric                =   1,
    kSptCallErrorInvalidPassword        =   2,
    kSptCallErrorInvalidParams          =   3,
    kSptCallErrorModeratorNotConnected  =   4,
    kSptCallErrorSessionID              =   5,
    kSptCallErrorServer                 =   6,
    kSptCallErrorSessionFull            =   7,
    kSptCallErrorCredentialsRequired    =   8,
    kSptCallErrorNoLicence              =   9,
    kSptCallErrorNameInUse              =   10,
    kSptCallErrorAlreadyConnected       =   11,
    kSptCallErrorModeratorInSession     =   12,
    kSptCallErrorNotAuthorized          =   13,
    kSptCallErrorMeetingTime            =   14,
    kSptCallErrorNetwork                =   15,
    kSptCallErrorModeratorPassword      =   16,
    kSptCallErrorVersion                =   17,
    kSptCallErrorExpired                =   18,
    kSptCallErrorHostInUse              =   19,
    kSptCallErrorTempUnavailable        =   20
};

/**
 Call service

 - eCallServiceText: Text service
 - eCallServiceAudio: Audio service
 - eCallServiceVideo: Video service
 - eCallServiceSharing: Sharing service
 - eCallServiceControl: Remote control service
 - eCallServiceFile: File transfer service
 - eCallServiceWhiteboard: Whiteboard/annotation service
 */
typedef NS_ENUM(NSUInteger, eCallService)
{
    eCallServiceText         = 0,
    eCallServiceAudio        = 1,
    eCallServiceVideo        = 2,
    eCallServiceSharing      = 3,
    eCallServiceControl      = 4,
    eCallServiceFile         = 5,
    eCallServiceWhiteboard   = 6
};

/**
 Cakk service flag

 - kSptCallServiceUnknown: Unkown service
 - kSptCallServiceText: Text service
 - kSptCallServiceAudio: Audio service
 - kSptCallServiceVideo: Video service
 - kSptCallServiceSharing: Sharing service
 - kSptCallServiceControl: Remote control service
 - kSptCallServiceFile: File transfer service
 - kSptCallServiceWhiteboard: whiteboard /annotation service
 */
typedef NS_OPTIONS(NSUInteger, CallService)
{
    kSptCallServiceUnknown      = 0,
    kSptCallServiceText         = 1 << 0,
    kSptCallServiceAudio        = 1 << 1,
    kSptCallServiceVideo        = 1 << 2,
    kSptCallServiceSharing      = 1 << 3,
    kSptCallServiceControl      = 1 << 4,
    kSptCallServiceFile         = 1 << 5,
    kSptCallServiceWhiteboard   = 1 << 6
};

/**
 Call context

 - kCallContextUnnown: Unknown call context
 - kCallContextChat: Chat call context
 - kCallContextChannel: Call started over a channel
 - kCallContextMeeting: It is a meeting
 */
typedef NS_ENUM(NSUInteger, CallContext)
{
    kCallContextUnnown  = 0,
    kCallContextChat    = 1,
    kCallContextChannel = 2,
    kCallContextMeeting = 3
};

/**
 Get participant by ID

 @param participantID Call participant ID
 @return Participant data
 */
-(ISptCallParticipantData *)getParticipantByID:(SptCallParticipantID)participantID;
/**
 Get active stream by ID

 @param tStreamID Stream ID
 @return Stream data
 */
-(ISptCallStream *)getCallActiveStreamByID:(SptCallStreamDataID) tStreamID;
/**
 Get the list of participants

 @param currentlyInCall YES in case you want only participants currently with the call active, NO include disconnected participantsa
 @return NSArray of ISptCallParticipantData with the requested participants
 */
-(NSArray *) getParticipants:(BOOL)currentlyInCall;
/**
 Get participant with an spepecific service active

 @param eService Service to check
 @return NSArray of ISptCallParticipantData with the requested participants
 */
-(NSArray *) getParticipantsWithActiveService:(eCallService)eService;
/**
 Is a service active in the call

 @param service Service to check
 @return YES in case it is active, NO otherwise
 */
-(BOOL)isServiceActiveInCall:(eCallService)service;
/**
 Get call request by type

 @param eType Type to retrieve
 @return Call request data, nil in case not found
 */
-(SptCallRequest *)getCallRequestByType:(eCallRequestType)eType;

/**
 Get call chat by room ID

 @param roomID Room ID to retrieve call chat
 @return Call chat data in case found, nil otherwise
 */
-(SptCallChat*)getCallChatByRoomID:(SptIMRoomID)roomID;

/**
 Call recording state

 - kRecordingStateNotRecordig: No recorded
 - kRecordingStateRecordigInMP4: Recording in MP4 format locally
 - kRecordingStateRecordigInWONF: Recording in WCONF format locally
 - kRecordingStateRecordigInAtServer: Recording at server
 - kRecordingStateRecordigInOther: Recording by other contact
 */
typedef NS_OPTIONS(NSUInteger, RecordingState)
{
    kRecordingStateNotRecordig          = 0,
    kRecordingStateRecordigInMP4        = 1 << 0,
    kRecordingStateRecordigInWONF       = 1 << 1,
    kRecordingStateRecordigInAtServer   = 1 << 2,
    kRecordingStateRecordigInOther      = 1 << 3
};


/**
 Call ID
 */
@property (readonly) SptCallID callID;

/**
 Call started type, it was started with audio or video
 */
@property (readonly) eCallType callStartedType;

/**
 Call context
 */
@property (readonly) CallContext callContext;

/**
 Call time from call started
 */
@property (readonly) NSDateComponents *callTime;

/**
 Call error
 */
@property (readonly) eCallError callError;

/**
 Call state
 */
@property (readonly) eCallState callState;

/**
 Can I invite new participants
 */
@property (readonly) BOOL canInvite;

/**
 Maximum number of participants you can invite to this call
 */
@property (readonly) NSUInteger maxParticipantsICanInvite;


/**
 Available call recording
 
 - kCanRecordNoAllowed: Call recording not allowed
 - kCanRecordLocally: Call recording allowed locally
 - kCanRecordAtServer: Call recording allowed at server
 */
typedef NS_OPTIONS(NSUInteger, CanRecord)
{
    kCanRecordNoAllowed             = 0,
    kCanRecordLocally               = 1 << 0,
    kCanRecordAtServer              = 1 << 2
};

/**
 Can I record the call /meeting
 */
@property (readonly) CanRecord canIRecord;

/**
 Am I moderator
 */
@property (readonly) BOOL amIModerator;

/**
 Can I expell a participant
 */
@property (readonly) BOOL canIHangParticipant;

/**
 Moderator call participant
 */
@property (readonly) ISptCallParticipantData* moderator;

/**
 NSArray of ISptCallParticipantData with the list of speaking participants sorted by last main speaker
 */
@property (readonly) NSArray *sSpeakingParticipantList;

/**
 NSArray of ISptCallStream with active streams
 */
@property (readonly) NSArray *callActiveStreams;

/**
 Recommended painting list
 */
@property (readonly) SptCallRecommendedPaintList *callRecommendedPaintList;

/**
 NSArray with hand rise request
 */
@property (readonly) NSArray *callHandRiseRequestCollection;

/**
 NSArray of SptCallRequest with call requests
 */
@property (readonly) NSArray *callRequestCollection;

/**
 Recording state
 */
@property (readonly) RecordingState recordingState;

/**
 NSArray of ISptCallParticipantData with the list of participants that are recording the call
 */
@property (readonly) NSArray *recordingParticipants;

/**
 Get the list of contacts from your contact directory that can be invited to the call
 @param eFilter Bit combination with the sort and filter contacts
 @result NSArray of ISptContactData with  the list of contacts from your contact directory that can be invited to the call
 */
-(NSArray *)invitableContacts:(eContactFilterSort)eFilter;

/**
 Call statistics
 */
@property (readonly) SptCallStatistics *callStatistics;

/**
 Default manage services, Services that any contact can active by default
 */
@property (readonly) CallService defaultManageServices;

/**
 Chat is available
 */
@property (readonly) BOOL chatAvailable;

/**
 Current call chat
 */
@property (readonly) SptCallChat *callChat;

/**
 Can I finish call for all participants
 */
@property (readonly) BOOL canIEndForAll;

/**
 In case it is a meeting, meeting data
 */
@property (readonly) SptSchMeeting *meeting;

/**
 In case it is a meeting, meeting sequence data
 */
@property (readonly) SptSchMeetingSequence *meetingSequence;

/**
 Call connectivity

 - kConnectivityGood: Call connectivity good
 - kConnectivityBad: Call connectivity bad
 - kConnectivityVeryBad: Call connectivity very bad
 */
typedef NS_ENUM(NSUInteger, CallConnectivity)
{
    kConnectivityGood    = 0,
    kConnectivityBad     = 1,
    kConnectivityVeryBad = 2
};

/**
 Call connectivity
 */
@property (readonly) CallConnectivity callConnectivity;

/**
 Unique call identifier
 */
@property (readonly) NSString *callIdentifier;

@end


/****************************************************************************************************************************************************/
/**
 Join meeting data, legacy mode
 */
@interface ISptJoinMeetingData : NSObject
/**
 Server address
 */
@property (readwrite) NSString *server;
/**
 Login
 */
@property (readwrite) NSString *login;
/**
 Password
 */
@property (readwrite) NSString *password;
/**
 Session ID
 */
@property (readwrite) NSString *sessionID;
@end

/****************************************************************************************************************************************************/


/**
 Make call
 */
@interface ISptMakeCall : NSObject
/**
 Make a call over a room

 @param roomID Room ID
 @param callType How you are going to connect to the meeting
 @return created instance
 */
+(instancetype)makeCallWithRoom:(SptIMRoomID)roomID
                        calltye:(eCallType) callType;

/**
 Create an empty make call instance

 @param callType How you will connect to the call
 @return created instance
 */
+(instancetype)makeCallEmpty:(eCallType) callType;


@end


/**
 @class SptCallHistory
 Call history
 */
@interface SptCallHistory : NSObject

/**
 Call ID
 */
@property (readonly) SptCallID callID;

/**
 Call direction

 - kSptUnknownCallDirection: Unknown call direction
 - kSptOutgoingCall: Outgoing call
 - kSptIncommingCall: Incomming call
 */
typedef NS_ENUM(NSUInteger, eCallDirection)
{
    kSptUnknownCallDirection = 0,
    kSptOutgoingCall = 1,
    kSptIncommingCall = 2
};

/**
 Call direction
 */
@property (readonly) eCallDirection callDirection;

/**
 Call established

 - kCallEstablishUnknown: Unknown
 - kCallNoAnswered: Call no answered, you were called
 - kCallMissed: Call wissed, you didn't answer
 - kCallEstablished: Call established
 - kCallError: call error
 */
typedef NS_ENUM(NSUInteger, eCallEstablished)
{
    kCallEstablishUnknown = 0,
    kCallNoAnswered       = 1,
    kCallMissed           = 2,
    kCallEstablished      = 3,
    kCallError            = 4
};

/**
 Call established state
 */
@property (readonly)  eCallEstablished callEstablished;


/**
 NSArray of ISptCallParticipantData with the participants
 */
@property (readonly)  NSArray *participants;

/**
 Date of the call
 */
@property (readonly)  NSDate  *callDate;
/**
 Duration of the call
 */
@property (readonly)  NSDateComponents *duration;
/**
 Chat room associated to the call in case it still exists.
 */
@property (readonly)  ISptRoomData *chatRoom;

/**
 Get display name
 In case of One 2 one call the name of ther other participant, in case of multi call the name of the participants separated by colom,
 In case of channel, the name of the channel
 */
@property (readonly) NSString *displayName;

/**
 In case of one 2 one call, get the other participant
 */
@property (readonly) ISptCallParticipantData *one2OneParticipant;
@end


/**
 Call history collection
 */
@interface SptCallHistoryCollection : NSObject

/**
 Total number of calls
 */
@property (readonly) NSUInteger totalNumCalls;
/**
 Number of calls currently loaded in memory
 */
@property (readonly) NSUInteger loadedNumCalls;
/**
 Get call by position

 @param position Position to retrieve call data starting at 0
 @return Call data
 */
-(SptCallHistory *) getCallByPosition:(NSUInteger)position;
/**
 Get call by historical ID

 @param tCallID Call ID
 @return Call data
 */
-(SptCallHistory *) getCallByID:(SptCallID)tCallID;

/**
 Get the position of the call in the list

 @param callID Call ID
 @return Position of the call in the list -1 in case not found
 */
-(NSInteger)getCallPositionByID:(SptCallID)callID;
/**
 Get an NSArray with the calls added since last reset

 @param reset Reset list
 @return NSArray with the calls added from the last reset
 */
-(NSArray *)getLastCallAdded:(BOOL)reset;
/**
 Can I load more calls in memory
 */
@property (readonly) BOOL canILoadMore;

@end



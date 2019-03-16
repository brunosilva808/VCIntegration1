//
//  CollaborateUtils.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "CollaborateUtils.h"

@implementation CollaborateUtils

+(CollaborateUtils*)Instance{
    /**
     Here we maintain an static object for this class
     */
    static CollaborateUtils *instance = nil;
    if ( instance == nil )
        instance = [[CollaborateUtils alloc]init];

    return instance;
}

-(id)init{
    self = [super init];

    //Here we initialize collaborate SDK object
    self.api = [ISpontaniaIMApi spontaniaIMApiWithDelegate:self];

    return self;
}

- (void)onConnected {
    //User Logged into Collaborate system
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.loginCallback != nil ){
            [self.loginCallback onLoginResult:YES error:-1];
        }
    });
}

- (void)onConnectionError:(eSptConnectionResult)eResult {
    //User Logged into Collaborate system
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.loginCallback != nil ){
            [self.loginCallback onLoginResult:NO error:-1];
        }
    });

}

- (void)onGetTokenDataResult:(SptTokenDataResult *)tokenDataResult{
    //User Logged into Collaborate system
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.loginCallback != nil ){
            [self.loginCallback onGetTokenDataResult:tokenDataResult];
        }
    });
}


-(void)updateRoster{
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.contactsCallback != nil ){
            [self.contactsCallback onContactListModified];
        }
    });
}

- (void)onRosterList:(NSArray *)rosterList {
    //Roster is available
    [self updateRoster];
}


- (void)onContactRosterAdded:(ISptContactData *)contactData {
    //A new contact has been removed from the list
    [self updateRoster];
}

- (void)onContactRosterRemoved:(ISptContactData *)contactData {
    //A new contact has been added to the list
    [self updateRoster];
}

- (void)onContactUpdated:(ISptContactData *)contactData {
    //User Logged into Collaborate system
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.contactsCallback != nil ){
            [self.contactsCallback onContactUpdated:contactData];
        }
    });
}


-(void)setCurrentCall:(ISptCall *)currentCall{
    if ( (_currentCall != nil && currentCall == nil )
        || (_currentCall == nil && currentCall != nil ) ){
        __block ISptCall *oldCall = _currentCall;
        _currentCall = currentCall;
        //User Logged into Collaborate system
        dispatch_async( dispatch_get_main_queue(), ^(){
            if ( self.callManagerCallback != nil ){
                if ( currentCall != nil ){
                    [self.callManagerCallback onNewCall:currentCall incoming:(currentCall.callState==kCallStateRinging) ];
                }else{
                    [self.callManagerCallback onCallFinished:oldCall];
                }
            }
        });
    }
}

- (void)onCallEventConnected:(SptCallID)callID calldata:(ISptCall *)callDataObj {

}

- (void)onCallEventDisconnected:(SptCallID)callID calldata:(ISptCall *)callDataObj {
    //A call has been finished
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.callManagerCallback != nil ){
            [self.callManagerCallback onCallFinished:callDataObj];
        }
    });
}

- (void)onCallEventIncomingCall:(SptCallID)callID calldata:(ISptCall *)callDataObj {
    //A new incoming call is received
    self.currentCall = callDataObj;
}

- (void)onCallEventStateUpdated:(SptCallID)callID calldata:(ISptCall *)callDataObj {
    if ( _currentCall == nil)
    {
        switch (callDataObj.callState) {

            case kCallStateUnknown:
            case kCallStateWaitingParticipants:
            case kCallStateReconnecting:
            case kCallStateConnected:
            case kCallStateConnectedInOtherDevice:
            case kCallStateDisconnecting:
            case kCallStateDisconnected:
            case kCallStateRejected:
            case kCallStateError:
                return;
                break;
            case kCallStateCreating:
            case kCallStateRinging:
            case kCallStateConnecting:
            case kCallStateAccepted:
                self.currentCall = callDataObj;
                break;

        }
    }

    if ( _currentCall != nil && _currentCall.callID == callID ){
        switch ( callDataObj.callState ){
            case kCallStateConnected:{
                //Just informs that the current call is being connected
                dispatch_async( dispatch_get_main_queue(), ^(){
                    if ( self.callManagerCallback != nil ){
                        [self.callManagerCallback onCallEstablished:callDataObj];
                    }
                });
            }break;

            case kCallStateConnectedInOtherDevice:
            case kCallStateDisconnecting:
            case kCallStateDisconnected:
            case kCallStateRejected:
            case kCallStateError:
                self.currentCall = nil;
                break;
            default:
                break;
        }
    }
}

- (void)onCallEventStreamStarted:(SptCallID)callID streamData:(ISptCallStream *)streamObj {
    if ( callID == _currentCall.callID ){
        //A new service streming has started
        dispatch_async( dispatch_get_main_queue(), ^(){
            if ( self.callCallback != nil ){
                [self.callCallback onStreamingStarted:streamObj];
                if ( streamObj.streamType == eStreamTypeWhiteboard )
                    [self.callCallback onStreamAnnotationEnabled:streamObj enabled:YES];
            }
        });
    }
}

- (void)onCallEventStreamStopped:(SptCallID)callID streamData:(ISptCallStream *)streamObj {
    if ( callID == _currentCall.callID ){
        //A new service streming has finished
        dispatch_async( dispatch_get_main_queue(), ^(){
            if ( self.callCallback != nil ){
                if ( streamObj.streamType == eStreamTypeWhiteboard )
                    [self.callCallback onStreamAnnotationEnabled:streamObj enabled:NO];
                [self.callCallback onStreamingStoped:streamObj];
            }
        });
    }
}


- (void)onCallEventAnnotationOverStreamStarted:(SptCallID)callID streamData:(ISptCallStream *)streamObj {
    if ( callID == _currentCall.callID ){
        //A new service streming has finished
        dispatch_async( dispatch_get_main_queue(), ^(){
            if ( self.callCallback != nil ){
                [self.callCallback onStreamAnnotationEnabled:streamObj enabled:YES];
            }
        });
    }
}

- (void)onCallEventAnnotationOverStreamStoped:(SptCallID)callID streamData:(ISptCallStream *)streamObj {
    if ( callID == _currentCall.callID ){
        //A new service streming has finished
        dispatch_async( dispatch_get_main_queue(), ^(){
            if ( self.callCallback != nil ){
                [self.callCallback onStreamAnnotationEnabled:streamObj enabled:NO];
            }
        });
    }
}


- (void)onCallEventStreamNewFrame:(SptCallID)callID streamData:(ISptCallStream *)streamObj {
}

- (void)onCallRequestUpdated:(SptCallID)callID request:(SptCallRequest *)callRequest {
    if ( callID == _currentCall.callID ){
        //A new service streming has finished
        dispatch_async( dispatch_get_main_queue(), ^(){
            if ( self.callCallback != nil ){
                [self.callCallback onCallRequestUpdated:callRequest];
            }
        });
    }
}


- (void)onEventChatReceived:(NSNumber *)contactID message:(ISptEventData *)eventData {
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.chatsCallback != nil ){
            [self.chatsCallback onChatEventReceived:eventData];
        }
    });
}

- (void)onEventChatSent:(ISptEventData *)eventData {
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.chatsCallback != nil ){
            [self.chatsCallback onChatEventSent:eventData];
        }
    });
}

- (void)onRoomCreated:(NSNumber *)contactID roomData:(ISptRoomData *)roomCreatedData {
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.chatsCallback != nil ){
            [self.chatsCallback onChatListModified];
        }
    });
}

- (void)onRoomJoined:(NSNumber *)contactID roomData:(ISptRoomData *)roomJoinedData {
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.chatsCallback != nil ){
            [self.chatsCallback onChatListModified];
        }
    });
}

- (void)onRoomLeft:(NSNumber *)contactID roomData:(ISptRoomData *)roomJoinedData {
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.chatsCallback != nil ){
            [self.chatsCallback onChatListModified];
        }
    });
}


- (void)onAccountCreatedResult:(eSptCreateAccountResult)eResult login:(SptLoginData *)loginData {

}

- (void)onAudioDevicesSet:(SptDeviceData *)deviceMic speaker:(SptDeviceData *)deviceSpk {

}

- (void)onCallCreditUpdated:(ISptPSTNCallCredit *)pstnCredit {

}

- (void)onCallEventChatFileDownloaded:(SptCallID)callID event:(SptCallChatEvent *)callChatEvent {

}

- (void)onCallEventChatFileSending:(SptCallID)callID event:(SptCallChatEvent *)callChatEvent {

}

- (void)onCallEventChatReceived:(SptCallID)callID event:(SptCallChatEvent *)callChatEvent {

}

- (void)onCallEventChatSend:(SptCallID)callID event:(SptCallChatEvent *)callChatEvent {

}

- (void)onCallEventChatUpdated:(SptCallID)callID event:(SptCallChatEvent *)callChatEvent {

}

- (void)onCallEventConnectivityUpdated:(SptCallID)callID {

}

- (void)onCallEventDefaultManageServicesUpdated:(SptCallID)callID calldata:(ISptCall *)callDataObj {

}

- (void)onCallEventParticipantConnected:(SptCallID)callID callParticipant:(ISptCallParticipantData *)callParticipantObj {

}

- (void)onCallEventParticipantDisconnected:(SptCallID)callID callParticipant:(ISptCallParticipantData *)callParticipantObj {

}

- (void)onCallEventParticipantSpeakingListUpt:(SptCallID)callID participantList:(NSArray *)sortedSpkList {

}

- (void)onCallEventParticipantSpeakingUpt:(SptCallID)callID participant:(ISptCallParticipantData *)callParticipantObj {

}

- (void)onCallEventParticipantUpdated:(SptCallID)callID callParticipant:(ISptCallParticipantData *)callParticipantObj {

}

- (void)onCallEventPrivateChatUpt:(SptCallID)callID chat:(SptCallChat *)callChat {

}

- (void)onCallEventPublicChatUpt:(SptCallID)callID chat:(SptCallChat *)callChat {

}

- (void)onCallEventRecommendedPaintListUpt:(SptCallID)callID paintlist:(SptCallRecommendedPaintList *)recommendedPaintList {

}

- (void)onCallEventRecordingStateUpdated:(SptCallID)callID calldata:(ISptCall *)callDataObj {

}

- (void)onCallEventSendSharingStopped:(SptCallID)callID {

}


- (void)onCallEventStreaSpeakUpdated:(SptCallID)callID streamData:(ISptCallStream *)streamObj {

}

- (void)onCallEventStreamPropertiesUpdated:(SptCallID)callID streamData:(ISptCallStream *)streamObj {

}

- (void)onCallHistoryReport:(eSptCallHistoryEvent)event {

}

- (void)onCloudStorageUpdated:(ISptCloudStorage *)cloudStorage {

}

- (void)onContactPresenceRequest:(ISptContactData *)contactData {

}


- (void)onContactsInvitedByEmailResult:(BOOL)success {

}

- (void)onDeviceListUpdated:(NSArray *)deviceList {

}

- (void)onDeviceUpdated:(SptDeviceData *)deviceData {

}

- (void)onDisconnected {

}

- (void)onEventChatFileSending:(ISptEventData *)eventFileData {

}

- (void)onEventFileDownloaded:(ISptEventData *)eventData {

}

- (void)onEventUpdated:(ISptEventData *)eventData {

}

- (void)onFavoriteAdded:(ISptFavoriteData *)favoriteData {

}

- (void)onFavoriteRemoved:(ISptFavoriteData *)favoriteData {

}

- (void)onFileUpdated:(SptFile *)fileData {

}

- (void)onGroupContactAdded:(NSNumber *)contactID group:(ISptGroupData *)groupData {

}

- (void)onGroupContactRemoved:(NSNumber *)contactID group:(ISptGroupData *)groupData {

}

- (void)onGroupCreated:(ISptGroupData *)groupData {

}

- (void)onGroupRemoved:(ISptGroupData *)groupData {

}

- (void)onLoadSeaechedEventRes:(SptLoadSearchedEventRes *)searchedEventRes {

}

- (void)onLocalProfileError:(ISptContactProfile *)localVCard {

}

- (void)onLocalProfileRequired:(BOOL)bRequired {

}

- (void)onLocalProfileStored:(ISptContactProfile *)localVCard {

}

- (void)onPasswordRecoveryResult:(eSptPasswordRecoveryResult)eResult mail:(NSString *)email {

}

- (void)onPersonalToDosUpdated:(NSArray *)personalToDos {

}

- (void)onRoomUpdated:(ISptRoomData *)roomData {

}

- (void)onRoomMoreHistoryLoaded:(ISptRoomData *)room {

}

- (void)onRoomSynchronized:(ISptRoomData *)roomData {

}

- (void)onRoomWritingUpdated:(ISptRoomData *)room {

}

- (void)onSchMeetingCreateError:(SptSchMeetingCreate *)meetingCreate {

}

- (void)onSchMeetingCreateProgress:(SptSchMeetingCreate *)meetingCreate {

}

- (void)onSchMeetingCreated:(SptSchMeetingSequence *)meetingSeq {

}

- (void)onSchMeetingUpdated:(SptSchMeetingSequence *)meetingSeq {

}

- (void)onSchMeetingsSynchronized {
    //User Logged into Collaborate system
    dispatch_async( dispatch_get_main_queue(), ^(){
        if ( self.loginCallback != nil ){
            [self.loginCallback onMeetingsSynchronized];
        }
    });
}

- (void)onSearchAvailable {

}

- (void)onSearchChannelResult:(SptSearchChannels *)searchChannel {

}

- (void)onSearchEventsResult {

}

- (void)onSearchResult:(SptSearchContacts *)searchContact {

}

- (void)onSearchedContactUpdated:(ISptContactData *)contactData {

}

- (void)onChannelDataUpdated:(ISptRoomData *)roomData{

}

- (void)onVideoDeviceSet:(SptDeviceData *)deviceData {

}

@end

//
//  CollaborateUtils.h
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CollaborateSpace/CollaborateSpace.h>

typedef NS_ENUM(NSInteger, JoinMeetingError)
{
    eNoError,
    eWaitingHost,
    eMeetingFinished,
    eMeetingNotStarted,
    eMeetingCancelled,
    eNoMeetingFound
};

/**
ISpontaniaIMApiDelegate has too many functions, so we simplify to different protocols for different purpose
*/

/**
 When the applications tries to connect Login callback will be called with login OK or any error
 */
@protocol CollaborateLoginCallback <NSObject>
@required
-(void)onLoginResult:(BOOL)loginOK error:(eSptConnectionResult)error;
-(void)onGetTokenDataResult:(SptTokenDataResult *)tokenDataResult;
-(void)onMeetingsSynchronized;
@end


/**
 This callbacks informs about when to refresh contacts information,
 we basically receive if we should rebuild all the list or just one contact
 */
@protocol CollaborateContactsCallback <NSObject>
@required
/**
 When the application switches between disconnected and connected, or with any insertion or deletion of a contact, we will receive this event
 */
-(void)onContactListModified;
/**
 When Contact information is received, or when contact presence status is modified we will receive this one
 @param contact This interface provides all information about the contact
 */
-(void)onContactUpdated:(ISptContactData*)contact;

@end

/**
 You should implement this protocol and set you class as ChatsCallback to implement text chat service over collaborate
 */
@protocol CollaborateChatsCallback <NSObject>
@required
/**
 This function is called when the conversation list is modified so we now we have to reload everything
 */
-(void)onChatListModified;
/**
 When some detail of the chat is updated

 @param chat Interface providing information about room chat
 */
-(void)onChatUpdated:(ISptRoomData*)chat;
/**
 When a message has been recived

 @param event This interface provides information about message (text, image, any event )
 */
-(void)onChatEventReceived:(ISptEventData*)event;
/**
 When a message is sent

 @param event This interface provides information about message (text, image, any event )
 */
-(void)onChatEventSent:(ISptEventData*)event;

@end


/**
 To receive events of the active call
    This CollaborateSDK supports multiple calls at same time, for this sample we have
    simplified it so we consider the first call as active call and we don't process
    any event from other calls.
 */
@protocol CollaborateCallCallback <NSObject>
@required
/**
 A new streaming is started in the call
 @param stream Interface to provide information about streaming (it also provides a .view property so you can directly add it to your UI)
 */
-(void)onStreamingStarted:(ISptCallStream*)stream;

/**
 A new streaming has finished in the call
 @param stream Interface to provide information about streaming
 */
-(void)onStreamingStoped:(ISptCallStream*)stream;

/**
 When the calls request some information to the UI

 @param callRequest Interface to provide information about the request ( type: Accept moderation? / share an application? / ... and status:Pending / Processing / Done /... )
 */
-(void)onCallRequestUpdated:(SptCallRequest *)callRequest;


/**
 Local user can annotate over the current stream

 @param stream Sharing or Whiteboard stream to annotate over
 @param enabled if annotation is enabled (YES) or disabled (NO)
 */
-(void)onStreamAnnotationEnabled:(ISptCallStream *)stream enabled:(BOOL)enabled;

@end

/**
 To detect when a call created/established/finished we should implement this callback
 */
@protocol CollaborateCallsManagerCallback <NSObject>
@required
/**
 A new call is created

 @param call Interface to provide information about call (participants, type: audio/video, status)
 @param incoming If you recived the call and you have to answer it
 */
-(void)onNewCall:(ISptCall*)call incoming:(BOOL)incoming;
/**
 The call was accepted by all the participants so services are enabled

 @param call Interface to provide information about call (participants, type: audio/video, status)
 */
-(void)onCallEstablished:(ISptCall*)call;
/**
 The call is finished

 @param call Interface to provide information about call (participants, type: audio/video, status)
 */
-(void)onCallFinished:(ISptCall*)call;
@end


/**
 This interface implements all the ISpontaniaIMApiDelegate methods and simplifies them into custom sample callbacks protocols
 (CollaborateLoginCallback, CollaborateContactsCallback, CollaborateCallCallback, CollaborateCallsManagerCall, CollaborateChatsCallback)
 */
@interface CollaborateUtils : NSObject <ISpontaniaIMApiDelegate>

/**
 To ease the access to this static class, from anywhere

 @return A valid pointer to a global CollaborateUtils instance
 */
+(CollaborateUtils*)Instance;

@property (nonatomic, retain) ISpontaniaIMApi *api;
/**
 Set this callback to receive login result events
 */
@property (nonatomic, weak) id<CollaborateLoginCallback> loginCallback;
/**
 Set this callback to receive contacts update events
 */
@property (nonatomic, weak) id<CollaborateContactsCallback> contactsCallback;
/**
 Set this callback to receive call services events
 */
@property (nonatomic, weak) id<CollaborateCallCallback> callCallback;
/**
 Set this callback to receive Call establishment events
 */
@property (nonatomic, weak) id<CollaborateCallsManagerCallback> callManagerCallback;
/**
 Set this callback to receive chats events
 */
@property (nonatomic, weak) id<CollaborateChatsCallback> chatsCallback;

/**
 For the sample implementation, we just support one call, we store a pointer to
 this call interface so we can access it anytime while it is alive
 */
@property (nonatomic, retain) ISptCall *currentCall;

// Askblue code

@property (nonatomic, retain) NSString *myServer;
@property (nonatomic, retain) NSString *myToken;

@end

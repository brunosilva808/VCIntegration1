/**
  ISptDevices.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/


#import "ISptTypes.h"


/**
 @class SptDeviceData
 Device dta
 */
@interface SptDeviceData : NSObject

/**
 Device unique ID
 */
@property (readonly) SptDeviceID deviceID;

/**
 Type of device

 - kDeviceTypeInvalid: Invalid device type
 - kDeviceTypeVideoCapture: Camera device type
 - kDeviceTypeAudioCapture: Microphone device type
 - kDeviceTypeAudioRender: Speaker device type
 */
typedef NS_OPTIONS(NSUInteger, SptDeviceType)
{
    kDeviceTypeInvalid          = 0,
    kDeviceTypeVideoCapture     = 1 << 0,
    kDeviceTypeAudioCapture     = 1 << 2,
    kDeviceTypeAudioRender      = 1 << 3
};


/**
 Device type
 */
@property (readonly) SptDeviceType deviceType;


/**
 Device state

 - kDeviceStateNone: Device is in the system
 - kDeviceStateSelected: Device is selected to be used in calls and meetings
 - kDeviceStateWorking: Device is currntly used in a call or meeting
 - kDeviceStateError: Device error
 */
typedef NS_ENUM(NSUInteger, SptDeviceState)
{
    kDeviceStateNone        = 0,
    kDeviceStateSelected,
    kDeviceStateWorking,
    kDeviceStateError
};

/**
 Device current state
 */
@property (readonly) SptDeviceState deviceState;

/**
 In case camera device, camera position

 - kVideoDevicePosUnknown: Inknown position
 - kVideoDevicePosFront: Front camera
 - kVideoDevicePosBack: Back camera
 */
typedef NS_ENUM(NSUInteger, SptVideoDevicePosition)
{
    kVideoDevicePosUnknown      = 0,
    kVideoDevicePosFront,
    kVideoDevicePosBack
};


/**
 Get device position in case camera device
 */
@property (readonly) SptVideoDevicePosition videoDevicePosition;

/**
 In case of speaker device, render route

 - kRenderRouteUnknown: Unknown render route
 - kRenderRouteSpeaker: Speaket render toute
 - kRenderRouteEarpiece: Earpice render route
 */
typedef NS_OPTIONS(NSUInteger, SptAudioDeviceRenderRoute)
{
    kRenderRouteUnknown      = 0,
    kRenderRouteSpeaker      = 1 << 0,
    kRenderRouteEarpiece     = 1 << 1
};


/**
 Available render routes
 */
@property (readonly) SptAudioDeviceRenderRoute availableRenderRoute;
/**
 Current render route
 */
@property (readonly) SptAudioDeviceRenderRoute currentRenderRoute;

/**
 Is device muted, YES in case device is muted, NO is not muted
 */
@property (readonly) BOOL isMuted;

@end

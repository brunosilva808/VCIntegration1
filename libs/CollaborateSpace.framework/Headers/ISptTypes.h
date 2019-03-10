/**
  ISptTypes.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>

typedef uint32_t  TSptIMContactID;
static const TSptIMContactID kSPT_LOCAL_CONTACT_ID = 0;
static const TSptIMContactID kSPT_INVALID_CONTACT_ID = 0xFFFFFFFF;

typedef uint32_t  SptIMGroupID;
static const SptIMGroupID kSPT_INVALID_IM_GROUP_ID = 0xFFFFFFFF;

typedef uint32_t  SptIMRoomID;
static const SptIMRoomID kSPT_INVALID_IM_ROOM_ID = 0xFFFFFFFF;

typedef uint32_t  SptIMEventID;
static const SptIMRoomID kSPT_INVALID_IM_EVENT_ID = 0xFFFFFFFF;

typedef uint32_t  SptIMFavoriteID;
static const SptIMFavoriteID kSPT_INVALID_IM_FAVORITE_ID = 0xFFFFFFFF;

typedef uint32_t  SptDeviceID;
static const SptDeviceID kSPT_INVALID_DEVICE_ID = 0;

typedef uint32_t  SptFileID;
static const SptFileID kSPT_INVALID_FILE_ID = 0xFFFFFFFF;

typedef uint32_t  SptMeetingSeqID;
static const SptMeetingSeqID kSPT_INVALID_MEETING_SEQUENCE_ID = 0xFFFFFFFF;

typedef uint32_t  SptMeetingID;
static const SptMeetingID kSPT_INVALID_MEETING_ID = 0xFFFFFFFF;

typedef uint32_t  SptCallID;
static const SptCallID kSPT_INVALID_CALLID = 0xFFFFFFFF;

typedef uint32_t  SptCallParticipantID;
static const SptCallParticipantID kSPT_LOCAL_CALLPARTICIPANT_ID = 0;
static const SptCallParticipantID kSPT_INVALID_CALLPARTICIPANT_ID = 0xFFFFFFFF;

typedef uint64_t SptCallStreamDataID;
static const SptCallStreamDataID kSPT_INVALID_CALLSTREAMDATA_ID = 0xFFFFFFFFFFFFFFFFLL;

typedef uint32_t SptAnnotationPageID;

typedef uint32_t SptLocalWhiteboardID;

typedef uint32_t SptEntryID;
static const SptEntryID kSPT_INVALID_ENTRY_ID = 0xFFFFFFFF;

/*!
 Sort and filter contact list
 */
typedef NS_OPTIONS(NSUInteger, eContactFilterSort)
{
    /*!
     * Include external users (from other companied) in the result
     */
    kFilterExternalContacts = (1 << 0),
    /*!
     * Sorted by favorite
     */
    kSortedByFavoriteFirst   = (1 << 1),
    /*!
     * Sorted by display name
     */
    kSortedByDisplayNameAsc  = (1 << 2)
};

/*!
 Room filter
 
 - SptRoomFilterOne2One: Filter by One 2 One
 - SptRoomFilterMultiUser: Filter by MultiUser chat room
 - SptRoomFilterPublicChannel: Filter by public channels
 - SptRoomFilterPrivateChannel: Filter by private channels
 - SptRoomFilterAll: All rooms
 */
typedef NS_OPTIONS(NSUInteger, eSptRoomFilter)
{
    SptRoomFilterOne2One        = 1 << 0,
    SptRoomFilterMultiUser      = 1 << 1,
    SptRoomFilterPublicChannel  = 1 << 2,
    SptRoomFilterPrivateChannel = 1 << 3,
    SptRoomFilterAll       = SptRoomFilterOne2One | SptRoomFilterMultiUser | SptRoomFilterPublicChannel |SptRoomFilterPrivateChannel
};

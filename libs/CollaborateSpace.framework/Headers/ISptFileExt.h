/**
  ISptFileExt.h
  SptIMCoreIOS

  Created by Fernando Sanchez on 8/15/17.
  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

#import "ISptTypes.h"
#import <UIKit/UIKit.h>
#import "ISptContactBaseProtocol.h"
@class ISptContactData;

/**
 @class SptFile
 File data
 */
@interface SptFile : NSObject

/**
 File type

 - kSptFileTypeUnknown: Unknown file type
 - kSptFileTypeImage: Image file type
 - kSptFileTypeVideo: Video file type
 - kSptFileTypeWhiteBoard: Whiteboard file type
 - kSptFileTypeDocumment: Document file type
 */
typedef NS_ENUM(NSUInteger, SptFileType)
{
    kSptFileTypeUnknown,
    kSptFileTypeImage,
    kSptFileTypeVideo,
    kSptFileTypeWhiteBoard,
    kSptFileTypeDocumment
};

/**
 File unique ID
 */
@property (readonly) SptFileID fileID;
/**
 File type
 */
@property (readonly) SptFileType  fileType;
/**
 Content type
 */
@property (readonly) NSString *contentTypeText;
/**
 Size in bytes
 */
@property (readonly) uint64_t size;
/**
 Display name
 */
@property (readonly) NSString *displayName;
/**
 Normalized display name
 */
@property (readonly) NSString *normalizedDisplayName;

/**
 Local full path in case file is in local
 */
@property (readonly) NSURL *localFullPath;
/**
 Thumbnail full path in case it is available
 */
@property (readonly) NSURL *fileThumbnailLocalPath;
/**
 Download URL
 */
@property (readonly) NSURL *downloadURL;
    
/**
 Thumbnail image in case it is in memory
 */
@property (readonly) UIImage *thumbnail;
/**
 Has thumbnail?
 */
@property (readonly) BOOL hasThumbnail;
    
    
/**
 File state

 - kFileStateUnknown: Unknown state
 - kFileStateSelected: Selected
 - kFileStateUploading: Uploading to the cloud
 - kFileStateUploaded: Uploaded
 - kFileStateInCloud: In cloud
 - kFileStateDownloading: Downloading from the cloud
 - kFileStateDownloaded: Downloaded
 - kFileStateError: Error uploading
 - kFileStateRemoved: Removed
 */
typedef NS_ENUM(NSUInteger, SptFileState)
{
    kFileStateUnknown,
    kFileStateSelected,
    kFileStateUploading,
    kFileStateUploaded,
    kFileStateInCloud,
    kFileStateDownloading,
    kFileStateDownloaded,
    kFileStateError,
    kFileStateRemoved
};
    
/**
 File state
 */
@property (readonly) SptFileState fileState;
/**
 Upload/download progress in case it is uploading/downloading. A value from 0 to 100
 */
@property (readonly) NSUInteger progress;

/**
 Contact who uploaded the file
 */
@property (readonly) ISptContactData *uploadedContact;
/**
 COntact ID of the contact who uploaded the file
 */
@property (readonly) TSptIMContactID uploadedContactID;

/**
 Is file in local device
 */
@property (readonly) BOOL isInLocal;
    
/**
 Meeting sequence ID in case file is attached to a meeting
 */
@property (readonly) SptMeetingSeqID meetingSeqID;
/**
 Meeting ID in case file is attached to a meeting
 */
@property (readonly) SptMeetingID meetingID;
/**
 Room ID in case file is in a room
*/
@property (readonly) SptIMRoomID roomID;
/**
 Event ID in case file is in a room an event loaded in memory
 */
@property (readonly) SptIMEventID eventID;
/**
 Sent date in local time
 */
@property (readonly) NSDate *sentTime;
/**
 Send date in milliseconds to the epoch
 */
@property (readonly) unsigned long long sentEpoch;

/**
 File update flags

 - FileUpdatedState: File state updated
 - FileUpdatedProgress: File progress updated
 - FileUpdatedThumbnail: File thumbnail updated
 - FileUpdatedLocalPath: File local path updated
 - FileUpdatedDownloaded: File downloaded
 - FileUpdatedUploaded: File uploaded
 - FileUpdatedContext: File contect updated, chat or meeting where the file is
 */
typedef NS_OPTIONS(NSUInteger, SptFileUpdate)
{
    FileUpdatedState        = 1<<0,
    FileUpdatedProgress     = 1<<1,
    FileUpdatedThumbnail    = 1<<2,
    FileUpdatedLocalPath    = 1<<3,
    FileUpdatedDownloaded   = 1<<4,
    FileUpdatedUploaded     = 1<<5,
    FileUpdatedContext      = 1<<6
};

/**
 Get updated fields

 @param reset YES in case reset updated fields, NO otherwise
 @return Updeted fields
 */
-(SptFileUpdate)getUpdatedFields:(bool)reset;

/**
 Is this file a meeting recorded
 
 @return It returns true in case file is a meeting recorded, false otherwise
 */
-(BOOL)isRecording;


/**
 * In case of recording get the duration of the recording. Duration is nil in case not available
 */
@property (readonly) NSDateComponents* duration;

@end


/**
 @class SptFileSender
 File sender data
 */
@interface SptFileSender : NSObject<SptContactBase>
/**
 Number of files
 */
@property (readonly)   NSUInteger numFiles;
/**
 Contact ID
 */
@property (readonly)   TSptIMContactID contactID;
@end

/**
 @class SptFileSenderCollection
 File sender collection
 */
@interface SptFileSenderCollection : NSObject

/**
 Get file sender by position

 @param pos Position to retrieve file sender starting at 0
 @return File sender data
 */
-(SptFileSender*)getSenderByPosition:(NSUInteger)pos;

/**
 Get file sender by contact ID

 @param contactID COntact ID
 @return File sender data
 */
-(SptFileSender*)getSenderByContactID:(TSptIMContactID)contactID;
/**
 Number of senders in the collection
 */
@property (readonly) NSUInteger numSenders;
@end

/**
 File collection
 */
@interface SptFileCollection : NSObject

/**
 Get file by position starting at 0

 @param iPos File position in the collection
 @return File data
 */
-(SptFile*)getFileByPosition:(NSUInteger)iPos;
/**
 Get file ID

 @param fileID File ID
 @return File data
 */
-(SptFile*)getFileByID:(SptFileID)fileID;
/**
 Get position in the collection by file ID

 @param fileID File ID
 @return Position in the collection, -1 in case not found
 */
-(NSInteger)getPositionByFileID:(SptFileID)fileID;
/**
 Get sender collection

 @return Sender collectrion
 */
-(SptFileSenderCollection*)getSenderCollection;
/**
 Number of files in the collection
 */
@property (readonly)   NSUInteger numFiles;
    

/**
 Number of files by type
 */
typedef struct
{
    /**
     Number of image files
     */
    NSUInteger  numImages;
    /**
     Number of video files
     */
    NSUInteger  numVideos;
    /**
     Number of document files
     */
    NSUInteger  numDocuments;
    /**
     Number of other files
     */
    NSUInteger  numOthers;
    /**
     Number of whiteboard files
     */
    NSUInteger  numWhiteboards;
}STNumFileTypes;

/**
 Number of files by type
 */
@property (readonly) STNumFileTypes numFileTypes;

@end



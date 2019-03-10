/**
  ISptObjectsExt.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

/**
 @class ISptCloudStorage
 Cloud storage data
 */
@interface ISptCloudStorage : NSObject

/**
 Total size in bytes in the cloud
 */
@property (readonly) uint64_t totalSize;
/**
 Available size in bytes in the cloud
 */
@property (readonly) int64_t availableSize;

/**
 Syze of the image files in bytes
 */
@property (readonly) uint64_t imageFilesSize;
/**
 Syze of the video files in bytes
 */
@property (readonly) uint64_t videoFilesSize;
/**
 Syze of the recordings in bytes
 */
@property (readonly) uint64_t recordingsSize;
/**
 Syze of the document files in bytes
 */
@property (readonly) uint64_t docFilesSize;
/**
 Syze of other files in bytes
 */
@property (readonly) uint64_t otherFilesSize;
@end


/**
 @class ISptPSTNCallCredit
 Call OSTN credit
 */
@interface ISptPSTNCallCredit : NSObject

/**
 Available credit in USD
 */
@property (readonly) float credit;
/**
 Can I buy credit
 */
@property (readonly) BOOL  canBuyCredit;
/**
 URL to the call cost web page
 */
@property (readonly) NSURL *callCostURL;
/**
 URL to the buy credit web page
 */
@property (readonly) NSURL *callBuyCreditURL;
/**
 URL to the call history web page
 */
@property (readonly) NSURL *callCreditHistoryURL;

@end


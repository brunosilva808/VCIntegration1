/**
  NSNumber+SptCategorizedNumbers.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne. All rights reserved.
*/

#import <Foundation/Foundation.h>
#import "ISptTypes.h"

/**
 @category SptCategorizedNumbers
 NSNumber category to manage IDs as NSNumbers
 */
@interface NSNumber(SptCategorizedNumbers)

/**
 Contact ID

 @param contactID Contact ID
 @return NSNumber with the contact ID
 */
+(NSNumber *)numberWithContactID:(TSptIMContactID)contactID;
/**
 Group ID

 @param groupID Group ID
 @return NSNumber with the group ID
 */
+(NSNumber *)numberWithGroupID:(SptIMGroupID)groupID;
/**
 Room ID

 @param roomID Room ID
 @return NSNumber with the room ID
 */
+(NSNumber *)numberWithRoomID:(SptIMRoomID)roomID;
/**
 Call ID

 @param callID Call ID
 @return NSNumber with the call ID
 */
+(NSNumber *)numberWithCallID:(SptCallID)callID;
/**
 Call participant ID

 @param callParticipantID Call participant ID
 @return NSNumber with the call participant ID
 */
+(NSNumber *)numberWithCallParticipantID:(SptCallParticipantID)callParticipantID;
/**
 Call stream ID

 @param sptCallStreamDataID Call stream ID
 @return NSNumber with the call stream ID
 */
+(NSNumber *)numberWithCallStreamID:(SptCallStreamDataID)sptCallStreamDataID;
/**
 Annotation/whiteboard page ID

 @param sptAnnotationPageID Annotation/whioteboard page ID
 @return NSNumber with the annotation/whiteboard page ID
 */
+(NSNumber *)numberWithAnnotationPageID:(SptAnnotationPageID)sptAnnotationPageID;

/**
 Contact ID

 @return Contact ID
 */
-(TSptIMContactID)contactID;
/**
 Group ID

 @return Group ID
 */
-(SptIMGroupID)groupID;
/**
 Room ID

 @return Room ID
 */
-(SptIMRoomID)roomID;
/**
 Call ID

 @return call ID
 */
-(SptCallID)callID;
/**
 Call participant ID

 @return Call participant ID
 */
-(SptCallParticipantID)callParticipantID;
/**
 Call steam ID

 @return Call stream ID
 */
-(SptCallStreamDataID)callStreamID;
/**
 Annotation/whiteboard page ID°

 @return Annotation/whiteboard page ID°
 */
-(SptAnnotationPageID)annotationPageID;

@end


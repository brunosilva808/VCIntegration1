//
//  CallViewController.h
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CollaborateUtils.h"
#import "DocSelectionController.h"


@interface CallViewController : UIViewController <CollaborateCallCallback, CollaborateCallsManagerCallback, UIScrollViewDelegate, DocSelectorControllerDelegate>

@property (nonatomic, retain) ISptCall *call;

@property (nonatomic, assign) SptMeetingID meetingID;
@property (nonatomic, assign) SptMeetingID seqID;
@property (nonatomic, assign) JoinMeetingError joinMeetingError;


@end

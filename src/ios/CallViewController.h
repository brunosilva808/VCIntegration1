//
//  CallViewController.h
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CollaborateUtils.h"
#import "DocSelectionController.h"

@interface CallViewController : UIViewController <CollaborateCallCallback, UIScrollViewDelegate, DocSelectorControllerDelegate>

@property (nonatomic, retain) ISptCall *call;
@end

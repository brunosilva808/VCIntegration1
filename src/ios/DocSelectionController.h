//
//  DocSelectionController.h
//  TestSpontaniaV4Views
//
//  Copyright © 2017 ClearOne. All rights reserved.
//

#import <UIKit/UIKit.h>


@protocol DocSelectorControllerDelegate<NSObject>

@optional
-(void)OnImageSelected:(UIImage*)image;
-(void)OnDocumentSelected:(NSURL*)url;
-(void)OnDocumentSelectionCanceled;

@end

@interface DocSelectorController : NSObject <UIDocumentPickerDelegate, UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (nonatomic, assign) id<DocSelectorControllerDelegate> delegate;
@property (nonatomic, assign) UIViewController *viewController;
@property (retain, nonatomic) UIDocumentPickerViewController *docViewController;
@property (retain, nonatomic) UIDocumentPickerViewController *docPicker;
@property (retain, nonatomic) id myself;

+(DocSelectorController*)openDocumentSelectionFromViewController:(UIViewController*)viewController sender:(id)sender andDelegate:(id<DocSelectorControllerDelegate>)delegate;
-(void) cancel;
@end

//
//  DocSelectionController.m
//  TestSpontaniaV4Views
//
//  Copyright © 2017 ClearOne. All rights reserved.
//

#import "DocSelectionController.h" 
#import <MobileCoreServices/MobileCoreServices.h>
#import <AssetsLibrary/AssetsLibrary.h>
#import <AVFoundation/AVFoundation.h>

@interface DocSelectorController()
@property (nonatomic, retain) UIImagePickerController * uiImagePickerController;
@property (nonatomic, retain) UIAlertController *alert;
@end

@implementation DocSelectorController

+(DocSelectorController*)openDocumentSelectionFromViewController:(UIViewController*)viewController sender:(id)sender andDelegate:(id<DocSelectorControllerDelegate>)delegate{
    DocSelectorController *selectionController =[[DocSelectorController alloc]initWithViewController:viewController sender:(id)sender andDelegate:delegate ];
    selectionController.myself = selectionController;
    return selectionController;
}

// Required
- (void)documentPicker:(UIDocumentPickerViewController *)controller didPickDocumentsAtURLs:(NSArray <NSURL *>*)urls{
    if ( urls.count > 0 ){
        [self.delegate OnDocumentSelected:urls.firstObject];
    }
}

// called if the user dismisses the document picker without selecting a document (using the Cancel button)
- (void)documentPickerWasCancelled:(UIDocumentPickerViewController *)controller{
    [self reportCancelled];
}

-(instancetype)initWithViewController:(UIViewController*)viewController sender:(id)sender andDelegate:(id<DocSelectorControllerDelegate>)delegate{
    self = [super init];
    _viewController = viewController;
    _delegate = delegate;

    _alert = [UIAlertController alertControllerWithTitle:nil message:nil preferredStyle:UIAlertControllerStyleActionSheet];
    
    UIAlertAction * cancelAction = [UIAlertAction actionWithTitle:@"Cancel" style:UIAlertActionStyleCancel handler:^(UIAlertAction * _Nonnull action) {
        [self reportCancelled];
    }];
    
    UIAlertAction * takePictureAction = [UIAlertAction actionWithTitle:@"Take Photo" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        self.uiImagePickerController = [[UIImagePickerController alloc] init];
        self.uiImagePickerController.delegate = self;
        self.uiImagePickerController.sourceType = UIImagePickerControllerSourceTypeCamera;
        self.uiImagePickerController.mediaTypes = [NSArray arrayWithObjects:(NSString*)kUTTypeImage, nil];
        self.uiImagePickerController.cameraDevice = UIImagePickerControllerCameraDeviceRear | UIImagePickerControllerCameraDeviceFront;
        self.uiImagePickerController.cameraFlashMode = UIImagePickerControllerCameraFlashModeOn | UIImagePickerControllerCameraFlashModeOff | UIImagePickerControllerCameraFlashModeAuto;
        
        [viewController presentViewController:self.uiImagePickerController animated:YES completion:^{
            
        }];
    }];
    
    UIAlertAction * photoLibraryAction = [UIAlertAction actionWithTitle:@"Select from Gallery" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        self.uiImagePickerController = [[UIImagePickerController alloc] init];
        self.uiImagePickerController.delegate = self;
        self.uiImagePickerController.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        NSArray *mediaTypes = @[(NSString*)kUTTypeImage];
        self.uiImagePickerController.mediaTypes = mediaTypes;
        self.uiImagePickerController.videoQuality = UIImagePickerControllerQualityTypeHigh;
        [viewController presentViewController:self.uiImagePickerController animated:YES completion:^{
            
        }];
    }];
    
    
    UIAlertAction * otherDocumentAction = [UIAlertAction actionWithTitle:@"Other Document" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {

        self.docViewController =[[UIDocumentPickerViewController alloc]initWithDocumentTypes:@[(NSString*)kUTTypeCompositeContent] inMode:UIDocumentPickerModeImport];
        self.docViewController.delegate = self;
        UIPopoverPresentationController *popover = self.docViewController.popoverPresentationController;
        popover.permittedArrowDirections = UIPopoverArrowDirectionUp | UIPopoverArrowDirectionDown;
        if ( sender != nil && [sender isKindOfClass:[UIBarButtonItem class]] )
            popover.barButtonItem = sender;
        else{
            UIView *v = sender;
            popover.sourceView = viewController.view;
            popover.sourceRect = [v convertRect:v.bounds toView:popover.sourceView];
        }
        [self.viewController presentViewController:self.docViewController animated:NO completion:nil];
    }];

    
    [_alert addAction:takePictureAction];
    [_alert addAction:photoLibraryAction];
    [_alert addAction:otherDocumentAction];
    [_alert addAction:cancelAction];
    
    if ( sender == nil )
        sender = viewController.view;
    UIPopoverPresentationController *popover = _alert.popoverPresentationController;
    
    if ( sender != nil && [sender isKindOfClass:[UIBarButtonItem class]] ){
        popover.barButtonItem = sender;
        popover.permittedArrowDirections = UIPopoverArrowDirectionAny;
    }else{
        UIView *v = sender;
        popover.sourceView = viewController.view;
        popover.sourceRect = [v convertRect:v.bounds toView:popover.sourceView];
        popover.permittedArrowDirections = UIPopoverArrowDirectionUp | UIPopoverArrowDirectionDown;
    }
    [viewController presentViewController:_alert animated:YES completion:nil];
   
    return self;
}

-(void)cancel{
    if ( _alert != nil ){
        [_alert dismissViewControllerAnimated:YES completion:nil];
    }
    
    if ( _docPicker != nil ){
        [_docPicker dismissViewControllerAnimated:YES completion:^{
            [self reportCancelled];
        }];
    }
    
    if ( _docViewController != nil ){
        [_docViewController dismissViewControllerAnimated:YES completion:^{
            [self reportCancelled];
        }];
    }
}


-(void)reportCancelled{
    if ( [_delegate respondsToSelector:@selector( OnDocumentSelectionCanceled ) ])
        [_delegate OnDocumentSelectionCanceled];
    _myself = nil;
}

-(UIImage*)imageWithoutRotation:(UIImage*)image{
    if (image.imageOrientation == UIImageOrientationUp)
        return image;
    UIGraphicsBeginImageContextWithOptions(image.size, NO, image.scale);
    [image drawInRect:(CGRect){{0, 0}, image.size}];
    UIImage *image2 = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return image2;
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary<NSString *,id> *)info{
    NSString *mediaType = [info objectForKey: UIImagePickerControllerMediaType];
    
    if (CFStringCompare ((__bridge_retained CFStringRef) mediaType, kUTTypeMovie, 0) == kCFCompareEqualTo)
    {
    }else{
        UIImage *image = [info valueForKey:UIImagePickerControllerOriginalImage];
        if ( [_delegate respondsToSelector:@selector( OnImageSelected: )] ){
            [picker dismissViewControllerAnimated:YES completion:^{
                [self.delegate OnImageSelected:image];
            }];
        }else{
            NSURL *url = [info objectForKey:UIImagePickerControllerImageURL];
            if ( url == nil ){
                [picker dismissViewControllerAnimated:YES completion:^{
                    NSString *tmp = [NSString stringWithFormat:@"%@%d%d.%@", NSTemporaryDirectory(), (int)[NSDate date].timeIntervalSinceReferenceDate, rand(), @"png" ];
                    [UIImagePNGRepresentation([self imageWithoutRotation:image]) writeToFile:tmp atomically:YES];
                    
                   if ( [self.delegate respondsToSelector:@selector( OnDocumentSelected: )] ){
                        [self.delegate OnDocumentSelected:[NSURL fileURLWithPath:tmp]];
                    }
                }];
            }else{
                [picker dismissViewControllerAnimated:YES completion:^{
                    if ( [self.delegate respondsToSelector:@selector( OnDocumentSelected: )] ){
                        [self.delegate OnDocumentSelected:url];
                    }
                }];
            }
        }
    }
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    [_uiImagePickerController dismissViewControllerAnimated:YES completion:^{
        [self reportCancelled];
    }];
}

@end

/**
  ISptAnnData.h
  SptIMCoreIOS

  Created by Fernando Sanchez on 12/4/17.
  Copyright © 2017 ClearOne Inc. All rights reserved.
*/

#import "ISptTypes.h"
#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

/**
 @class SptAnnotation
 Annotation/whiteboard data
 */
@interface SptAnnotation : NSObject

/**
 Annotation tool

 - kAnnToolInvalid: Invalid annotation tool
 - kAnnToolBrush: Brush
 - kAnnToolLine: Line
 - kAnnToolRectangle: Rectangle
 - kAnnToolTriangle: Triangle
 - kAnnToolEllipse: Ellipse
 - kAnnToolArrow: Arrow
 - kAnnToolBalloon: Ballon
 - kAnnToolEraser: Eraser
 - kAnnToolText: Text
 - kAnnToolDrag: Grag objects
 */
typedef NS_ENUM(NSUInteger, AnnotationTool)
{
    kAnnToolInvalid,
    kAnnToolBrush,
    kAnnToolLine,
    kAnnToolRectangle,
    kAnnToolTriangle,
    kAnnToolEllipse,
    kAnnToolArrow,
    kAnnToolBalloon,
    kAnnToolEraser,
    kAnnToolText,
    kAnnToolDrag,
};

/**
 Line tickness

 - kAnnThickInvalid: Invalid
 - kAnnThickMinimun: Minimum
 - kAnnThickWeak: Weak
 - kAnnThickMedium: Medium
 - kAnnThickStrong: Strong
 - kAnnThickMaximum: Maximum
 */
typedef NS_ENUM(NSUInteger, AnnotationThickness)
{
    kAnnThickInvalid,
    kAnnThickMinimun,
    kAnnThickWeak,
    kAnnThickMedium,
    kAnnThickStrong,
    kAnnThickMaximum,
};

/**
 Text size

 - kAnnTextSizeInvalid: Invalid text size
 - kAnnTextSizeSmall: Small
 - kAnnTextSizeMedium: Medium
 - kAnnTextSizeBig: Big
 */
typedef NS_ENUM(NSUInteger, AnnotationTextSize)
{
    kAnnTextSizeInvalid,
    kAnnTextSizeSmall,
    kAnnTextSizeMedium,
    kAnnTextSizeBig
};

/**
 Report a finger action

 - kFingerPress: Finger press
 - kFingerMove: Finger move
 - kFingerRelease: Finger release
 */
typedef NS_ENUM(NSUInteger, SptFingerAction)
{
    kFingerPress,
    kFingerMove,
    kFingerRelease
};

/**
 Whioteboard actions

 - kAnnUndo: Undo
 - kAnnRedo: Redo
 - kAnnClearAll: Clear all
 */
typedef NS_ENUM(NSUInteger, SptAnnSpecialAction)
{
    kAnnUndo,
    kAnnRedo,
    kAnnClearAll
};

/**
 Is whiteboard or annotation, YES in case of whiteboard, NO annotation
 */
@property (readonly) bool isWhiteboard;
/**
 Number of pages
 */
@property (readonly) int numPages;
/**
 NSArray with NSNumbers with the pages IDs
 */
@property (readonly) NSArray *pages;
/**
 Current selected page
 */
@property (readonly) SptAnnotationPageID currentPage;
/**
 Can I undo
 */
@property (readonly) bool canIUndo;
/**
 Can I redo
 */
@property (readonly) bool canIRedo;
/**
 Can I clear all
 */
@property (readonly) bool canIClearPage;
/**
 Current selected tool
 */
@property (readonly) AnnotationTool currentTool;
/**
 Current selected thickness
 */
@property (readonly) AnnotationThickness currentThickness;
/**
 Current selected text size
 */
@property (readonly) AnnotationTextSize currentTextSize;

/**
 Set tool

 @param tool Tool to set
 @return true in case of seccess, false in case of error
 */
-(bool)setAnnotationTool:(AnnotationTool)tool;
/**
 Set thickness

 @param thickness Thickness to set
 @return true in case of seccess, false in case of error
 */
-(bool)setAnnotationThickness:(AnnotationThickness)thickness;
/**
 Set text size

 @param textSize Text size to set
 @return true in case of seccess, false in case of error
 */
-(bool)setAnnotationTextSize:(AnnotationTextSize)textSize;
/**
 Set color

 @param border It is boder color or fill color
 @param color Color to set
 @return true in case of seccess, false in case of error
 */
-(bool)setAnnotationColor:(bool)border
                    setColor:(UIColor *)color;

/**
 Create a new page

 @return true in case of seccess, false in case of error
 */
-(bool)createAnnotationPage;
/**
 Delete page

 @param page Annotation page ID
 @return true in case of seccess, false in case of error
 */
-(bool)deleteAnnotationPage:(SptAnnotationPageID)page;
/**
 Set current page

 @param page Page ID
 @return true in case of seccess, false in case of error
 */
-(bool)setAnnotationPage:(SptAnnotationPageID)page;


/**
 Report a paint action

 @param fingerAction Finger action
 @param point Point in pixels
 @return true in case of seccess, false in case of error
 */
-(bool)makePaintAction:(SptFingerAction)fingerAction
              position:(CGPoint)point;

/**
 Make action

 @param fingerAction Action to perform
 @return true in case of seccess, false in case of error
 */
-(bool)makeSpecialAction:(SptAnnSpecialAction)fingerAction;

/**
 Save

 @param fileUrl file URL where will be saved
 @return YES in case of seccess, NO in case of error
 */
-(BOOL)saveAnnotation:(NSURL *)fileUrl;

@end


/**
 @protocol SptLocalAnnotationDelegate
 Receive local whiteboard notifications
 */
@protocol SptLocalAnnotationDelegate <NSObject>
/**
 Error

 @param whiteboardID Local whiteboard ID
 */
-(void)onLocalAnnotationError:(SptLocalWhiteboardID) whiteboardID;
/**
 Whiteboard created

 @param whiteboardID Local whiteboard ID
 */
-(void)onLocalAnnotationCreated:(SptLocalWhiteboardID) whiteboardID;
/**
 Whiteboard updated

 @param whiteboardID Local whiteboard ID
 */
-(void)onLocalAnnotationUpdated:(SptLocalWhiteboardID) whiteboardID;
/**
 Whiteboard image updated

 @param whiteboardID Local whiteboard ID
 */
-(void)onLocalAnnotationImageUpdated:(SptLocalWhiteboardID) whiteboardID;

/**
 Local annotation saved to disk
 
 @param whiteboardID Local whiteboard ID
 */
-(void)onLocalAnnotationSaved:(SptLocalWhiteboardID) whiteboardID;

@end

@protocol SptMediaView;

/**
 @class SptLocalAnnotation
 Local whiteboard data
 */
@interface SptLocalAnnotation : SptAnnotation

/**
 Init with delegate

 @param delegate Delegate to receive notifications
 @return created instance
 */
+(instancetype)localAnnotationWithDelegate:(id<SptLocalAnnotationDelegate>) delegate;
/**
 Init with file

 @param delegate Delegate to receive notifications
 @param file File to load
 @return Created instance
 */
+(instancetype)localAnnotationWithFile:(id<SptLocalAnnotationDelegate>) delegate
                                    filepath:(NSURL*)file;

/**
 Generate a whiteboard thumbnail from file

 @param url File
 @param size Size of the thumbnail
 @return Thumbnail image in case of success, nul in case of error
 */
+(UIImage*)generateThumbnailFromFile:(NSURL*)url size:(CGSize)size;
/**
 Local whiteboard ID
 */
@property (readonly) SptLocalWhiteboardID localWhiboardID;
/**
 Size in pixels
 */
@property (readonly) CGSize size;

/**
 Get view
 */
@property (readonly) id<SptMediaView> view;

@end


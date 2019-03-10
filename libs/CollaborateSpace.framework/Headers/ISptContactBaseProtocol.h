/**
  ISptContactBaseProtocol.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

/*!
 @protocol SptContactBase
 Contact base data
 */
@protocol SptContactBase <NSObject>
/*!
 Display name
 */
@property (readonly) NSString * displayName;
/*!
 Normalized display name
 */
@property (readonly) NSString * normalizedDisplayName;
/*!
 Initials
 */
@property (readonly) NSString *initials;
/*!
 Color
 */
@property (readonly) UIColor *color;
/*!
 Picture
 */
@property (readonly) UIImage *picture;
@end


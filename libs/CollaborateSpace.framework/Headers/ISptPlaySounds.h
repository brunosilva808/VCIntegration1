/**
  ISptTypes.h
  SptIMCoreIOS

  Copyright © 2018 ClearOne Inc. All rights reserved.
*/

#import <Foundation/Foundation.h>


/**
 @class SptPlaySound
 Play sounds
 */
@interface SptPlaySound : NSObject

/**
 Create a sound to play
 @param url To the file to play
 */
+(SptPlaySound*)playSoundWithURL:(NSURL *)url;
/**
 Play sound
 */
-(BOOL)play;

/**
 Stop play sound
 */
-(void)stop;

/**
 Stop other sounds and play this one
 */
@property (nonatomic, assign) BOOL force;

/**
 Play in a loop
 */
@property (nonatomic, assign) BOOL loop;

@end

//
//  ISptContactData+UIUtils.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "ISptContactData+UIUtils.h"

@implementation ISptContactData (UIUtils)

-(UIColor *)presenceColor{
    switch ( self.state ){
        case kSptPresenceDND:
        case kSptPresenceOffLine:
        case kSptPresenceInvisible:
            return UIColor.redColor;
            break;
        case kSptPresenceAway:
            return UIColor.yellowColor;
            break;
        case kSptPresenceAvailable:
        case kSptPresenceCollaborateCall:
        case kSptPresenceSpontaniaCall:
            return UIColor.greenColor;
            break;
    }
}
@end

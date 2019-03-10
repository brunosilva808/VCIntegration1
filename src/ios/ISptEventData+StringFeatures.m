//
//  ISptEventData+StringFeatures.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "ISptEventData+StringFeatures.h"


@implementation ISptEventData (StringFeatures)

-(NSString*)text:(BOOL)addContactName{
    NSMutableString *contactsEvent = [NSMutableString string];
    for ( ISptContactData *contact in self.contactCollection ){
        if ( contactsEvent.length > 0 )
            [contactsEvent appendString:@", "];
        [contactsEvent appendString:contact.displayName];
    }
    
    switch ( self.eventType ){
        case kSptEventTypeChatMessage:
            if ( addContactName )
                return [NSString stringWithFormat:@"%@: %@", self.contactText, self.message];
            else
                return self.message;
        case kSptEventTypeFile:
            if ( addContactName )
                return [NSString stringWithFormat:@"%@: (file)", self.contactText];
            else
                return @"(file)";
        case kSptEventNotificationTitleUpd:
            return @"Chat title changed";
        case kSptEventNotificationDescUpd:
            return @"Chat description changed";
        case kSptEventNotificationPublic:
            return @"Administrator has published the chat";
        case kSptEventNotificationJoinedPart:
        case kSptEventNotificationAddedParts:
            return [NSString stringWithFormat:@"%@ enter the conversation", contactsEvent ];
        case kSptEventNotificationLeaveParts:
            return [NSString stringWithFormat:@"%@ leaves the conversation", contactsEvent ];
        case kSptEventNotificationOutcastParts:
            return [NSString stringWithFormat:@"%@ banned from conversation", contactsEvent ];
        case kSptEventNotificationCallStarted:
            return @"Call established";
        case kSptEventNotificationCallNoAnswer:
            return @"No answer";
        case kSptEventNotificationCallMissed:
            return @"Call missed";
        case kSptEventNotificationCallFinished:
            return @"Call finished";
        case kSptEventNotificationCallError:
            return @"Error in call";
        default:
            return @"";
    }
    
    return @"";
}
-(NSString*)text{
    return [self text:NO];
}

-(BOOL)notification{
    return !(self.eventType == kSptEventTypeChatMessage || self.eventType == kSptEventTypeFile);
}
-(NSString*)contactText{
    if ( !self.notification )
        return (self.contact.contactID == kSPT_LOCAL_CONTACT_ID)?@"Me":self.contact.displayName;
    else
        return @"";
}

-(NSString*)textFull{
    return [self text:YES];
}

-(NSString*)dateText{
    BOOL sameDay = [[NSCalendar currentCalendar] isDate:[NSDate date] inSameDayAsDate:self.time];
    
    return [NSDateFormatter localizedStringFromDate:self.time
                                          dateStyle:(sameDay)?NSDateFormatterNoStyle:NSDateFormatterShortStyle
                                          timeStyle:(sameDay)?NSDateFormatterShortStyle:NSDateFormatterNoStyle];
}

@end


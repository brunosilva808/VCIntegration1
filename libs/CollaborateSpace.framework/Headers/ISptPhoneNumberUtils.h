//
//  ISptPhoneNumberUtils.h
//  CollaborateSpace
//
//  Copyright © 2018 ClearOne Inc. All rights reserved.
//

#ifndef ISptPhoneNumberUtils_h
#define ISptPhoneNumberUtils_h

/**
 @class SptPhoneNumberData
 Phone number data
 */
@interface SptPhoneNumberData : NSObject

/**
 Create object with phone number
 
 @param number Phone number
 @param defaultCountry Default country, in case of nil, it is taken from the carrier, in case
 no carrier, it is taken from the device configuration
 */
+(instancetype) sptPhoneNumberDataWithString:(NSString *)number
                                     country:(NSString *)defaultCountry;

/**
 Get default region
 
 @return default region
 */
+(NSString *) defaultRegion;

/**
 Get default country phone prefix
 
 @return default contry phone code
 */
+(NSUInteger) defaultRegionCode;

typedef NS_ENUM(NSUInteger, SptPhoneNumberValid)
{
    kValidUnknown       = 0,
    kPossible           = 1, /*!< The number length matches that of valid numbers for this region. */
    kPossibleLocalOnly  = 2, /*!< The number length matches that of local numbers for this region only
                              (i.e. numbers that may be able to be dialled within an area, but do not
                              have all the information to be dialled from anywhere inside or outside the country).*/
    kInvalidCountryCode = 3, /*!< The number has an invalid country calling code. */
    kTooShort           = 4, /*!< The number is shorter than all valid numbers for this region. */
    kInvalidLenght      = 5, /*!< The number is longer than the shortest valid numbers for this region,
                              shorter than the longest valid numbers for this region, and does not
                              itself have a number length that matches valid numbers for this region.
                              This can also be returned in the case where there are no numbers of
                              this type at all for this region.*/
    kTooLong            = 6, /*!< The number is longer than all valid numbers for this region. */
    kNotInRegion        = 7  /*!< Number is not valid in the region */
};
    
    
typedef NS_ENUM(NSUInteger, SptPhoneNumberType)
{
    kNumberTypeUnknown = 0,    /*!< A phone number is of type UNKNOWN when it does not fit any of the known
                                patterns for a specific region.*/
    kFixedLine         = 1,    /*!< Fixed line */
    kMobile            = 2,    /*!< Mobile */
    kFixedLineOrMobile = 3,    /*!< In some regions (e.g. the USA), it is impossible to distinguish between
                                fixed-line and mobile numbers by looking at the phone number itself. */
    kTollFree          = 4,    /*!< Freephone lines */
    kPremiumRate       = 5,    /*!< Premium rate */
    kSharedCost        = 6,    /*!< The cost of this call is shared between the caller and the recipient, and
                                is hence typically less than PREMIUM_RATE calls. See
                                http://en.wikipedia.org/wiki/Shared_Cost_Service for more information. */
    kVoIP              = 7,    /*!< Voice over IP numbers. This includes TSoIP (Telephony Service over IP). */
    kPersonalNumber    = 8,    /*!< A personal number is associated with a particular person, and may be
                                routed to either a MOBILE or FIXED_LINE number. Some more information can
                                be found here: http://en.wikipedia.org/wiki/Personal_Numbers */
    kPager             = 9,
    kUAN               = 10,   /*!< Used for "Universal Access Numbers" or "Company Numbers". They may be
                                further routed to specific offices, but allow one number to be used for a company. */
    kVoiceMail         = 11,   /*!< Used for "Voice Mail Access Numbers */
};

/**
 Valid number
 */
@property (readonly) SptPhoneNumberValid valid;

/**
 Type of number
 */
@property (readonly) SptPhoneNumberType type;

/**
 Original number
 */
@property (readonly) NSString *number;

/**
 Number in E.164 format
 */
@property (readonly) NSString *numberE164;

/**
 Country number
 */
@property (readonly) NSUInteger countryNumber;

/**
 Local number, without country code
 */
@property (readonly) long long localNumber;

/**
 Country code in ISO 3166-1 alpha-2 format
 */
@property (readonly) NSString *countryCode; //ISO 3166-1 alpha-2


@end
#endif /* ISptPhoneNumberUtils_h */

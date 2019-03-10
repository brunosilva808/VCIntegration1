//
//  ContactImageView.m
//  TestCollaborateIOS
//
//  Copyright © 2018 ClearOne. All rights reserved.
//

#import "ContactImageView.h"
#import "ISptContactData+UIUtils.h"

@interface ContactImageView()
@property (nonatomic, retain) UILabel *labelInitials;
@property (nonatomic, retain) UIView *viewPresence;
@property (nonatomic, retain) UIImageView *imageView;
@end

@implementation ContactImageView

-(void)awakeFromNib{
    [super awakeFromNib];
    
    _viewPresence = [UIView new];
    [self addSubview:_viewPresence];

    _imageView = [UIImageView new];
    _imageView.contentMode = UIViewContentModeScaleAspectFill;
    [self addSubview:_imageView];
    [self sendSubviewToBack:_imageView];
    
    _labelInitials = [UILabel new];
    _labelInitials.adjustsFontSizeToFitWidth = YES;
    _labelInitials.minimumScaleFactor = 0.1;
    _labelInitials.textAlignment = NSTextAlignmentCenter;
    _labelInitials.baselineAdjustment = UIBaselineAdjustmentAlignCenters;
    _labelInitials.textColor = UIColor.whiteColor;
    [self addSubview:_labelInitials];
    [self sendSubviewToBack:_labelInitials];
}

-(void)setContact:(ISptContactData *)contact{
    _contact = contact;
    [self reloadContactData];
}

-(void)reloadContactData{
    ISptContactProfile *profile = _contact.profile;
    if ( profile != nil && profile.picture != nil ){
        _imageView.image = profile.picture;
        _labelInitials.hidden = YES;
        _imageView.hidden = NO;
    }else{
        _labelInitials.text = _contact.initials;
        _labelInitials.backgroundColor = (_contact.color==nil)?UIColor.grayColor:_contact.color;
        _labelInitials.hidden = NO;
        _imageView.hidden = YES;
    }
    
    _viewPresence.backgroundColor = _contact.presenceColor;
    [self setNeedsLayout];
}

-(void)layoutSubviews{
    [super layoutSubviews];
    
    CGRect r = self.bounds;
    _labelInitials.frame = r;
    _labelInitials.layer.cornerRadius = r.size.width / 2;
    _labelInitials.layer.masksToBounds = YES;
    _labelInitials.font = [UIFont systemFontOfSize:_labelInitials.frame.size.width*0.5];
    
    CGRect framePresence = CGRectMake( 0.7 * r.size.width, 0.7* r.size.height, 0.25 * r.size.width, 0.25 * r.size.height );
    _viewPresence.frame = framePresence;
    _viewPresence.layer.cornerRadius = framePresence.size.width / 2;
    
    _imageView.frame = r;
    _imageView.layer.cornerRadius = r.size.width / 2;
    _imageView.layer.masksToBounds = YES;
}

@end

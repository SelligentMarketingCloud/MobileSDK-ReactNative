//
//  SMManagerUniversalLinksDelegate.h
//  MobileSDK
//
//  Created by Marc Biosca on 7/12/21.
//  Copyright © 2021 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  This protocol will give you the possibility to manage the behaviour when clicking a "deeplink" button type containing an universal link.
 */
@protocol SMManagerUniversalLinksDelegate <NSObject>
@optional

/*!
 * @abstract Invoked when a "deeplink" button type, whose URL scheme is HTTP or HTTPS, is clicked
 * @param url The NSURL introduced as value of the button that has been clicked
 */
- (void) executeLinkAction:(NSURL*_Nonnull)url;

@end

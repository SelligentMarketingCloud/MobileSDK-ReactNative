//
//  SMManagerDelegate.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 25/5/2021.
//  Copyright © 2021 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMInAppMessage.h"

/**
 *  This protocol will help you intercept the inapp messages and allow you to display them your own way or store them somewhere to be shown later.
 */
@protocol SMManagerInAppMessageDelegate <NSObject>
@optional

/*!
 * @abstract Invoked when an inapp message linked to a remote notification is received by sdk.
 * @param inAppMessage The inAppMessage object containing all necessary datas for you to display content of the message
 */
- (void) displayInAppMessage:(SMInAppMessage*_Nonnull)inAppMessage;

@end

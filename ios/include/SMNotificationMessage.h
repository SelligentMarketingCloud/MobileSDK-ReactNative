//
//  SMNotificationMessage.h
//  MobileSDK
//
//  Created by Walter Tricknot on 17/01/2017.
//  Copyright © 2017 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMInAppMessage.h"
#import "SMNotificationButtonData.h"

@interface SMNotificationMessage : SMInAppMessage

/*!
 *  NSString instance providing url of the Rich media attached to the remote-notification
 */
@property (readonly, nonatomic) NSString*_Nullable mediaUrl;

/*!
 *  SMNotificationButtonData instance providing the main action behind the remote-notification banner
 *  @see SMNotificationButtonData
 */
@property (readonly, nonatomic) SMNotificationButtonData*_Nullable mainAction;

/*!
 *  NSArray of SMLink objects from the remote-notification
 */
@property (readonly, nonatomic) NSArray*_Nullable notificationButtons;

@end

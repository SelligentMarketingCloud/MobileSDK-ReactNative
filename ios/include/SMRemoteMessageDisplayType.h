//
//  SMRemoteMessageDisplayType.h
//  MobileSDK
//
//  Created by Marc Biosca on 9/10/21.
//  Copyright © 2021 Selligent. All rights reserved.
//

/*!
 * Defines the behaviour that the SDK will apply when receiving a remote-notification in foreground.
 */
typedef NS_ENUM (NSInteger, SMRemoteMessageDisplayType) {
    /*!
     *  Default value when not explicitly set.
     */
    kSMRemoteMessageDisplayType_Unknown = 0,
    
    /*!
     *  No Push nor in-app messages will be displayed.
     */
    kSMRemoteMessageDisplayType_None = 1,
    
    /*!
     *  A Push notification will be displayed.
     */
    kSMRemoteMessageDisplayType_Notification = 2,
    
    /*!
     *  An in-app message will be displayed (when there is an in-app message available within the remote-notification payload).
     */
    kSMRemoteMessageDisplayType_Automatic = 3
};

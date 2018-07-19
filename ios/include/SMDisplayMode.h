//
//  SMDisplayMode.h
//  MobileSDK
//
//  Created by Jean-Louis Delmarche on 25/05/16.
//  Copyright © 2016 Selligent. All rights reserved.
//


/*!
 *  #SMDisplayMode :#
 */
typedef NS_ENUM(NSInteger, SMDisplayMode) {
    /*!
     *  This explicitely sets the displayMode to unknown
     */
    kSMDisplayMode_Unknown = -1,
    
    /*!
     *  Display only once
     */
    kSMDisplayMode_OnlyOnce = 0,
    
    /*!
     *  Always display until replaced
     */
    kSMDisplayMode_UntilReplaced = 1
};

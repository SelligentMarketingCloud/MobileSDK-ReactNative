//
//  SMIAMRefreshType.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 13/11/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

/*!
 *  #SMInAppRefreshType :#
 */
typedef NS_ENUM(NSInteger, SMInAppRefreshType) {
    /*!
     *  This explicitely disable the In App fetch  mecahnism
     */
    kSMIA_RefreshType_None,
    /*!
     * Allow to fetch In App Minutely (to be used only in development)
     */
    kSMIA_RefreshType_Minutely,
    /*!
     * Allow to fetch In App hourly
     */
    kSMIA_RefreshType_Hourly,
    /*!
     * Allow to fetch In App Daily
     */
    kSMIA_RefreshType_Daily ,
};

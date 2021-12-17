//
//  SMInAppMessageType.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 24/9/2020.
//  Copyright © 2020 Selligent. All rights reserved.
//

typedef NS_ENUM (NSInteger, SMInAppMessageType) {
    /*!
     *  In App message of unknown type.
     */
    kSMInAppMessageType_Unknown = -2,
    
    /*!
     *  In App message of hidden type.
     */
    kSMInAppMessageType_Hidden = -1,
    
    /*!
     *  In App message of alert type.
     */
    kSMInAppMessageType_Alert = 0,
    
    /*!
     *  In App message of html type.
     */
    kSMInAppMessageType_HTML = 1,
    
    /*!
     *  In App message of url type.
     */
    kSMInAppMessageType_Url = 2,
    
    /*!
     *  In App message of image type.
     */
    kSMInAppMessageType_Image = 3,
    
    /*!
     *  In App message of map type.
     */
    kSMInAppMessageType_Map = 4,
    
    /*!
     *  In App message of passbook type.
     */
    kSMInAppMessageType_Passbook = 5
};


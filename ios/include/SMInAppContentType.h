//
//  SMInAppContentType.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 02/03/16.
//  Copyright © 2016 Selligent. All rights reserved.
//


/*!
 *  #SMInAppContentType :#
 */
typedef NS_OPTIONS (NSInteger, SMInAppContentType) {
    
    /*!
     *  In App content of unknown type.
     */
    kSMInAppContentType_Unknown = -2,
    
    /*!
     *  In App content of HTML type.
     */
    kSMInAppContentType_HTML = 1,
    
    /*!
     *  In App content of URL type.
     */
    kSMInAppContentType_Url = 2,
    
    /*!
     *  In App content of Image type.
     */
    kSMInAppContentType_Image = 3

    
};
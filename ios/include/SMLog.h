//
//  SMLog.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 12/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//




/*!
 *  Enumeration type for the log granularity
 */
typedef NS_OPTIONS(NSInteger, SMLogLevel){
    /*!
     *  No log printed at all.
     *  This is the suggested log-level for release.
     */
    kSMLogLevel_None = 0,
    
    /*!
     *  Default log-entry.
     *  Basically inform user when library starts / ends.
     */
    kSMLogLevel_Info = 1 << 1,
    
    /*!
     *  Only warning messages are printed
     */
    kSMLogLevel_Warning = 1 << 2,
    
    /*!
     *  Only Error messages are being printed
     */
    kSMLogLevel_Error = 1 << 3,
    
    /*!
     *  Print only HTTP-requests stuff
     */
    kSMLogLevel_HTTPCall =  1 << 4,

    /*!
     *  Print only location-requests stuff
     */
    kSMLogLevel_Location =  1 << 5,
    
    /*!
     *  Print everything. Do not use for release!!!
     */
    kSMLogLevel_All = 0xFF,
};






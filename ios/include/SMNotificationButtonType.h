//
//  SMNotificationButtonType.h
//  MobileSDK
//
//  Created by Gauthier Dumont on 03/07/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//


/*!
 *  This enumeration declares all known buttun-type
*/
typedef NS_ENUM(NSInteger, SMNotificationButtonType) {
    /*!
     *  Any received button-type not in this enumeration type will be considered as unknown
     */
    kSMNotificationButtonType_Unknown                    = -1,

    /*!
     *  A button-type that will have no action but when clicked will send back button value to the platform
     */
    kSMNotificationButtonType_Simple                     = 0,

    /*!
     *  A button-type that will open the Phone application with a ready to use number to dial
     */
    kSMNotificationButtonType_OpenPhoneCall              = 1,

    /*!
     *  A button-type that will open the sms application with a ready to dial sms
     */
    kSMNotificationButtonType_OpenSms                    = 2,

    /*!
     *  A button-type that will open the mail application
     */
    kSMNotificationButtonType_OpenMail                   = 3,

    /*!
     *  Button that will open a ready to use safari-browser
     */
    kSMNotificationButtonType_OpenBrowser                = 4,

    /*!
     *  Button that will open a third party application
     */
    kSMNotificationButtonType_OpenApplication            = 5,

    /**
     *  Button-type which will allow application rating.
     *  This will behave similarly to kSMNotificationButtonType_OpenApplication
     *  In Android terminology, this notion is called "Store"
     */
    kSMNotificationButtonType_RateApplication            = 6,

    /*!
     *  Button that will trigger a notification (broadcast in Android terminology) inside the application for any interested listener.
     *  You may register in your application to a specific event from NSNotificationCenter. The notification is broadcasted as soon as the push is received.
     *  Your back-end team should inform you about the notification-name.
     *  No parameters are currently supported.
     */
    kSMNotificationButtonType_CustomActionBroadcastEvent = 7,

    /**
     *  Button-type which will allow user to provide back a media-type as answer
     *  Media-type of kind Text
     */
    kSMNotificationButtonType_Return_Text                = 8,

    /**
     *  Button-type which will allow user to provide back a media-type as answer
     *  Media-type of kind Picture
     */
    kSMNotificationButtonType_Return_Photo               = 9,

    /**
     *  Button-type which will allow user to provide back a media-type as answer
     *  Media-type of kind Text + Picture
     */
    kSMNotificationButtonType_Return_TextAndPhoto        = 10,
    
    /**
     *  Button-type which will allow user to add
     */
    kSMNotificationButtonType_Passbook                    = 11
    

};













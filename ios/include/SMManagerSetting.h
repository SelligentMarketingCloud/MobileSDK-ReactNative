//
//  SMManagerSetting.h
//  MobileSDK
//
//  Created by Gauthier Dumont on 12/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SMClearCache.h"

@class SMManagerSettingIAM;
@class SMManagerSettingIAC;
@class SMManagerSettingLocation;


/**
 *  #Note about the SMManagerSetting object :#
 *  Creating an SMManagerSetting's instance is pretty straightforward as there's only [one constructor for doing so](settingWithUrl:ClientID:PrivateKey:).
 *  This sole constructor is sufficent to get you started. 
 *
 *  Additional parameters described in this header will provide you with additional control and ***are all optional***.
 *
 *  #Being user-friendly :#
 *  When the application is in foreground and receive a remote-notification, by default, the library will display it on the current visible UIViewController. This behaviour might be unwanted and may disturb the user if he appears to navigate in a different context. Should you want to prevent that behaviour and display the remote-notification shortly after (when the user will be in a more appropriate context), please follow these steps :
 *
 *  *   Create an SMManagerSetting with the default constructor as usual.
 *  *   Set shouldDisplayRemoteNotification to FALSE.
 *  *   Start the library as usual [SMManager startWithLaunchOptions:Setting:]
 *  *   Listen to NSNotification-name: _kSMNotification_Event_DidReceiveRemoteNotification_ (declared in SMNSNotification)
 *
 *  At this point, remote-notification are NOT displayed when the application is in foreground. (Other application's state are not affected).
 *  Then, displaying the remote-notification is up to the application and can be done at any time by :
 *
 *  *   Retrieve the last remote-notification with [SMManager(RemoteNotification) retrieveLastRemotePushNotification]
 *  *   Display the notification according to its ID with [SMManager(RemoteNotification) displayNotificationID:]
 *
 *  Or, more straightforwardly :
 *
 *  *   Display the last known remote notification by calling : [SMManager(RemoteNotification) displayLastReceivedRemotePushNotification]
 *
 *  #IAM :#
 *  In-Application-Message-service is configurable using SMManagerSettingIAM which you'll inject using the API configureInAppMessageServiceWithSetting:
 *  A dedicated topic regarding this topic can be found in SMManager(InAppMessage)
 *
 *  #IAC :#
 *  In-Application-Content-service is configurable using SMManagerSettingIAC which you'll inject using the API configureInAppContentServiceWithSetting:
 *  A dedicated topic regarding this topic can be found in SMManager(InAppContent)
 *
 *  #SMManagerSetting :#
 *  This class allow you to configure the SMManager.
 *  Such instance must be created before starting the library.
 */
@interface SMManagerSetting : NSObject


/**
 *  Once a new remote-notification is displayed, the badge is automaticly reseted.
 *  Should you want to handle this property yourself, you can set this property to FALSE before starting the library
 *  Default value is set to TRUE
 */
@property (nonatomic) BOOL shouldClearBadge;

/**
 *  Used to configure the remote-notification-display
 *  @discussion  When the app is active, once a new remote-notification is received, it is automatically diplayed on the device
 *  Should you want to prevent that behaviour, you can set this property to FALSE before starting the library.
 *  Default value is set to TRUE.
 *  @warning This property does not have an impact when app is open from a notification selected by user in the notification center or when [SMManager(RemoteNotification) displayNotificationID:] or  [SMManager(RemoteNotification) displayLastReceivedRemotePushNotification] are called.
 *   Once you set this value to TRUE, the application becomes responsable about displaying the remote-notification. (Make sure to read the header file of SMManagerSetting before doing so).
 */
@property (nonatomic) BOOL shouldDisplayRemoteNotification;

/**
 *  This value tells how often the SDK's cache mechanism should clear itself.
 *  @discussion Internally, each notification-messages has a life-span.
 *  Clearing the cache stands for deleting notification-messages with an expired life-span.
 *  In other words, only old notification-messages are deletesd from the cache.
 *  More recent ones are kept in memory until their life-span expires and a new clearCache is called.
 *  By default, this value is set to kSMClearCache_Auto.
 *  Configuring this value highly depends of how frequently the application will query specific notification-messages.
 *  As if the application query a notification-message which is not in the cache anymore, it will automaticaly fetch it from the backend.
 *  In other words, it depends how often you call the API [SMManager(RemoteNotification) displayNotificationID:].
 *
 *  In a nutshell:
 *
 *  *   If the application will never query [SMManager(RemoteNotification) displayNotificationID:], we recommend keeping this value to default.
 *  *   If the application use IAM-service, we recommend keeping this value to default.
 *  *   On the other hand, if the application abuse [SMManager(RemoteNotification) displayNotificationID:], we recommend selecting a value higher than the default one according to your application's need.
 *
 *  @warning As soon as IAM-service is enabled, the SDK will consider kSMClearCache_Weekly as being the default value. Except if you explicitly overide the property.
 *  In 99% of the cases, you should not overide this property as the SDK is smart enough to handle the cache mechanism by itself.
 *  Keep also in mind that this behavior  is only applicable for notification and IAM that doesn't have a n expiration date set
 */
@property (nonatomic) SMClearCache clearCacheIntervalValue;

/**
*  This value provides to the sdk  the app group id that you have previously defined in your apple developer portal.
*  @discussion it is used to allow the sdk to share data between the main app and the notifications extensions (service and/or content)
*  The deviceid provided by selligent mobile platform is stored encrypted in this container
*/
@property (nonatomic, strong) NSString *appGroupId;


/*!
 *  Default-mandatory constructor to start the SMManager shared-instance
 *
 *  @param urlName  NSString instance representing the urlname of your backend.
 *  @param clientID NSString instance referencing the client's ID
 *  @param privateKey NSString instance containing a valid private-key used to secure requests
 *  @warning All these parameters are mandatory.
 *  If any of them is nil, the library won't start. 
 *  Please contact our support to get valid configuration-setting.
 *
 *  @return SMManagerSetting new instance. SMFailure in case of error
 */
+ (instancetype)settingWithUrl:(NSString*)urlName ClientID:(NSString*)clientID PrivateKey:(NSString*)privateKey;

/**
 *  @discussion This call is optional. It is not needed to successfully start the SDK.
 *  However, it is required to enable In-Application-Message.
 *  Please read SMManager(InAppMessage) for additional information.
 *
 *  @param settingIAM The SMManagerSettingIAM instance containing the IAM desired configuration.
 *  @warning An invalid or nil setting is considered as an error and will not startUp the IAM-service.
 *  Don't forget to enable In App message according to application need by calling [SMManager(InAppMessage) enableInAppMessage:]
 */
- (void)configureInAppMessageServiceWithSetting:(SMManagerSettingIAM*)settingIAM;


/**
 *  @discussion This call is optional. It is not needed to successfully start the SDK.
 *  However, it is required to enable In-Application-Content.
 *  Please read SMManager(InAppContent) for additional information.
 *
 *  @param settingIAC The SMManagerSettingIAC instance containing the IAC desired configuration.
 *  @warning An invalid or nil setting is considered as an error and will not startUp the IAC-service.
 *  Don't forget to enable In App content according to application need by calling [SMManager(InAppContent) enableInAppContent:]
 */
- (void)configureInAppContentServiceWithSetting:(SMManagerSettingIAC*)settingIAC;

/**
 *  @discussion This call is optional. It is not needed to successfully start the SDK.
 *  However, it is the first step to enable Location service.
 *  It is the first step to inform the sdk that geo location services are going to be used by the 
 *
 *  @warning To use location service you will need to have PlotProject.framework in your app.
 */
- (void)configureLocationService;

@end

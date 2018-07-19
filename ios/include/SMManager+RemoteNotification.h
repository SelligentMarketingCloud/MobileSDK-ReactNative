//
//  SMManager+RemoteNotification.h
//  MobileSDK
//
//  Created by Samy Ziat on 25/09/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMManager.h"


/**
 *  This category contains the basic step-by-step implementation to get you started.
 *  Make sure to read the category SMManager(SilentPush) to learn more about background-remote-notification.
 *
 *  #Handling Remote Notifications:#
 *  In order to receive remote-notification from the back-end,  all the following methods must be included in you application's delegate:
 *
 *  - didRegisterForRemoteNotificationsWithDeviceToken:
 *  - didRegisterUserNotificationSettings:
 *  - didFailToRegisterForRemoteNotificationsWithError:
 *  - didReceiveRemoteNotification:
 *
 *  Finally, make sure to call registerForRemoteNotification according to your application's need.
 *
 *  #Receiving Remote Notifications:#
 *  When a remote-notification is received, the library will automatically display a custom UIViewController.
 *  Should you want to prevent this behaviour, feel free to configure the SMManagerSetting accordingly before starting the SMManager.
 *
 *  Before displaying the remote-notification's UIVIewController, the library will broadcast an NSNotification offering the application a chance to pause any ongoing heavy task.
 *  The same principle is applied before dismissing the UIVIewController providing the application the opportunity to start again the paused heavy-task.
 *
 *  Finally, should you want to know when the user interact with UIViewController's control, an NSNotification is also posted providing information about the selected element.
 *  For additionnal information about NSNotification processing and handling, please check SMNSNotification
 *
 *  #Displaying notification :#
 *  The application can display any notification based on its ID using the API displayNotificationID:
 *  These IDs can be retrieved from broadcasted NSNotification.
 *  (Please read SMNSNotification for additional information).
 *
 *  A convenient method is provided to display the last received remote-notification using displayLastReceivedRemotePushNotification
 *
 *  #SMManager+RemoteNotification :#
 *
 */
@interface SMManager (RemoteNotification)




/*!
 *  Mandatory method which allows notification registration
 *
 *  @discussion This API will display a dialog asking user's permission for remote-notifications (when app is launched the very 1st time).
 *  Often, this call is added right after startWithLaunchOptions:Setting:
 *  However, you may call this API later in your code according to your application need. Just remember that this call is mandatory to receive remote-notifications
 *  @warning If your device has already been registered to remote-notifications by your application or a third-party framework, then this call is not mandatory.
 */
- (void)registerForRemoteNotification;


/**
 *  Use this API to unregister the current device. In other words, the device will not receive any remote-notification from our backend server anymore.
 *  @warning This does NOT call unregisterForRemoteNotifications on the sharedApplication instance.
 *  Therefore, the application can still receive third-party remote-notifications.
 */
- (void)unregisterForRemoteNotification;



/*!
 *  Mandatory API to be included in application:didRegisterForRemoteNotificationsWithDeviceToken:
 *
 *  @param deviceToken A string that identifies the device to APNs.
 *  @discussion This method is mandatory to handle properly all notifications
 */
- (void)didRegisterForRemoteNotificationsWithDeviceToken:(NSData*) deviceToken;


/*!
 *  @warning Deprecated method - replaced by  didRegisterUserNotificationSettings;
 *  Mandatory API to be included in application:didRegisterUserNotificationSettings
 *
 *  @param notificationSettings The user notification settings that are available to your app.
 *  @discussion This method confirms the type of notification the user would like to receive.
 */
- (void)didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings __deprecated;


/*!
 *  Mandatory API to be included in application:didRegisterUserNotificationSettings
 *
 *  @discussion This method confirms the type of notification the user would like to receive.
 */
- (void)didRegisterUserNotificationSettings;



/*!
 *  Mandatory API to be included in application:didFailToRegisterForRemoteNotificationsWithError
 *
 *  @param error An NSError object that encapsulates information why registration did not succeed. Provided by the delegate call
 *  @discussion Called when the user has deactivated remote-notification or if any other error happen.
 */
- (void)didFailToRegisterForRemoteNotificationsWithError:(NSError *)error;


/*!
 *  Mandatory API to be included in application:didReceiveRemoteNotification
 *  Handle and display remote notification when application is in foreground
 *
 *  @param userInfo An NSDictionary that contains information related to the remote notification. Provided by the delegate call
 *  @discussion This method is not mandatory anymore if you implement didReceiveRemoteNotification:fetchCompletionHandler:
 *  For additional information about background-remote-notifications, please check SMManager(SilentPush) for further details.
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo;

/**
 *  Display a notification based on its ID
 *
 *  @param idNotification NSString instance referencing the unique notification's ID
 *  @discussion Basically, the application may store notification's IDs and then display them according to its need.
 *  In this context, the word "notification" stands for either a remote-notification or an InAppMessage.
 *  This feature has initially been added to allow applications to display remote-notifications at any time (not directly when the push is received).
 *  Then, it has been extended to display In-App-Messages. For additional information about IAM, please read SMManager(InAppMessage).
 */
- (void)displayNotificationID:(NSString*)idNotification;


/**
 *  Retrieve and display the last known notification.
 *
 *  @discussion Basically, This API is a helpher which combine both retrieveLastRemotePushNotification and displayNotificationID:
 *  It only focuses on remote-notification. Not on IAM.
 *  At this stage, only the very last remote-notification can be recovered, previous ones are automaticly overriden.
 *  To learn more about this API, please read documentation in [SMManagerSetting](SMManagerSetting), more particularly [SMManagerSetting shouldDisplayRemoteNotification]
 */
- (void)displayLastReceivedRemotePushNotification;



/**
 *  Retrieve information about the last received remote-notification
 *
 *  @return NSDictionary instance containing basic information about the last push, nil if no push was received so far.
 *  @discussion This is a convinient method to quickly retrieve the last remote-notificaiton known by the device.
 *  At this stage, only the very last remote-notification can be recovered, previous ones are automaticly overriden.
 *  To learn more about this API, please read documentation in [SMManagerSetting](SMManagerSetting), more particularly [SMManagerSetting shouldDisplayRemoteNotification]
 */
- (NSDictionary*)retrieveLastRemotePushNotification;



@end

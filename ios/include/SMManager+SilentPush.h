//
//  SMManager+SilentPush.h
//  MobileSDK
//
//  Created by Samy Ziat on 25/09/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMManager+RemoteNotification.h"


/**
 *  Optionally, you can support silent-remote-notificaiton which will not render anything on the device.
 *  To know more about this topic, please visit [the Apple documentation.](https://developer.apple.com/library/ios/documentation/NetworkingInternet/Conceptual/RemoteNotificationsPG/Chapters/ApplePushService.html#//apple_ref/doc/uid/TP40008194-CH100-SW1)
 *
 *  Even if you're not planning to use silent-pushes, we recommand enabling this service in your application anyway.
 *  As using this service will also improve rendering time for the usual (non-silent) remote-notifications.
 *
 *  #Implementation :#
 *  In a nutshell, you should do the following :
 *
 *  *   In the application's target, enable the following: Capabilities > Background Modes > Remote Notifications
 *  *   Removing previous call to didReceiveRemoteNotification: (see last point of "Start library")
 *  *   Implement didReceiveRemoteNotification:fetchCompletionHandler: in UIApplication's delegate.
 *
 *  #SMManager+SilentPush :#
 */
@interface SMManager (SilentPush)






/**
 *  Mandatory API to be included in application:didReceiveRemoteNotification:fetchCompletionHandler
 *  Handle and display the received notification according to different application state.
 *
 *  @param userInfo An NSDictionary that contains information related to the remote notification. Provided by the delegate call
 *  @param completionHandler The block-completion to be processed after the download. Provided by the delegate call
 *  @discussion It is recommended to use this API over didReceiveRemoteNotification: as it handles silent-remote-notificaitons.
 *  @warning You must enable "Remote notifications" in your application's Capabilities in order to use this API. 
 *  If this capability is not usefull to your application, you must use didReceiveRemoteNotification: instead.
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler;



/**
 *  See didReceiveRemoteNotification:fetchCompletionHandler:
 *
 *  @param userInfo An NSDictionary that contains information related to the remote notification. Provided by the delegate call
 *  @param completionHandler The block-completion to be processed after the download. Provided by the delegate call
 *  @param resultFetch The enumeration that might be overiden by application if needed
 *  @discussion This API is provided in order to force the fetch result to a specific value. 
 *  Use it only if your application need to overide the service. 
 *  Otherwise, please use didReceiveRemoteNotification:fetchCompletionHandler:
 *  @warning You must enable "Remote notifications" in your application's Capabilities in order to use this API.
 *  If this capability is not usefull to your application, you must use didReceiveRemoteNotification: instead.
 */
- (void)didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler ForceResultFetch:(UIBackgroundFetchResult)resultFetch;








@end

//
//  SellMobileSDK.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 17/04/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "SMManagerHelper.h"

@class SMManagerSetting;

/*!
 *  ##Start Library
 *  In order to start the library, please follow the steps bellow (will mainly happen in your UIApplication's delegate):
 *
 *  -   Use startWithLaunchOptions:Setting: in your application:didFinishLaunchingWithOptions:
 *  -   Implement methods described in SMManager(RemoteNotification) in your UIApplication's delegate
 *  -   When building against iOS10 : Implement methods described in SMManager(UserNotification) in your UIApplication's delegate
 *
 *  Starting the library will not register for remote notification.
 *  Don't forget to call registerForRemoteNotification according to your application's need.
 *
 *  From there, your application is ready to handle all incoming remote-notifications.
 */
@interface SMManager : NSObject

/**
 *  The current version of the library
 */
@property (readonly, nonatomic) NSString *_Nonnull versionLib;

/*!
 * Singleton for SellMobileSDK Class which allow to access public SellMobileSDK methods and properties
 *
 * @return SMManager: singleton instance of SMManager class
 */
+ (instancetype _Nonnull) sharedInstance;

/*!
 *  Mandatory method which allows sdk initialisation. To be included in application:didFinishLaunchingWithOptions: 
 *  Make sure to provide the launchOptions dictionary
 *
 *  @param launchOptions NSDictionary instance indicating the reason the app was launched (if any). This dictionary is provided by application:didFinishLaunchingWithOptions
 *  @param setting  mandatory SMManagerSetting instance to start-up the library
 *  @see SMManagerSetting
 *  @discussion This method is mandatory in order to start / initialise the library and should be called in application:didFinishLaunchingWithOptions:
 */
- (void) startWithLaunchOptions:(NSDictionary* _Nullable)launchOptions Setting:(SMManagerSetting* _Null_unspecified)setting;

/*!
 *  Optional + used for testing only. This method will re-configure the SMManager with the newly provided information
 *
 *  @discussion This is a handy API in case you would like to switch between two backend environements without rebuilding your target.
 *  @param setting  mandatory SMManagerSetting instance to start-up the library
 *  @warning This API is provided for testing purposes only. Never use it in production.
 *  Make sure to re-enable any service after calling this API.
 *  @see SMManagerSetting
 */
- (void) reloadSetting:(SMManagerSetting* _Null_unspecified)setting;

/*!
 *  Device id  used by the sdk
 */
- (NSString*_Nullable) deviceID;

 @end

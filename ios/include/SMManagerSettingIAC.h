//
//  SMManagerSettingIAC.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 11/03/16.
//  Copyright © 2016 Selligent. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "SMInAppRefreshType.h"

/**
 *  This class allow you to configure the In-App-Content service.
 *  Such instance must be created before starting the library.
 */
@interface SMManagerSettingIAC : NSObject




/**
 *  Constructor to be used in order to create the SMManagerSettingIAC instance
 *  @discussion use this constructor to enable background-mode only.
 *  The OS will refresh automaticly the IAC based on how often the user interacts with the application
 *  @warning If background-fetch is not enabled in Application's Capabilities, the IAC-service will not start.
 *  See SMManager(InAppContent) for additional information.
 */
+ (instancetype)settingWithBackgroundFetchOnly;



/**
 *  Constructor to be used in order to create the SMManagerSettingIAC instance
 *
 *  @param refreshType The type of refresh to consider when the application is in foreground
 *  @discussion Use this constructor should you want to perform periodic refresh when the application is in foreground-state only.
 *  For enabling backgroundState, use settingWithRefreshType:ShouldPerformBackgroundFetch: instead
 */
+ (instancetype)settingWithRefreshType:(SMInAppRefreshType)refreshType;




/**
 *  Constructor to be used in order to create the SMManagerSettingIAC instance
 *
 *  @param refreshType                  The type of refresh to consider when the application is in foreground
 *  @param shouldPerformBackgroundFetch If set to TRUE, it will activate UIApplication-BackGround-Fetch-mode automaticly
 *  @discussion This constructor provides you with more control on foreground / background fetch.
 *  Should you want to restrict to only one fetch-mode, feel free to use other constructors.
 */
+ (instancetype)settingWithRefreshType:(SMInAppRefreshType)refreshType ShouldPerformBackgroundFetch:(BOOL)shouldPerformBackgroundFetch;





@end

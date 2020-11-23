//
//  SMManagerSettingIAM.h
//  MobileSDK
//
//  Created by Samy Ziat on 30/09/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SMInAppRefreshType.h"

/**
 *  This class allow you to configure the In-App-Message service.
 *  Such instance must be created before starting the library.
 */
@interface SMManagerSettingIAM : NSObject




/**
 *  Constructor to be used in order to create the SMManagerSettingIAM instance
 *  @discussion use this constructor to enable background-mode only. 
 *  The OS will refresh automaticly the IAM based on how often the user interacts with the application
 *  @warning If background-fetch is not enabled in Application's Capabilities, the IAM-service will not start.
 *  See SMManager(InAppMessage) for additional information.
 */
+ (instancetype)settingWithBackgroundFetchOnly;



/**
 *  Constructor to be used in order to create the SMManagerSettingIAM instance
 *
 *  @param refreshType The type of refresh to consider when the application is in foreground
 *  @discussion Use this constructor should you want to perform periodic refresh when the application is in foreground-state only.
 *  For enabling backgroundState, use settingWithRefreshType:ShouldPerformBackgroundFetch: instead
 */
+ (instancetype)settingWithRefreshType:(SMInAppRefreshType)refreshType;




/**
 *  Constructor to be used in order to create the SMManagerSettingIAM instance
 *
 *  @param refreshType                  The type of refresh to consider when the application is in foreground
 *  @param shouldPerformBackgroundFetch If set to TRUE, it will activate UIApplication-BackGround-Fetch-mode automaticly
 *  @discussion This constructor provides you with more control on foreground / background fetch.
 *  Should you want to restrict to only one fetch-mode, feel free to use other constructors.
 */
+ (instancetype)settingWithRefreshType:(SMInAppRefreshType)refreshType ShouldPerformBackgroundFetch:(BOOL)shouldPerformBackgroundFetch;





@end

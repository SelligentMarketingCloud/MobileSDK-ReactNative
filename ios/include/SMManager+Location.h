//
//  SMManager+Location.h
//  MobileSDK
//
//  Created by Samy Ziat on 02/12/15.
//  Copyright © 2015 Selligent. All rights reserved.
//

#import "SMManager.h"

#import "SMLocationAuthorisationType.h"

/*!
 *  #Introduction :#
 *  Location is an optional service which will **automatically** provide with user's location-information.
 *  Location-information are provided at regular intervals according to provided configuration.
 *
 *  This information is not granted! Users may decide to share their location and then, few days afterwards, stop sharing it.
 *  The SDK will *automatically* inform the back-end of any permission changes.
 *
 *  #Implementation :#
 *  In order to correctly start the location-service, please follow these steps :
 *
 *  - Add a key-value pair in your info-plist-file (Additional details in the section below).
 *  - Optional step depending on the value of the enableOnFirstRun in your plotconfig.json file: if set to false you will have to enableGeoLocation
 *  - Finally, you can call requestLocationAuthorisation: to ask user permissions according to your application's need.
 *
 *  #Accessing User Data :#
 *  Requesting user's authorisation is a mandatory step to access their location-information.
 *  The dialogue asking for this permission will only be displayed once in the application life cycle.
 *
 *  If user denies sharing location-information, the application can NOT display the dialogue a 2nd time.
 *  Thus, he'll have to manually access the Settings-application and enable location sharing from there.
 *
 *  #Configuring Info-Plist :#
 *  For the reason stated above, it is extremely important to explain to users the exact reason why to access their location information.
 *  A key-value pair explaining that reason must be added to the application's Info-Plist-file.
 *
 *  The **Key** depends on SMLocationAuthorisationType used :
 *
 *  - For kSMLocationAuthorisationType_InUse use **NSLocationWhenInUseUsageDescription**
 *  - For kSMLocationAuthorisationType_Always use **NSLocationAlwaysUsageDescription** or **NSLocationAlwaysAndWhenInUseUsageDescription** since iOS11
 *
 *  The **Value** represents the string-sentence that will be displayed in the alert.
 *
 *  To know more about Plist-configuration, please see [Apple documentation](https://developer.apple.com/library/ios/documentation/General/Reference/InfoPlistKeyReference/Articles/CocoaKeys.html#//apple_ref/doc/uid/TP40009251-SW18).
 *  Also, Apple does provide [few guidelines](https://developer.apple.com/library/ios/documentation/UserExperience/Conceptual/MobileHIG/LocationServices.html) for displaying the string-sentence.
 *
 *
 *  #SMManager+Location :#
 */
@interface SMManager (Location)

/**
 *  @return The current authorisation status for this application.
 *  @discussion Please check SMLocationAuthorisationStatus to understand each case.
 *  @warning If this value is kSMLocationAuthorisationStatus_Refused --> Users must activate location from Settings-Application.
 *  Alerts are only displayed once!
 */
- (SMLocationAuthorisationStatus)currentAuthorisationStatus;


/**
 *  Ask user's permission to share his location
 *
 *  @param type The requested location-authorisation-type check SMLocationAuthorisationType to understand each type.
 *  @discussion This call will display an alert requesting user's location-information. 
 *  The alert will only be displayed once. However, it may no harm to make this call several times.
 *  Call this API according to your application's need.
 */
- (void)requestLocationAuthorisation:(SMLocationAuthorisationType)type;

/**
 *  Enable geolocation services
 *
 *  @discussion This optional call will enable geolocation services at sdk level. it is independent of iOS location authorisation
 *  If you use plotproject for geolocation it will be mandatory to call it if you have set enableOnFirstRun to false in the plotconfig.json
 *  Call this API according to your application's need.
 */
-(void) enableGeoLocation;

/**
 *  Disable geolocation services
 *
 *  @discussion This optional call will disable geolocation services at sdk level. it is independent of iOS location authorisation
 *  Call this API according to your application's need.
 */
-(void) disableGeoLocation;


/**
 *  check geolocation services status
 *
 *  @discussion This optional call will inform you if geolocation services at sdk level are enabled. it is independent of iOS location authorisation
 */
-(BOOL) isGeoLocationEnabled;
@end

//
//  SMManager+Location.h
//  MobileSDK
//
//  Created by Samy Ziat on 02/12/15.
//  Copyright © 2015 Selligent. All rights reserved.
//

#import "SMManager.h"

/*!
 *  In order to use the location services features provided by the sdk you will mandatory need to use the lsdk library supporting the plotproject framework .
 *  Otherwise calling the method in this SMManager category will have no effect and no ios api related to geofencing will be called (as this is all done by the plot project framework)
 */
@interface SMManager (Location)

/**
 *  Enable geolocation services
 *
 *  @discussion This optional call will enable geolocation services at sdk level. it is independent of iOS location authorisation
 *  If you use plotproject for geolocation it will be mandatory to call it if you have set enableOnFirstRun to false in the plotconfig.json
 *  Call this API according to your application's need.
 */
- (void) enableGeoLocation;

/**
 *  Disable geolocation services
 *
 *  @discussion This optional call will disable geolocation services at sdk level. it is independent of iOS location authorisation
 *  Call this API according to your application's need.
 */
- (void) disableGeoLocation;

/**
 *  Check the geolocation services status
 *
 *  @discussion This optional call will inform you if geolocation services at sdk level are enabled. it is independent of iOS location authorisation
 */
- (BOOL) isGeoLocationEnabled;

@end

//
//  SMManagerSetting+Location.h
//  MobileSDK
//
//  Created by Marc Biosca on 6/28/21.
//  Copyright © 2021 Selligent. All rights reserved.
//

#import "SMManagerSetting.h"

/**
 *  This category will help you to enable the geolocation service.
 */
@interface SMManagerSetting (Location)

/**
 *  Optional API to enable location services.
 *
 *  @discussion This call is useless if the sdk version is not the one associated to the plotproject framework
 *  However in the case you are using the sdk version associated to plotproject framework, it is the first step to enable Location service.
 *  It is the first step to inform the sdk that geo location services are going to be used by the
 *
 *  @warning To use location service you will mandatory need to have PlotProject.framework in your app and the correct version of the selligent sdk library
 */
- (void) configureLocationService;

@end

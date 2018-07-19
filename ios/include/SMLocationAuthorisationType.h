//
//  SMLocationAuthorisationType.h
//  MobileSDK
//
//  Created by Samy Ziat on 08/12/15.
//  Copyright © 2015 Selligent. All rights reserved.
//

typedef NS_ENUM(NSInteger, SMLocationAuthorisationType) {
    /**
     *  This value asks user permission to monitor their position
     *  only when the application is being used.
     *  Highly encouraged by Apple for efficiency purposes.
     */
    kSMLocationAuthorisationType_InUse,
    
    /**
     *  This value asks user permission to monitor their position
     *  for all application's state.
     *  Use this option only if your application needs it.
     */
    kSMLocationAuthorisationType_Always
};




typedef NS_ENUM(NSInteger, SMLocationAuthorisationStatus) {
    /**
     *  The authorisation satus is unknown.
     */
    kSMLocationAuthorisationStatus_Unknown,
    
    /**
     *  The authorisation status is rejected by user or impossible
     */
    kSMLocationAuthorisationStatus_Refused,
    
    /**
     *  The authorisation status is OK when the application is in-use
     */
    kSMLocationAuthorisationStatus_GrantedInUse,
    
    /**
     *  The authorisation status is OK for all application's state
     */
    kSMLocationAuthorisationStatus_GrantedAlways
};





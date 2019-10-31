//
//  SMClearCache.h
//  MobileSDK
//
//  Created by Samy Ziat on 09/10/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//


/**
 *  Enumeration used to define how often the SDK's cache should automaticaly clear itself
 *  #SMClearCache :#
 */
typedef NS_ENUM(NSInteger, SMClearCache) {
    /**
     *  This is the default value.
     */
    kSMClearCache_Auto,
    /**
     *  This explicitely disable the SDK-cache mechanism
     */
    kSMClearCache_None,
    /**
     *  Clear the cache weekly
     */
    kSMClearCache_Week,
    /**
     *  Clear the cache each month
     */
    kSMClearCache_Month,
    /**
     *  Clear the cache every three months
     */
    kSMClearCache_Quarter,
};


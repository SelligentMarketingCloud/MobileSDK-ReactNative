//
//  RNSelligentMapper.h
//  SelligentDevAppRN
//
//  Created by Marc Biosca on 16/5/23.
//  Copyright © 2023 Facebook. All rights reserved.
//

#if __has_include(<React/RCTBridgeModule.h>)
    #import <React/RCTBridgeModule.h>
    #import <React/RCTEventEmitter.h>
#else
    #import "RCTBridgeModule.h"
    #import <RCTEventEmitter.h>
#endif

@import RNSelligentMobileSDK;

@interface RNSelligentMapper : RCTEventEmitter <RCTBridgeModule, RNSelligentEventHandlerProtocol>

@end

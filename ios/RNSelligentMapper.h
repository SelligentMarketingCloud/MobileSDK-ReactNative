#if __has_include(<React/RCTBridgeModule.h>)
    #import <React/RCTBridgeModule.h>
    #import <React/RCTEventEmitter.h>
#else
    #import "RCTBridgeModule.h"
    #import <RCTEventEmitter.h>
#endif

@import RNSelligentMobileSDK;

@interface RNSelligentMapper : RCTEventEmitter <RCTBridgeModule, RNSelligentEventHandlerProtocol>

@property (nonatomic) BOOL listeningEvents;
@property (nonatomic) NSMutableArray * pendingEvents;

@end

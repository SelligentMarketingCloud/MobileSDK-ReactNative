#import "RNSelligentMapper.h"

@implementation RNSelligentMapper

RCT_EXPORT_MODULE(RNSelligent)

- (instancetype) init {
  self = [super init];
  
  RNSelligent.eventDelegate = self;
  
  return self;
}

+ (BOOL) requiresMainQueueSetup {
  return true;
}

#pragma mark - Helpers

RCT_EXPORT_METHOD(getVersionLib:(RCTResponseSenderBlock)callback) {
  callback(@[[RNSelligent getVersionLib], [NSNull null]]);
}

RCT_EXPORT_METHOD(getDeviceId:(RCTResponseSenderBlock)callback) {
  callback(@[[RNSelligent getDeviceId], [NSNull null]]);
}

RCT_EXPORT_METHOD(executePushAction) {
  [RNSelligent executePushAction];
}

RCT_EXPORT_METHOD(applyLogLevel:(NSArray<NSNumber *> *)logLevels) {
  [RNSelligent applyLogLevel:logLevels];
}

#pragma mark - Push

RCT_EXPORT_METHOD(enableNotifications:(BOOL)enable) {
  [RNSelligent enableNotifications:enable];
}

RCT_EXPORT_METHOD(registerForProvisionalRemoteNotification) {
  [RNSelligent registerForProvisionalRemoteNotification];
}

RCT_EXPORT_METHOD(displayLastReceivedNotification) {
  [RNSelligent displayLastReceivedNotification];
}

RCT_EXPORT_METHOD(displayLastReceivedRemotePushNotification:(NSString *)templateId) {
  [RNSelligent displayLastReceivedRemotePushNotificationWithTemplateId:templateId];
}

RCT_EXPORT_METHOD(getLastRemotePushNotification:(RCTResponseSenderBlock)callback) {
  callback(@[[RNSelligent getLastRemotePushNotification] ?: [NSNull null], [NSNull null]]);
}

#pragma mark - IAM

RCT_EXPORT_METHOD(enableInAppMessages:(BOOL)enabled) {
  [RNSelligent enableInAppMessages:enabled];
}

RCT_EXPORT_METHOD(areInAppMessagesEnabled:(RCTResponseSenderBlock)callback) {
  callback(@[@([RNSelligent areInAppMessagesEnabled]), [NSNull null]]);
}

RCT_EXPORT_METHOD(getInAppMessages:(RCTResponseSenderBlock)callback) {
  callback(@[[RNSelligent getInAppMessages] ?: [NSNull null], [NSNull null]]);
}

RCT_EXPORT_METHOD(setInAppMessageAsSeen:(NSString *)messageId successCallback:(RCTResponseSenderBlock)successCallback errorCallback:(RCTResponseSenderBlock)errorCallback) {
  NSString* errorMessage = [RNSelligent setInAppMessageAsSeen:messageId seen:true];
  
  if (errorMessage) {
    errorCallback(@[errorMessage]);
    return;
  }
  
  successCallback(@[[NSNull null]]);
}

RCT_EXPORT_METHOD(setInAppMessageAsUnseen:(NSString *)messageId successCallback:(RCTResponseSenderBlock)successCallback errorCallback:(RCTResponseSenderBlock)errorCallback) {
  NSString* errorMessage = [RNSelligent setInAppMessageAsSeen:messageId seen:false];
  
  if (errorMessage) {
    errorCallback(@[errorMessage]);
    return;
  }
  
  successCallback(@[[NSNull null]]);
}

RCT_EXPORT_METHOD(setInAppMessageAsDeleted:(NSString *)messageId successCallback:(RCTResponseSenderBlock)successCallback errorCallback:(RCTResponseSenderBlock)errorCallback) {
  NSString* errorMessage = [RNSelligent setInAppMessageAsDeleted:messageId];
  
  if (errorMessage) {
    errorCallback(@[errorMessage]);
    return;
  }
  
  successCallback(@[[NSNull null]]);
}

RCT_EXPORT_METHOD(executeButtonAction: (NSString *)buttonId messageId:(NSString *)messageId successCallback:(RCTResponseSenderBlock)successCallback errorCallback:(RCTResponseSenderBlock)errorCallback) {
  NSString* errorMessage = [RNSelligent executeButtonAction:buttonId messageId:messageId];
  
  if (errorMessage) {
    errorCallback(@[errorMessage]);
    return;
  }
  
  successCallback(@[[NSNull null]]);
}

RCT_EXPORT_METHOD(displayNotification:(NSString *)notificationId templateId:(NSString *)templateId) {
  [RNSelligent displayNotification:notificationId templateId:templateId];
}

#pragma mark - Events

RCT_EXPORT_METHOD(sendEvent:(NSDictionary *)data successCallback:(RCTResponseSenderBlock)successCallback errorCallback:(RCTResponseSenderBlock)errorCallback) {
  [RNSelligent sendEvent:data completion:^(BOOL status, NSString *message) {
    if (status) {
      successCallback(@[message, [NSNull null]]);
      return;
    }
    
    errorCallback(@[message, [NSNull null]]);
  }];
}

RCT_EXPORT_METHOD(subscribeToEvents:(NSArray<NSString *> *)events) {
  [RNSelligent subscribeToEvents:events];
}

- (void) sendBroadcastEventWithName:(NSString * _Nonnull)name type:(NSString * _Nonnull)type data:(NSDictionary * _Nullable)data {
  [self sendEventWithName:name body:@{@"data": data ?: [NSNull null], @"broadcastEventType": type}];
}

- (NSArray<NSString *> *) supportedEvents {
    return @[
        @"ButtonClicked",
        @"ReceivedInAppMessage",
        @"WillDisplayNotification",
        @"WillDismissNotification",
        @"ReceivedRemoteNotification",
        @"ReceivedDeviceId",
        @"UniversalLinkExecuted",
        @"TriggeredCustomEvent",
        @"DisplayingInAppMessage"
     ];
}

@end

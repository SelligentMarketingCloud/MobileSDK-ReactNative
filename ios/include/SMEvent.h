//
//  SMEvent.h
//  MobileSDK
//
//  Created by Gilbert Schakal on 03/06/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SMFailure.h"
#import "SMSuccess.h"

/*!
 * This is the Base class for all type of events
 */
@interface SMEvent : NSObject

/*!
 *  Confirm if the current event should be cached or not
 *  @discussion If the event fail to be delivered to your backend, then by default, it is cached into an internal queue.
 *  After a while, the library will automaticly try to send it again.
 *  Should you want to prevent this behaviour, feel free to set this property to FALSE.
 *  By default, it is set to TRUE
 */
@property (nonatomic) BOOL shouldCache;

/*!
 *  Create a generic event object that will be sent to platform
 *
 *  @param dict A Dictionary containing any kind of custom datas that must be stored and managed by platform
 *  @return An SMEvent object
 */
+ (instancetype _Nonnull) eventWithDictionary:(NSDictionary* _Nullable)dict;

/*!
 *  Allow to initialise a success block and/or a failure block that will be triggered after an event is sent to the platform
 *
 *  @param blockSuccess An SMCompletionBlockSuccess block that will be triggered if the send to the platform is successfull
 *  @param blockFailure An SMCompletionBlockFailure block that will be triggered if the send to the platform has failed
 *  @discussion This method may be used as follow:
 *
 *  @code
 *  NSDictionary *dictMyCustomData = @{@"MyKey": @"MyValue"};
 *
 *  SMEvent *event = [SMEvent eventWithDictionary:dictMyCustomData];
 *
 *  [event applyBlockSuccess:^(SMSuccess *success) {
 *
 *  //  My code for success}
 *
 *  BlockFailure:^(SMFailure *failure) {
 *
 *  //  My code for failure }];
 *
 *  [[SMManager sharedInstance] sendSMEvent:event];
 *  @endcode
 *  
 *  This method is optional. Use it only if you need it.
 *  @warning It is developer's responsability to make sure no strong retrain cycles are added to the completion-blocks.
 *  Make sure to read the following [Apple documentation.](https://developer.apple.com/library/ios/documentation/Cocoa/Conceptual/ProgrammingWithObjectiveC/WorkingwithBlocks/WorkingwithBlocks.html#//apple_ref/doc/uid/TP40011210-CH8-SW16)
 *  @see SMCompletionBlockSuccess
 *  @see SMCompletionBlockFailure
 */
- (void) applyBlockSuccess:(SMCompletionBlockSuccess _Nullable)blockSuccess BlockFailure:(SMCompletionBlockFailure _Nullable)blockFailure;

@end



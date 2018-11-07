#import <Foundation/Foundation.h>
#import "Event.h"
#import "SMFailure.h"
#import "SMSuccess.h"
#import "SMBlock.h"

@class SMEvent;

@interface Event (SMEvent)

- (SMEvent *)smEventWithBlockSuccess:(SMCompletionBlockSuccess)blockSuccess BlockFailure:(SMCompletionBlockFailure)blockFailure;

@end

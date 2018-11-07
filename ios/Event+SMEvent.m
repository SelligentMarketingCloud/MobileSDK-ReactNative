#import "Event+SMEvent.h"
#import "SMEvent.h"
#import "SMEventUserRegistration.h"
#import "SMEventUserUnregistration.h"
#import "SMEventUserLogin.h"
#import "SMEventUserLogout.h"

@implementation Event (SMEvent)

- (SMEvent *)smEventWithBlockSuccess:(SMCompletionBlockSuccess)blockSuccess BlockFailure:(SMCompletionBlockFailure)blockFailure {
    SMEvent *event;

    switch (self.type) {
        case etRegister:
            event = [SMEventUserRegistration eventWithEmail:self.email Dictionary:self.data];
            break;

        case etUnregister:
            event = [SMEventUserUnregistration eventWithEmail:self.email Dictionary:self.data];
            break;

        case etUserLogin:
            event = [SMEventUserLogin eventWithEmail:self.email Dictionary:self.data];
            break;

        case etUserLogout:
            event = [SMEventUserLogout eventWithEmail:self.email Dictionary:self.data];
            break;

        default:
            event = [SMEvent eventWithDictionary:self.data];
            break;
    }

    [event applyBlockSuccess:blockSuccess BlockFailure:blockFailure];

    return event;

}

@end

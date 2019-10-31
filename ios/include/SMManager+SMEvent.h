//
//  SMManager+SMEvent.h
//  MobileSDK
//
//  Created by Samy Ziat on 25/09/15.
//  Copyright (c) 2015 Selligent. All rights reserved.
//

#import "SMManager.h"

@class SMEvent;

/**
 *  #Sending events :#
 *  Sending any set of data to the back-end can be done with the API sendSMEvent:
 *
 *  #Event type :#
 *  Few default events are already available for you to be used. 
 *  They all inhirit from SMEvent and are configurable through their constructors.
 *  At the time of this writing, they default provided events are :
 *
 *  * SMEventUserLogin
 *  * SMEventUserLogout
 *  * SMEventUserRegistration
 *  * SMEventUserUnregistration
 *
 *  #Custom events :#
 *  Simplest case is to create an instance of SMEvent.
 *  Then, inject your data in it (Code example bellow).
 *
 *  Also, you can subclass from default provided event-type or even create your own sub-classes of events.
 *
 *  The library will keep sending events to the backend as far as they inhirit from SMEvent.
 *
 *  #Injecting custom data in events :#
 *  Any information can be appended to an event and sent to your back-end.
 *  This is basically done by creating a dictionary containing your data and injecting it as in the example bellow.
 *
 *
 *  @code
 *  //  Dictionary with your custom data
 *  NSDictionary *dictMyCustomData = @{@"MyKey": @"MyValue"};
 *  //  Create the event
 *  SMEvent *event = [SMEvent eventWithDictionary:dictMyCustomData];
 *  //  Sent the event to the back-end
 *  [[SMManager sharedInstance] sendSMEvent:event];
 *  @endcode
 *
 *  The exemple above is considered as a custom event.
 *  The same principle can be applied to any event-type subclasses stated above or to your own subclasses of SMEvent.
 *
 *  #SMManager+SMEvent :#
 */
@interface SMManager (SMEvent)



/*!
 *  Send an event to the Selligent platform
 *
 *  @param event An SMEvent object containing your event
 *  @discussion Should you want to track the event's response, please check SMEvent
 */
- (void)sendSMEvent:(SMEvent*)event;


@end

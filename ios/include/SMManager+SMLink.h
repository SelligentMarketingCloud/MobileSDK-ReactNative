//
//  SMManager+SMLink.h
//  MobileSDK
//
//  Created by Marc Biosca on 7/12/21.
//  Copyright © 2021 Selligent. All rights reserved.
//

#import "SMManagerUniversalLinksDelegate.h"

@class SMNotificationMessage;
@class SMLink;

/**
 *  This category will help you to manage specific behaviour related to SMLink.
 */
@interface SMManager (SMLink)

/**
 *  Used to let the app manage the behaviour of "deeplink" button types containing universal links.
 *
 *  @param delegate  An object implementing SMManagerUniversalLinksDelegate methods
 *  @discussion This setting will allow you to manage the behaviour of the click in a "deeplink" button type that contains an universal link.
 *  In order to do it, the delegate object should implement [SMManagerUniversalLinksDelegate executeLinkAction:] method, it will provide the app with the defined NSURL.
 *  @see SMManagerUniversalLinksDelegate
 */
- (void) universalLinksDelegate:(id <SMManagerUniversalLinksDelegate>_Nullable) delegate;

/**
 *  Tells to the SDK that a certain SMLink object has been clicked.
 *  The SDK will send a clicked event to the Selligent platform.
 *
 *  @param link  SMLink that needs to be marked as clicked.
 *  @param notificationMessage The SMNotificationMessage from where the link was extracted.
 *  @discussion This is a convinient method when the behaviour when receiving a remote-notification is handled at App side
 *  and the standard events need to be sent back to the Selligent platform.
 *  @warning The App will be fully responsible of possible event duplication in the Selligent platform when implementing this method,
 *  as each execution will trigger a new event, so make sure to just trigger it once if you don't want this to happen.
 *  @see SMLink
 *  @see SMNotificationMessage
 */
- (void) setLinkAsClicked:(SMLink*_Nullable)link fromMessage:(SMNotificationMessage*_Nullable)notificationMessage;

@end

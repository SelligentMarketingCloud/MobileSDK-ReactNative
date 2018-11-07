




/**
 *  NSString representing a notification name you can listen to.
 *  An NSNotification with this name is broadcasted when the user interacts with a remote-notification
 *  Usefull to retrieve user's actions on a received remote-notification, developers may listen to kSMNotification_Event_ButtonClicked from NSNotificationCenter.
 */
extern NSString* kSMNotification_Event_ButtonClicked;

/**
 *  NSString representing a notification name you can listen to.
 *  An NSNotification with this name is broadcasted shortly before displaying a remote-notification
 *  Primary-application may use this notification to pause any ongoing work before the remote-notification is displayed.
 *  This notification-name is also triggered even if you disable shouldDisplayRemoteNotification (see SMManagerSetting).
 */
extern NSString* kSMNotification_Event_WillDisplayNotification;

/**
 *  NSString representing a notification name you can listen to.
 *  An NSNotification with this name is broadcasted shortly before Dismissing the current remote-notification
 *  Primary-application may use this notification to resume any paused work. (see kSMNotification_Event_WillDisplayNotification)
 */
extern NSString* kSMNotification_Event_WillDismissNotification;


/**
 *  NSString representing a notification name you can listen to.
 *  An NSNotification with this name is broadcasted shortly after receiving a remote-notification
 *  Primary-application may use this notification to decide when to display any remote-notification
 */
extern NSString* kSMNotification_Event_DidReceiveRemoteNotification;

/**
 *  NSString representing a notification name you can listen to.
 *  An NSNotification with this name is broadcasted shortly after receiving InApp messages
 *  Primary-application may use this notification to manage the received InApp messages */
extern NSString* kSMNotification_Event_DidReceiveInAppMessage;

/**
 *  NSString representing a notification name you can listen to.
 *  An NSNotification with this name is broadcasted shortly after receiving InApp content
 *  Primary-application may use this notification to manage the received InApp content */
extern NSString* kSMNotification_Event_DidReceiveInAppContent;



/**
 *  NSString representing a key to retrieve an object inside NSNotification
 *  Use the key kSMNotification_Data_ButtonData to retrive the object SMNotificationButtonData from the NSNotification-name kSMNotification_Event_ButtonClicked.
 */
extern NSString* kSMNotification_Data_ButtonData;


/**
 *  NSString representing a key to retrieve an object inside NSNotification
 *  Use the key kSMNotification_Data_RemoteNotification to retrieve an NSDictionary instance with push ID and name
 */
extern NSString* kSMNotification_Data_RemoteNotification;

/**
 *  NSString representing a key to retrieve an object inside NSNotification
 *  Use the key kSMNotification_Data_InAppMessage to retrieve an NSDictionary instance with an array of SMNotificationMessage
 */
extern NSString* kSMNotification_Data_InAppMessage;

/**
 *  NSString representing a key to retrieve an object inside NSNotification
 *  Use the key kSMNotification_Data_InAppContent to retrieve an NSDictionary instance with an array of  in app contents categories as key and number of in app contents for the category as value
 */
extern NSString* kSMNotification_Data_InAppContent;
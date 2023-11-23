/**
 * @module SelligentConstants
 */
const SelligentConstants = {
	/**
	 * @description
	 * Defines the interval value to clear the cache.
	 */
	ClearCacheIntervalValue: {
		/** Clear cache automatically (on startup?)  */
		AUTO: 1,
		/** Don't clear cache  */
		NONE: 2,
		/** Clear cache daily */
		DAY: 3,
		/** Clear cache weekly */
		WEEK: 4,
		/** Clear cache monthly  */
		MONTH: 5,
		/** Clear cache quarterly */
		QUARTER: 6
	},
	/**
	 * @description
	 * Defines how often the SDK must retrieve the in-app messages.
	 */
	InAppMessageRefreshType: {
		/** Refresh in-app messages none */
		NONE: 10,
		/** Refresh in-app messages minutely */
		MINUTE: 11,
		/** Refresh in-app messages hourly */
		HOUR: 12,
		/** Refresh in-app messages daily */
		DAY: 13,
	},
	/**
	 * @description
	 * Defines the in-app messages type.
	 */
	InAppMessageType: {
		UNKNOWN: -2,
		HIDDEN: -1,
		ALERT: 0,
		HTML: 1,
		URL: 2,
		IMAGE: 3,
		MAP: 4,
		PASSBOOK: 5,
	},
	/**
	 * @description
	 * Defines if and how remote messages can be displayed.
	 */
	RemoteMessagesDisplayType: {
		/** Display remote messages automatically */
		AUTOMATIC: 20,
		/** Don't display remote messages */
		NONE: 21,
		/** Display remote messages as notification */
		NOTIFICATION: 22
	},
	/**
	 * @description
	 * Defines the level of output of logging messages on iOS.
	 */
	iOSLogLevel: {
		/** Output nothing */
		NONE: 50,
		/** Output info */
		INFO: 51,
		/** Output warning */
		WARNING: 52,
		/** Output error */
		ERROR: 53,
		/** Output HTTPCall */
		HTTP_CALL: 54,
		/** Output everything */
		ALL: 56
	},
	/**
	 * @description
	 * Defines the type of an event.
	 */
	EventType: {
		/** User registered */
		USER_REGISTER: 90,
		/** User unregistered */
		USER_UNREGISTER: 91,
		/** User logged in */
		USER_LOGIN: 92,
		/** User logged out */
		USER_LOGOUT: 93,
		/** Custom event */
		CUSTOM: 94,
	},
	/**
	 * @description
	 * Defines the type of button for notifications and inapp messages.
	 */
	NotificationButtonType: {
		/** Unknown button type */
		UNKNOWN: 100,
		/** Simple open phone call button type */
		SIMPLE_OPEN_PHONE_CALL: 101,
		/** Open sms button type */
		OPEN_SMS: 102,
		/** Open mail button type */
		OPEN_MAIL: 103,
		/** Open browser button type */
		OPEN_BROWSER: 104,
		/** Open application button type */
		OPEN_APPLICATION: 105,
		/** Rate application button type */
		RATE_APPLICATION: 106,
		/** Custom action broadcast event button type */
		CUSTOM_ACTION_BROADCAST_EVENT: 107,
		/** Passbook button type */
		PASSBOOK: 111,
		/** Deeplink button type */
		DEEPLINK: 112,
		/** Simple button type */
		SIMPLE: 112
	},
	/**
	 * @description
	 * Defines the type of button for notifications and inapp messages on iOS.
	 * 
	 * @deprecated Use NotificationButtonType instead.
	 */
	iOSNotificationButtonType: {
		/** Unknown button type */
		UNKNOWN: 100,
		/** Simple open phone call button type */
		SIMPLE_OPEN_PHONE_CALL: 101,
		/** Open sms button type */
		OPEN_SMS: 102,
		/** Open mail button type */
		OPEN_MAIL: 103,
		/** Open browser button type */
		OPEN_BROWSER: 104,
		/** Open application button type */
		OPEN_APPLICATION: 105,
		/** Rate application button type */
		RATE_APPLICATION: 106,
		/** Custom action broadcast event button type */
		CUSTOM_ACTION_BROADCAST_EVENT: 107,
		/** Passbook button type */
		PASSBOOK: 111,
		/** Deeplink button type */
		DEEPLINK: 112,
		/** Simple button type */
		SIMPLE: 112
	},
	/**
	 * @description
	 * Defines the type of a broadcast event.
	 */
	BroadcastEventType: {
		/** A button was clicked */
		BUTTON_CLICKED: "ButtonClicked",
		/** An in-app message has been received */
		RECEIVED_IN_APP_MESSAGE: "ReceivedInAppMessage",
		/** A notification will be displayed */
		WILL_DISPLAY_NOTIFICATION: "WillDisplayNotification",
		/** A notification will be dismissed */
		WILL_DISMISS_NOTIFICATION: "WillDismissNotification",
		/** A device id has been received */
		RECEIVED_DEVICE_ID: "ReceivedDeviceId",
		/** Received GCM TOKEN */
		RECEIVED_GCM_TOKEN: "ReceivedGCMToken",
		/** Received a remote notification */
		RECEIVED_REMOTE_NOTIFICATION: "ReceivedRemoteNotification",
		/** Received an universal link execution */
		UNIVERSAL_LINK_EXECUTED: "UniversalLinkExecuted",
		/** A custom event has been triggered */
		TRIGGERED_CUSTOM_EVENT: "TriggeredCustomEvent",
		/** An IAM is about to be displayed (when `customInAppUi` is set to `true` in `selligent.json`) */
		DISPLAYING_IN_APP_MESSAGE: "DisplayingInAppMessage"
	},

};

module.exports = SelligentConstants

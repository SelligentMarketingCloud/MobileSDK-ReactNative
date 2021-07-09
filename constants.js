import {Platform} from 'react-native'

/**
 * @module SelligentConstants
 */
var SelligentConstants = {
	/**
	 * @description
	 * Defines the interval value to clear the cache.
	 */
	ClearCacheIntervalValue: {
		/** Clear cache automatically (on startup?)  */
		AUTO: 1,
		/** Don't clear cache  */
		NONE: 2,
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
	 * Defines if and how remote messages can be displayed on Android.
	 */
	AndroidRemoteMessagesDisplayType: {
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
		/** Output location */
		LOCATION: 55,
		/** Output everything */
		ALL: 56
	},
	/**
	 * @description
	 * Description of the possible results of a background fetch on iOS.
	 */
	iOSBackgroundFetchResult: {
		/** Background fetch resulted in new data */
		NEW_DATA: 60,
		/** Background fetch resulted in no new data */
		NO_DATA: 61,
		/** Background fetch failed */
		FAILED: 62
	},
	/**
	 * @description
	 * Description of the possible status of use of location services on a device.
	 */
	iOSLocationAuthorisationStatus: {
		/** Status of use of location services is unknown */
		UNKNOWN: 70,
		/** Use of location services is refused */
		REFUSED: 71,
		/** Use of location services is granted when in use */
		GRANTED_IN_USE: 72,
		/** Use of location services is always granted */
		GRANTED_ALWAYS: 73
	},
	/**
	 * @description
	 * Defines the level of request for the authorisation of usage of location services on a device.
	 */
	iOSLocationAuthorisationType: {
		/** Request authorisation when in location services are in use */
		IN_USE: 80,
		/** Always request the authorisation of the location services */
		ALWAYS: 81
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
	 * Defines the type of button for notifications on iOS.
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
		/** Return text button type */
		RETURN_TEXT: 108,
		/** Return photo button type */
		RETURN_PHOTO: 109,
		/** Return text and photo button type */
		RETURN_TEXT_AND_PHOTO: 110,
		/** Passbook button type */
		PASSBOOK: 111
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
		RECEIVED_DEVICE_ID: "ReceivedDeviceId"
	},
	/**
	 * @description
	 * Defines the type of a Remote Notification.
	 */
	RemoteNotification: {}
};

// Android specific
if (Platform.OS === 'android') {
	/** Clear cache daily */
	SelligentConstants.ClearCacheIntervalValue.DAY = 3
	/** Refresh in-app messages every minute */
	SelligentConstants.InAppMessageRefreshType.MINUTE = 11
	/** Received GCM TOKEN */
	SelligentConstants.BroadcastEventType.RECEIVED_GCM_TOKEN = "ReceivedGCMToken"
}

// iOS specific
if (Platform.OS === 'ios') {
	/** Received a broadcast event */
	SelligentConstants.BroadcastEventType.RECEIVED_REMOTE_NOTIFICATION = "ReceivedRemoteNotification"
	/** Received a remote notification */
	SelligentConstants.RemoteNotification.FETCHED_REMOTE_NOTIFICATION = "FetchedRemoteNotification"
}

module.exports = SelligentConstants

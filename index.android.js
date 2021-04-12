// Android specific methods
import { NativeEventEmitter, NativeModules } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules
const RNSEventEmitter = new NativeEventEmitter(RNSelligent)

export default {
	// Basic SMManager

	// InAppMessage

	/**
	 * Enable/disable in-app messages on Android.
	 *
	 * Android specific: if args is a boolean set to "true", the in-app messages will be enabled with a default refresh type "DAY".
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {(boolean|InAppMessageRefreshType)} options Boolean to enable/disable in-app messages or an enum InAppMessageRefreshType to enable and set which in-app messages should be enabled.
	 */
	enableInAppMessages: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'number') && !SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean or a number.'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.enableInAppMessages({ enabled })
		return
	},

	/**
	 * To check if in app messages are enabled on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	areInAppMessagesEnabled: function (successCallback) {
		return RNSelligent.areInAppMessagesEnabled(successCallback)
	},

	/**
	 * Display message on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} messageId Id of the message.
	 */
	displayMessage: function (successCallback, errorCallback, messageId) {
		if (!SelligentHelpers.typeMatches(messageId, 'string')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string.'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.displayMessage(messageId)
		return
	},

	// Log
	/**
	 * Enable logging messages on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {boolean} shouldEnableLoggingMessages Boolean to enable/disable logging messages on Android.
	 */
	enableAndroidLogging: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean.'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setDebug(enabled)
		return
	},
	// Remote Notification

	/**
	 * Check if notifications are enabled or disabled.
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	areNotificationsEnabled: function (successCallback) {
		RNSelligent.areNotificationsEnabled(successCallback)
		return
	},

	/**
	 * Set the resource for the small icon for notifications on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} iconName Name of the icon.
	 */
	setNotificationSmallIcon: function (successCallback, errorCallback, iconName) {
		if (!SelligentHelpers.typeMatches(iconName, 'string') || iconName.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setNotificationSmallIcon(iconName)
		return
	},

	/**
	 * Set the resource for the large icon for notifications on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} iconName Name of the icon.
	 */
	setNotificationLargeIcon: function (successCallback, errorCallback, iconName) {
		if (!SelligentHelpers.typeMatches(iconName, 'string') || iconName.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setNotificationLargeIcon(iconName)
		return
	},

	/**
	 * Get GCM Token
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	getGCMToken: function (successCallback) {
		RNSelligent.getGCMToken(successCallback)
		return
	},

	/**
	 * Get remote messages display type.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 */
	getRemoteMessagesDisplayType: function (successCallback) {
		RNSelligent.getRemoteMessagesDisplayType(successCallback)
		return
	},
	// Broadcasts Events

	/**
	 * Subscribe to events.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {function} eventCallback Callback function on event.
	 * @param {array} customEvents Array of custom events to subscribe to.
	 */
	subscribeToEvents: function (successCallback, errorCallback, eventCallback, customEvents = []) {

		if (customEvents !== undefined) {
			if (!SelligentHelpers.typeMatches(customEvents, 'array')) {
				errorCallback(SelligentHelpers.createTypeErrorMessage('customEvents', customEvents, 'array'))
				return
			}

			// check if values are all strings
			var arrayLength = customEvents.length
			for (var i = 0; i < arrayLength; i++) {
				if (!SelligentHelpers.typeMatches(customEvents[i], 'string')) {
					errorCallback(SelligentHelpers.wrongArgumentError('Expected an array of strings.'))
					return
				}
			}
		}

		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.BUTTON_CLICKED, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_IN_APP_MESSAGE, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.WILL_DISPLAY_NOTIFICATION, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.WILL_DISMISS_NOTIFICATION, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_GCM_TOKEN, eventCallback);

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.subscribeToEvents(customEvents)
		return
	},

	/**
	 * Subscribe to event.
	 *
	 * @param {function} eventCallback Callback function on event.
	 * @param {string} eventName Name of the event to subscribe to.
	 */
	subscribeToEvent: function (eventCallback, eventName) {
		RNSEventEmitter.addListener(eventName, eventCallback);
		return
	},

	/**
	 * Set the firebase (GCM) token
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} token the firebase token.
	 */
	setFirebaseToken: function (successCallback, errorCallback, token) {
		if (!SelligentHelpers.typeMatches(token, 'string') || token.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setFirebaseToken(token)
		return
	},
}

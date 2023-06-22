// Android specific methods
import { NativeModules } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules

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
	 * @param {(boolean|InAppMessageRefreshType)} enabled Boolean to enable/disable in-app messages or an enum InAppMessageRefreshType to enable and set which in-app messages should be enabled.
	 */
	enableInAppMessages: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'number') && !SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean or a number.'))
			return
		}
		else if (SelligentHelpers.typeMatches(enabled, 'number') && !Object.values(SelligentConstants.InAppMessageRefreshType).includes(enabled)) {
			errorCallback(SelligentHelpers.wrongArgumentError('Value should be one from InAppMessageRefreshType'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.enableInAppMessages({ enabled })
	},

	/**
	 * To check if in app messages are enabled on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	areInAppMessagesEnabled: function (successCallback) {
		return RNSelligent.areInAppMessagesEnabled(successCallback)
	},

	// Log
	/**
	 * Enable logging messages on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {boolean} enabled Boolean to enable/disable logging messages on Android.
	 */
	enableAndroidLogging: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean.'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setDebug(enabled)
	},
	// Remote Notification

	/**
	 * Check if notifications are enabled or disabled.
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	areNotificationsEnabled: function (successCallback) {
		RNSelligent.areNotificationsEnabled(successCallback)
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
	},

	/**
	 * Set the color for the icon for notifications on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} color The color for the notification.
	 */
	setNotificationIconColor: function (successCallback, errorCallback, color) {
		if (!SelligentHelpers.typeMatches(color, 'string') || color.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		const _successCallback = () => {
			successCallback(SelligentHelpers.SUCCESS)
		}

		RNSelligent.setNotificationIconColor(color, _successCallback, errorCallback)
	},

	/**
	 * Set the notification activity on Android.
	 *
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} activityName The name of the activity.
	 */
	 setNotificationActivity: function (successCallback, errorCallback, activityName) {
		if (!SelligentHelpers.typeMatches(activityName, 'string') || activityName.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		const _successCallback = () => {
			successCallback(SelligentHelpers.SUCCESS)
		}

		RNSelligent.setNotificationActivity(activityName, _successCallback, errorCallback)
	},

	/**
	 * Get GCM Token
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	getGCMToken: function (successCallback) {
		RNSelligent.getGCMToken(successCallback)
	},

	/**
	 * Get remote messages display type.
	 *
	 * @param {function} successCallback Callback function on success.
	 */
	getRemoteMessagesDisplayType: function (successCallback) {
		RNSelligent.getRemoteMessagesDisplayType(successCallback)
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
	},
}

import { NativeModules, Platform } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules

// Check if Native version of Selligent found
SelligentHelpers.isNativeSelligentFound(RNSelligent)

// to export the android methods without syntax sugar and/or javascript manipulation, use this line:
// export default RNSelligent;

// platform specific code
var platformSpecificMethods = {}

if (Platform.OS === 'android') {
	platformSpecificMethods = require('./index.android.js').default
} else if (Platform.OS === 'ios') {
	platformSpecificMethods = require('./index.ios.js').default
}

// or export with syntax sugar and/or javascript manipulation:
export default Object.assign(
	{
		// Check if the Selligent Module is loaded
		_selligentLoaded: Boolean(RNSelligent),
		// Basic SMManager

		/**
		 * Returns the version of the underlying Selligent SDK.
		 * 
		 * @param {function} successCallback Callback function on success.
		 */
		getVersionLib: function (successCallback) {
			RNSelligent.getVersionLib(successCallback)
			return
		},
		// DataTransaction

		// InAppMessage

		/**
		 * Get in app messages.
		 *  
		 * @param {function} successCallback Callback function on success.
		 */
		getInAppMessages: function (successCallback) {
			RNSelligent.getInAppMessages(successCallback)
			return
		},

		/**
		 * Set in app message as seen
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} messageId Message id to identify the message which has been seen.
		 */
		setInAppMessageAsSeen: function (successCallback, errorCallback, messageId) {
			// check if required options are valid
			if (!SelligentHelpers.typeMatches(messageId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a string.'))
				return
			}

			// continue if options are valid
			const _successCallback = () => {
				successCallback(SelligentHelpers.SUCCESS)
			}

			RNSelligent.setInAppMessageAsSeen(messageId, _successCallback, errorCallback)
			return
		},

		/**
		 * Execute action on button
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} buttonId Button id to identify the message.
		 * @param {string} messageId Message id to identify the message.
		 */
		executeButtonAction: function (successCallback, errorCallback, buttonId, messageId) {
			if (!SelligentHelpers.typeMatches(buttonId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected buttonId to be a string.'))
				return
			}
			if (!SelligentHelpers.typeMatches(messageId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected messageId to be a string.'))
				return
			}

			const _successCallback = () => {
				successCallback(SelligentHelpers.SUCCESS)
			}

			RNSelligent.executeButtonAction(buttonId, messageId, _successCallback, errorCallback)
			return
		},

		// Location

		/**
		 * Enable/disable geolocation.
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {boolean} enabled Boolean to enable or disable geolocation.
		 */
		enableGeolocation: function (successCallback, errorCallback, enabled) {
			// check if required options are valid
			if (!SelligentHelpers.typeMatches(enabled, 'boolean')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean.'))
				return
			}

			// continue if options are valid
			successCallback(SelligentHelpers.SUCCESS)
			RNSelligent.enableGeolocation(enabled)
			return
		},

		/**
		 * Check if geolocation is enabled or disabled.
		 *  
		 * @param {function} successCallback Callback function on success.
		 */
		isGeolocationEnabled: function (successCallback) {
			RNSelligent.isGeolocationEnabled(successCallback)
			return
		},
		// Event

		/**
		 * Send event.
		 *
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {object} event Event to send.
		 */
		sendEvent: function (successCallback, errorCallback, event) {
			// check if required options are valid
			if (!SelligentHelpers.hasRequiredParameterAndMatchesType(event, 'type', 'number')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected an object with the required key "type".'))
				return
			}

			// check which type is send
			// When type is `CUSTOM`
			if (event.type === SelligentConstants.EventType.CUSTOM) {
				// check if required options are valid
				if (!SelligentHelpers.hasRequiredParameterAndMatchesType(event, 'data', 'object')) {
					errorCallback(SelligentHelpers.wrongArgumentError('Expected an object with the key "data".'))
					return
				}

				// check if required options are valid
				if (event.hasOwnProperty('email')) {
					console.warn("Email prop is not used with \"custom\" event type and will be ignored.");
				}
			} else {
				if (!SelligentHelpers.hasRequiredParameterAndMatchesType(event, 'email', 'string')) {
					errorCallback(SelligentHelpers.wrongArgumentError('Expected an object with the key "email".'))
					return
				}
			}

			if (!SelligentHelpers.hasOptionalParameterAndMatchesType(event, 'shouldCache', 'boolean')) {
				errorCallback(SelligentHelpers.createTypeErrorMessage('shouldCache', event.shouldCache, 'boolean'))
				return
			}

			// continue if options are valid
			RNSelligent.sendEvent(event, successCallback, errorCallback)
			return
		},
		// Remote Notifications

		/**
		 * Enable/disable notification.
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {boolean} enabled Boolean to enable or disable notifications.
		 */
		enableNotifications: function (successCallback, errorCallback, enabled) {
			// check if required options are valid
			if (!SelligentHelpers.typeMatches(enabled, 'boolean')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean.'))
				return
			}

			// continue if options are valid
			successCallback(SelligentHelpers.SUCCESS)
			RNSelligent.enableNotifications(enabled)
			return
		},

		/**
		 * Display the last received remote push notification
		 *  
		 * @param {function} successCallback Callback function on success.
		 */
		displayLastReceivedRemotePushNotification: function (successCallback) {
			successCallback(SelligentHelpers.SUCCESS)
			RNSelligent.displayLastReceivedRemotePushNotification()
			return
		},

		/**
		 * Get last remote push notification
		 *  
		 * @param {function} successCallback Callback function on success.
		 */
		getLastRemotePushNotification: function (successCallback) {
			RNSelligent.getLastRemotePushNotification(successCallback)
			return
		}
	},
	{ ...platformSpecificMethods }
)

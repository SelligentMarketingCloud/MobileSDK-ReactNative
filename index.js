import { NativeEventEmitter, NativeModules, Platform } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules
export const RNSEventEmitter = new NativeEventEmitter(RNSelligent)

// Check if Native version of Selligent found
SelligentHelpers.isNativeSelligentFound(RNSelligent)

// to export the android methods without syntax sugar and/or javascript manipulation, use this line:
// export default RNSelligent;

// platform specific code
let platformSpecificMethods = {};

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
		 * Returns the version of the underlying Selligent native SDK.
		 * 
		 * @param {function} successCallback Callback function on success.
		 */
		getVersionLib: function (successCallback) {
			RNSelligent.getVersionLib(successCallback)
		},

		// InAppMessage
		
		/**
		 * To check if in app messages are enabled.
		 *
		 * @param {function} successCallback Callback function on success.
		 */
		areInAppMessagesEnabled: function (successCallback) {
			return RNSelligent.areInAppMessagesEnabled(successCallback)
		},

		/**
		 * Gets all known (and not deleted/expired) in app messages.
		 *  
		 * @param {function} successCallback Callback function on success.
		 */
		getInAppMessages: function (successCallback) {
			RNSelligent.getInAppMessages(successCallback)
		},

		/**
		 * Sets an in app message as seen
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
		},

		/**
		 * Sets an in app message as unseen
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} messageId Message id to identify the message which has been unseen.
		 */
		setInAppMessageAsUnseen: function (successCallback, errorCallback, messageId) {
			// check if required options are valid
			if (!SelligentHelpers.typeMatches(messageId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a string.'))
				return
			}

			// continue if options are valid
			const _successCallback = () => {
				successCallback(SelligentHelpers.SUCCESS)
			}

			RNSelligent.setInAppMessageAsUnseen(messageId, _successCallback, errorCallback)
		},
		
		/**
		 * Sets an in app message as deleted
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} messageId Message id to identify the message which has been deleted.
		 */
		setInAppMessageAsDeleted: function (successCallback, errorCallback, messageId) {
			// check if required options are valid
			if (!SelligentHelpers.typeMatches(messageId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a string.'))
				return
			}

			// continue if options are valid
			const _successCallback = () => {
				successCallback(SelligentHelpers.SUCCESS)
			}

			RNSelligent.setInAppMessageAsDeleted(messageId, _successCallback, errorCallback)
		},

		/**
		 * Execute action on button
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} buttonId Button id to identify the button.
		 * @param {string} messageId Message id to identify the message.
		 */
		executeButtonAction: function (successCallback, errorCallback, buttonId, messageId) {
			if (!SelligentHelpers.typeMatches(buttonId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected buttonId to be a string.'))
				return
			}
			else if (!SelligentHelpers.typeMatches(messageId, 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected messageId to be a string.'))
				return
			}

			const _successCallback = () => {
				successCallback(SelligentHelpers.SUCCESS)
			}

			RNSelligent.executeButtonAction(buttonId, messageId, _successCallback, errorCallback)
		},

		/**
		 * Displays an inapp message given its id, (optionally with a specific templateId to use custom styles).
		 * @deprecated Use displayMessage instead.
		 * 
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} notificationId Id of the notification.
		 * @param {string} templateId Id of the template from where to get the styles.
		 */
		displayNotification: function (successCallback, errorCallback, notificationId, templateId) {
			this.displayMessage(successCallback, errorCallback, notificationId, templateId)
		},

		/**
		 * Displays an inapp message given its id, (optionally with a specific templateId to use custom styles for iOS).
		 * 
		 * @param {function} successCallback Callback function on success.
		 * @param {function} errorCallback Callback function on error.
		 * @param {string} messageId Id of the message.
		 * @param {string} templateId Id of the template from where to get the styles (iOS only).
		 */
		displayMessage: function (successCallback, errorCallback, messageId, templateId) {
			if (!SelligentHelpers.typeMatches(messageId, 'string') || messageId.length === 0) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty) messageId.'))
				return
			}

			successCallback(SelligentHelpers.SUCCESS)

			if (Platform.OS === 'ios') {
				RNSelligent.displayNotification(messageId, templateId)
			}
			else if (Platform.OS === 'android') {
				RNSelligent.displayMessage(messageId)
			}
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
			} 
			else if (!SelligentHelpers.hasRequiredParameterAndMatchesType(event, 'email', 'string')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected an object with the key "email".'))
				return
			}

			if (!SelligentHelpers.hasOptionalParameterAndMatchesType(event, 'shouldCache', 'boolean')) {
				errorCallback(SelligentHelpers.createTypeErrorMessage('shouldCache', event.shouldCache, 'boolean'))
				return
			}

			// continue if options are valid
			RNSelligent.sendEvent(event, successCallback, errorCallback)
		},
		// Device Id
		/**
		 * Returns the device id.
		 * 
		 * @param {function} successCallback Callback function on success.
		 */
		 getDeviceId: function (successCallback) {
			RNSelligent.getDeviceId(successCallback)
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
		},

		/**
		 * Displays the last received remote push notification content (optionally, on iOS, with a specific templateId to use custom styles).
		 *  
		 * @param {function} successCallback Callback function on success.
		 * @param {string} templateId Id of the template from where to get the styles.
		 */
		displayLastReceivedRemotePushNotification: function (successCallback, templateId) {
			successCallback(SelligentHelpers.SUCCESS)
			RNSelligent.displayLastReceivedRemotePushNotification(templateId)
		},

		/**
		 * Displays the last received remote push notification (if any).
		 */
		displayLastReceivedNotification: function() {
			RNSelligent.displayLastReceivedNotification()
		},

		/**
		 * Get last remote push notification
		 *  
		 * @param {function} successCallback Callback function on success.
		 */
		getLastRemotePushNotification: function (successCallback) {
			RNSelligent.getLastRemotePushNotification(successCallback)
		},

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
				const arrayLength = customEvents.length;
				for (let i = 0; i < arrayLength; i++) {
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
			RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_DEVICE_ID, eventCallback);
			RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_REMOTE_NOTIFICATION, eventCallback);
			RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.TRIGGERED_CUSTOM_EVENT, eventCallback);

			if (Platform.OS === "ios") {
				RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.UNIVERSAL_LINK_EXECUTED, eventCallback);
			}
			else if (Platform.OS === "android") {
				RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_GCM_TOKEN, eventCallback);
			}
			
			successCallback(SelligentHelpers.SUCCESS)
			RNSelligent.subscribeToEvents(customEvents)
		},

		/**
		 * Subscribe to event.
		 *
		 * @param {function} eventCallback Callback function on event.
		 * @param {string} eventName Name of the custom event to subscribe to.
		 */
		subscribeToEvent: function (eventCallback, eventName) {
			if (Object.values(SelligentConstants.BroadcastEventType).includes(eventName)) {
				RNSEventEmitter.addListener(eventName, eventCallback)
			}
			else {
				RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.TRIGGERED_CUSTOM_EVENT, eventCallback)
			}

			RNSelligent.subscribeToEvents([eventName])
		}
	},
	{ ...platformSpecificMethods }
)

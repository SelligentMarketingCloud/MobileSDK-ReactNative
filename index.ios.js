// iOS specific methods
import { NativeEventEmitter, NativeModules } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules
const RNSEventEmitter = new NativeEventEmitter(RNSelligent)

export default {
	// Basic SMManager

	// InAppMessage

	/**
	 * Enable/disable in-app messages on iOS.
	 *  
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {boolean} enabled Boolean to enable/disable in-app messages.
	 */
	enableInAppMessages: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean.'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.enableInAppMessages(enabled)
		return
	},
	// Log

	/**
	 * Enable logging messages on iOS.
	 * 
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {array} logLevels Array of logging levels that should be enabled.
	 */
	enableiOSLogging: function (successCallback, errorCallback, logLevels) {
		if (!SelligentHelpers.typeMatches(logLevels, 'array')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected an array of numbers.'))
			return
		}

		// check if values are all numbers and iOS Loglevels
		var arrayLength = logLevels.length
		for (var i = 0; i < arrayLength; i++) {

			if (!SelligentHelpers.typeMatches(logLevels[i], 'number')) {
				errorCallback(SelligentHelpers.wrongArgumentError('Expected a number.'))
				return
			}

			if (!SelligentHelpers.constantIsValid(SelligentConstants.iOSLogLevel, logLevels[i])) {
				errorCallback(SelligentHelpers.createTypeErrorMessage('iOSloglevel', logLevels[i], 'number'))
				return
			}
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.applyLogLevel(logLevels)
		return
	},
	// Location

	/**
	 * Get Current AuthorisationStatus.
	 *  
	 * @param {function} successCallback Callback passing iOSLocationAuthorisationStatus.
	 */
	currentAuthorisationStatus: function (successCallback) {
		RNSelligent.currentAuthorisationStatus(successCallback)
		return
	},

	/**
	 * Request Location Authorisation.
	 *  
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {iOSLocationAuthorisationType} iOSLocationAuthorisationType Requested authorisation type.
	 */
	requestLocationAuthorisation: function (successCallback, errorCallback, iOSLocationAuthorisationType) {
		if (!SelligentHelpers.constantIsValid(SelligentConstants.iOSLocationAuthorisationType, iOSLocationAuthorisationType)) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('iOSLocationAuthorisationType', iOSLocationAuthorisationType, 'number'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.requestLocationAuthorisation(iOSLocationAuthorisationType)
		return
	},
	// Remote Notification

	/**
	 * Display notification by id on iOS.
	 * 
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {string} notificationId Id of the notification.
	 */
	displayNotification: function (successCallback, errorCallback, notificationId) {
		if (!SelligentHelpers.typeMatches(notificationId, 'string') || notificationId.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.displayNotification(notificationId)
		return
	},

	/**
	 * Register a completion handler for successfully fetching remote notifications.
	 * 
	 * @param {function} successCallback Completion handler.
	 * @param {function} eventCallback Callback function on event.
	 */
	registerRemoteNotificationFetchCompletionHandler: function (successCallback, eventCallback) {
		RNSEventEmitter.addListener(SelligentConstants.RemoteNotification.FETCHED_REMOTE_NOTIFICATION, eventCallback);
		successCallback(SelligentHelpers.SUCCESS)
		return
	},

	/**
	 * Force the result of a remote notification fetch to be a specific value.
	 * 
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {iOSBackgroundFetchResult} iOSBackgroundFetchResult Type of result to force, when fetching remote notifications.
	 */
	forceRemoteNotificationBackgroundFetchResult: function (successCallback, errorCallback, iOSBackgroundFetchResult) {
		if (!SelligentHelpers.typeMatches(iOSBackgroundFetchResult, 'number') || !SelligentHelpers.constantIsValid(SelligentConstants.iOSBackgroundFetchResult, iOSBackgroundFetchResult)) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a value of Selligent constant enum "iOSBackgroundFetchResult".'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.forceRemoteNotificationBackgroundFetchResult(iOSBackgroundFetchResult)
		return
	},
	// Broadcasts Events

	/**
	 * Subscribe to events.
	 * 
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {function} eventCallback Callback function on event.
	 */
	subscribeToEvents: function (successCallback, errorCallback, eventCallback) {
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_IN_APP_MESSAGE, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.WILL_DISPLAY_NOTIFICATION, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.WILL_DISMISS_NOTIFICATION, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_REMOTE_NOTIFICATION, eventCallback);

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.subscribeToEvents()
		return
	}
}

// iOS specific methods
import { NativeEventEmitter, NativeModules } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules
const RNSEventEmitter = new NativeEventEmitter(RNSelligent)

export default {
	// Basic SMManager

	// InAppMessage
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
	currentAuthorisationStatus: function (successCallback) {
		RNSelligent.currentAuthorisationStatus(successCallback)
		return
	},
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
	displayNotification: function (successCallback, errorCallback, notificationId) {
		if (!SelligentHelpers.typeMatches(notificationId, 'string') || notificationId.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.displayNotification(notificationId)
		return
	},
	registerRemoteNotificationFetchCompletionHandler: function (successCallback, eventCallback) {
		RNSEventEmitter.addListener(SelligentConstants.RemoteNotification.FETCHED_REMOTE_NOTIFICATION, eventCallback);
		successCallback(SelligentHelpers.SUCCESS)
		return
	},
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

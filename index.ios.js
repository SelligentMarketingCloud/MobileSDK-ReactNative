// iOS specific methods
import {NativeEventEmitter, NativeModules} from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const {RNSelligent} = NativeModules
const RNSEventEmitter = new NativeEventEmitter(RNSelligent)

export default {
	// Basic SMManager
	reloadSettings: function (successCallback, errorCallback, settings) {
		// check if required options are valid
		if (!SelligentHelpers.hasRequiredParameterAndMatchesType(settings, 'url', 'string') ||
			!SelligentHelpers.hasRequiredParameterAndMatchesType(settings, 'clientId', 'string') ||
			!SelligentHelpers.hasRequiredParameterAndMatchesType(settings, 'privateKey', 'string')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected an object with keys "url", "clientId" and "privateKey", and strings for values.'))
			return
		}
		// check if optional options are valid
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'googleApplicationId', 'string')) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('googleApplicationId', settings.googleApplicationId, 'string'))
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'clearCacheIntervalValue', 'number', SelligentConstants.ClearCacheIntervalValue)) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('clearCacheIntervalValue', settings.clearCacheIntervalValue, 'number'))
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'configureLocationServices', 'boolean')) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('configureLocationServices', settings.configureLocationServices, 'boolean'))
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'inAppMessageRefreshType', 'number', SelligentConstants.InAppMessageRefreshType)) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('inAppMessageRefreshType', settings.inAppMessageRefreshType, 'number'))
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'shouldClearBadge', 'boolean')) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('shouldClearBadge', settings.shouldClearBadge, 'boolean'))
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'shouldDisplayRemoteNotification', 'boolean')) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('shouldDisplayRemoteNotification', settings.shouldDisplayRemoteNotification, 'boolean'))
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'shouldPerformBackgroundFetch', 'boolean')) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('shouldPerformBackgroundFetch', settings.shouldPerformBackgroundFetch, 'boolean'))
			return
		}
		// continue if options are valid
		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.reloadSettings(settings)
		return
	},
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
	subscribeToEvents: function (successCallback, eventCallback) {
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_IN_APP_MESSAGE, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.WILL_DISPLAY_NOTIFICATION, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.WILL_DISMISS_NOTIFICATION, eventCallback);
		RNSEventEmitter.addListener(SelligentConstants.BroadcastEventType.RECEIVED_REMOTE_NOTIFICATION, eventCallback);

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.subscribeToEvents()
		return
	}
}

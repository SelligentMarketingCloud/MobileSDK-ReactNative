// Android specific methods
import { NativeEventEmitter, NativeModules } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules
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

		if (!SelligentHelpers.hasRequiredParameterAndMatchesType(settings, 'fullyQualifiedNotificationActivityClassName', 'string')) {
			errorCallback(SelligentHelpers.WRONG_ARGUMENTS + ' ' + 'Expected an object with key "fullyQualifiedNotificationActivityClassName" of the type "string".' + ' ' + SelligentHelpers.MORE_INFORMATION)
			return
		}
		if (!SelligentHelpers.hasOptionalParameterAndMatchesType(settings, 'remoteMessageDisplayType', 'number', SelligentConstants.AndroidRemoteMessagesDisplayType)) {
			errorCallback(SelligentHelpers.createTypeErrorMessage('remoteMessageDisplayType', settings.remoteMessageDisplayType, 'number'))
			return
		}

		// continue if options are valid
		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.reloadSettings(settings)
		return
	},
	// InAppMessage
	enableInAppMessages: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'number') && !SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean or a number.'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.enableInAppMessages({ enabled })
		return
	},
	areInAppMessagesEnabled: function (successCallback) {
		return RNSelligent.areInAppMessagesEnabled(successCallback)
	},
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
	areNotificationsEnabled: function (successCallback) {
		RNSelligent.areNotificationsEnabled(successCallback)
		return
	},
	setNotificationSmallIcon: function (successCallback, errorCallback, iconName) {
		if (!SelligentHelpers.typeMatches(iconName, 'string') || iconName.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setNotificationSmallIcon(iconName)
		return
	},
	setNotificationLargeIcon: function (successCallback, errorCallback, iconName) {
		if (!SelligentHelpers.typeMatches(iconName, 'string') || iconName.length === 0) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a string (not empty).'))
			return
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.setNotificationLargeIcon(iconName)
		return
	},
	getGCMToken: function (successCallback) {
		RNSelligent.getGCMToken(successCallback)
		return
	},
	getRemoteMessagesDisplayType: function (successCallback) {
		RNSelligent.getRemoteMessagesDisplayType(successCallback)
		return
	},
	// Broadcasts Events
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
	subscribeToEvent: function (eventCallback, eventName) {
		RNSEventEmitter.addListener(eventName, eventCallback);
		return
	},
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

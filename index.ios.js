// iOS specific methods
import { NativeModules } from 'react-native'
import SelligentConstants from './constants'
import SelligentHelpers from './helpers'

const { RNSelligent } = NativeModules

export default {
	// Basic SMManager

	// InAppMessage

	/**
	 * Enable/disable in-app messages on iOS.
	 *  
	 * @param {function} successCallback Callback function on success.
	 * @param {function} errorCallback Callback function on error.
	 * @param {boolean | number} enabled Boolean to enable/disable in-app messages.
	 */
	enableInAppMessages: function (successCallback, errorCallback, enabled) {
		if (!SelligentHelpers.typeMatches(enabled, 'number') && !SelligentHelpers.typeMatches(enabled, 'boolean')) {
			errorCallback(SelligentHelpers.wrongArgumentError('Expected a boolean or a number.'))
			return
		}

		let result;

		if (typeof enabled === 'boolean'){
			result = enabled
		}
		else {
			if (!Object.values(SelligentConstants.InAppMessageRefreshType).includes(enabled)) {
				errorCallback(SelligentHelpers.wrongArgumentError('Value should be one from InAppMessageRefreshType'))
				return
			}

			result = enabled !== SelligentConstants.InAppMessageRefreshType.NONE;
		}

		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.enableInAppMessages(result)
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
		const arrayLength = logLevels.length;
		for (let i = 0; i < arrayLength; i++) {

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
	},
	// Remote Notification

	/**
	 * Register for Provisional Push Notifications.
	 *  
	 * @param {function} successCallback Callback function on success.
	 */
	registerForProvisionalRemoteNotification: function (successCallback) {
		successCallback(SelligentHelpers.SUCCESS)
		RNSelligent.registerForProvisionalRemoteNotification()
	}
}
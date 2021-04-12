export function getVersionLib(successCallback: Function): void;
export function getInAppMessages(successCallback: Function): void;
export function setInAppMessageAsSeen(
  successCallback: Function,
  errorCallback: Function,
  messageId: string
): void;
export function executeButtonAction(
  successCallback: Function,
  errorCallback: Function,
  buttonId: string,
  messageId: string
): void;
export function enableGeolocation(
  successCallback: Function,
  errorCallback: Function,
  enabled: boolean
): void;
export function isGeolocationEnabled(successCallback: Function): void;
export function sendEvent(
  successCallback: Function,
  errorCallback: Function,
  event: any
): void;
export function enableNotifications(
  successCallback: Function,
  errorCallback: Function,
  enabled: boolean
): void;
export function displayLastReceivedRemotePushNotification(
  successCallback: Function
): void;
export function getLastRemotePushNotification(successCallback: Function): void;

// IOS
export function enableInAppMessages(
  successCallback: Function,
  errorCallback: Function,
  enabled: boolean
): void;
export function enableiOSLogging(
  successCallback: Function,
  errorCallback: Function,
  logLevels: any[]
): void;
export function currentAuthorisationStatus(successCallback: Function): void;
export function requestLocationAuthorisation(
  successCallback: Function,
  errorCallback: Function,
  iOSLocationAuthorisationType: any
): void;
export function displayNotification(
  successCallback: Function,
  errorCallback: Function,
  notificationId: string
): void;
export function registerRemoteNotificationFetchCompletionHandler(
  successCallback: Function,
  eventCallback: Function
): void;
export function forceRemoteNotificationBackgroundFetchResult(
  successCallback: Function,
  errorCallback: Function,
  iOSBackgroundFetchResult: any
): void;
export function subscribeToEvents(
  successCallback: Function,
  errorCallback: Function,
  eventCallback: Function
): void;

// ANDROID
export function enableInAppMessages(
  successCallback: Function,
  errorCallback: Function,
  enabled: boolean | number
): void;
export function areInAppMessagesEnabled(successCallback: Function): any;
export function displayMessage(
  successCallback: Function,
  errorCallback: Function,
  messageId: string
): void;
export function enableAndroidLogging(
  successCallback: Function,
  errorCallback: Function,
  enabled: any
): void;
export function areNotificationsEnabled(successCallback: Function): void;
export function setNotificationSmallIcon(
  successCallback: Function,
  errorCallback: Function,
  iconName: string
): void;
export function setNotificationLargeIcon(
  successCallback: Function,
  errorCallback: Function,
  iconName: string
): void;
export function getGCMToken(successCallback: Function): void;
export function getRemoteMessagesDisplayType(successCallback: Function): void;
export function subscribeToEvents(
  successCallback: Function,
  errorCallback: Function,
  eventCallback: Function,
  customEvents?: any[]
): void;
export function subscribeToEvent(
  eventCallback: Function,
  eventName: string
): void;
export function setFirebaseToken(
  successCallback: Function,
  errorCallback: Function,
  token: string
): void;

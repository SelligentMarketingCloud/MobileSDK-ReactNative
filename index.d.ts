export function getVersionLib(successCallback: Function): void;
export function getInAppMessages(successCallback: Function): void;
export function setInAppMessageAsSeen(
  successCallback: Function,
  errorCallback: Function,
  messageId: string
): void;
export function setInAppMessageAsUnseen(
  successCallback: Function,
  errorCallback: Function,
  messageId: string
): void;
export function setInAppMessageAsDeleted(
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
export function sendEvent(
  successCallback: Function,
  errorCallback: Function,
  event: any
): void;
export function getDeviceId(successCallback: Function): void;
export function enableNotifications(
  successCallback: Function,
  errorCallback: Function,
  enabled: boolean
): void;
export function displayLastReceivedRemotePushNotification(
  successCallback: Function,
  templateId?: string
): void;
export function displayLastReceivedNotification(): void;
export function getLastRemotePushNotification(successCallback: Function): void;
export function enableInAppMessages(
  successCallback: Function,
  errorCallback: Function,
  enabled: boolean | number
): void;
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
export function displayNotification(
  successCallback: Function,
  errorCallback: Function,
  notificationId: string,
  templateId?: string
): void;
export function displayMessage(
  successCallback: Function,
  errorCallback: Function,
  messageId: string,
  templateId?: string
): void;
export function executePushAction(): void;

// IOS
export function enableiOSLogging(
  successCallback: Function,
  errorCallback: Function,
  logLevels: any[]
): void;
export function registerForProvisionalRemoteNotification(
  successCallback: Function
): void;

// ANDROID
export function areInAppMessagesEnabled(successCallback: Function): any;
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
export function setNotificationIconColor(
  successCallback: Function,
  errorCallback: Function,
  color: string
): void;
export function setNotificationActivity(
  successCallback: Function,
  errorCallback: Function,
  activityName: string
): void;
export function getGCMToken(successCallback: Function): void;
export function getRemoteMessagesDisplayType(successCallback: Function): void;
export function setFirebaseToken(
  successCallback: Function,
  errorCallback: Function,
  token: string
): void;

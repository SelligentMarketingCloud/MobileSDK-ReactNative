export namespace ClearCacheIntervalValue {
  const AUTO = 1;
  const NONE = 2;
  const DAY = 3;
  const WEEK = 4;
  const MONTH = 5;
  const QUARTER = 6;
}

export namespace InAppMessageRefreshType {
  const NONE = 10;
  const MINUTE = 11;
  const HOUR = 12;
  const DAY = 13;
}

export namespace AndroidRemoteMessagesDisplayType {
  const AUTOMATIC = 20;
  const NONE = 21;
  const NOTIFICATION = 22;
}

export namespace iOSLogLevel {
  const NONE = 50;
  const INFO = 51;
  const WARNING = 52;
  const ERROR = 53;
  const HTTP_CALL = 54;
  const LOCATION = 55;
  const ALL = 56;
}

export namespace iOSBackgroundFetchResult {
  const NEW_DATA = 60;
  const NO_DATA = 61;
  const FAILED = 62;
}

export namespace iOSLocationAuthorisationStatus {
  const UNKNOWN = 70;
  const REFUSED = 71;
  const GRANTED_IN_USE = 72;
  const GRANTED_ALWAYS = 73;
}

export namespace iOSLocationAuthorisationType {
  const IN_USE = 80;
  const ALWAYS = 81;
}

export namespace EventType {
  const USER_REGISTER = 90;
  const USER_UNREGISTER = 91;
  const USER_LOGIN = 92;
  const USER_LOGOUT = 93;
  const CUSTOM = 94;
}

export namespace iOSNotificationButtonType {
  const UNKNOWN = 100;
  const SIMPLE_OPEN_PHONE_CALL = 101;
  const OPEN_SMS = 102;
  const OPEN_MAIL = 103;
  const OPEN_BROWSER = 104;
  const OPEN_APPLICATION = 105;
  const RATE_APPLICATION = 106;
  const CUSTOM_ACTION_BROADCAST_EVENT = 107;
  const RETURN_TEXT = 108;
  const RETURN_PHOTO = 109;
  const RETURN_TEXT_AND_PHOTO = 110;
  const PASSBOOK = 111;
}

export namespace BroadcastEventType {
  const BUTTON_CLICKED = "ButtonClicked";
  const RECEIVED_IN_APP_MESSAGE = "ReceivedInAppMessage";
  const WILL_DISPLAY_NOTIFICATION = "WillDisplayNotification";
  const WILL_DISMISS_NOTIFICATION = "WillDismissNotification";
  const RECEIVED_GCM_TOKEN = "ReceivedGCMToken";
  const RECEIVED_REMOTE_NOTIFICATION = "ReceivedRemoteNotification";
}

export namespace RemoteNotification {
  const FETCHED_REMOTE_NOTIFICATION = "FetchedRemoteNotification";
}

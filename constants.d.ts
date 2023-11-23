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

export namespace InAppMessageType {
  const UNKNOWN: -2;
  const HIDDEN: -1;
  const ALERT: 0;
  const HTML: 1;
  const URL: 2;
  const IMAGE: 3;
  const MAP: 4;
  const PASSBOOK: 5;
}

export namespace RemoteMessagesDisplayType {
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
  const ALL = 56;
}

export namespace EventType {
  const USER_REGISTER = 90;
  const USER_UNREGISTER = 91;
  const USER_LOGIN = 92;
  const USER_LOGOUT = 93;
  const CUSTOM = 94;
}

export namespace NotificationButtonType {
  const UNKNOWN = 100;
  const SIMPLE_OPEN_PHONE_CALL = 101;
  const OPEN_SMS = 102;
  const OPEN_MAIL = 103;
  const OPEN_BROWSER = 104;
  const OPEN_APPLICATION = 105;
  const RATE_APPLICATION = 106;
  const CUSTOM_ACTION_BROADCAST_EVENT = 107;
  const PASSBOOK = 111;
  const DEEPLINK = 112;
  const SIMPLE = 113;
}

export import iOSNotificationButtonType = NotificationButtonType;

export namespace BroadcastEventType {
  const BUTTON_CLICKED = "ButtonClicked";
  const RECEIVED_IN_APP_MESSAGE = "ReceivedInAppMessage";
  const WILL_DISPLAY_NOTIFICATION = "WillDisplayNotification";
  const WILL_DISMISS_NOTIFICATION = "WillDismissNotification";
  const RECEIVED_GCM_TOKEN = "ReceivedGCMToken";
  const RECEIVED_DEVICE_ID = "ReceivedDeviceId";
  const RECEIVED_REMOTE_NOTIFICATION = "ReceivedRemoteNotification";
  const UNIVERSAL_LINK_EXECUTED = "UniversalLinkExecuted";
  const TRIGGERED_CUSTOM_EVENT = "TriggeredCustomEvent";
  const DISPLAYING_IN_APP_MESSAGE = "DisplayingInAppMessage";
}

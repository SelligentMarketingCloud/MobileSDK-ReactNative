package com.selligent;


import java.util.HashMap;

class Settings {

    private String url;
    private String clientId;
    private String privateKey;
    private String googleApplicationId;
    private String activityName;
    private String notificationSmallIcon;
    private String notificationLargeIcon;
    private String notificationIconColor;
    private boolean addInAppMessageFromPushToInAppMessageList = false;
    private Boolean doNotFetchTheToken = false;
    private Boolean doNotListenToThePush = false;
    private Boolean loadCacheAsynchronously = false;
    private Boolean configureLocationServices = false;
    private ClearCacheIntervalValue clearCacheIntervalValue;
    private InAppMessageRefreshType inAppMessageRefreshType;
    private RemoteMessageDisplayType remoteMessageDisplayType;
    private String notificationChannelId = "SMChannel001";
    private String notificationChannelName = "SMDefaultChannel";
    private String notificationChannelDescription = "";

    private Settings() { }

    public String getUrl() {
        return url;
    }

    public String getClientId() {
        return clientId;
    }

    public String getPrivateKey() {
        return privateKey;
    }

    public String getGoogleApplicationId() {
        return googleApplicationId;
    }

    public String getActivityName() {
        return activityName;
    }

    public String getNotificationSmallIcon() {
        return notificationSmallIcon;
    }

    public String getNotificationLargeIcon() {
        return notificationLargeIcon;
    }

    public String getNotificationIconColor() {
        return notificationIconColor;
    }

    public Boolean getConfigureLocationServices() {
        return configureLocationServices;
    }

    public Boolean getDoNotListenToThePush() { return doNotListenToThePush; }

    public Boolean getAddInAppMessageFromPushToInAppMessageList() { return addInAppMessageFromPushToInAppMessageList; }

    public Boolean getDoNotFetchTheToken() { return doNotFetchTheToken; }

    public Boolean getLoadCacheAsynchronously() { return loadCacheAsynchronously; }

    public ClearCacheIntervalValue getClearCacheIntervalValue() {
        return clearCacheIntervalValue;
    }

    public InAppMessageRefreshType getInAppMessageRefreshType() {
        return inAppMessageRefreshType;
    }

    public RemoteMessageDisplayType getRemoteMessageDisplayType() {
        return remoteMessageDisplayType;
    }

    public String getNotificationChannelId() {
        return notificationChannelId;
    }

    public String getNotificationChannelName() {
        return notificationChannelName;
    }

    public String getNotificationChannelDescription() {
        return notificationChannelDescription;
    }

    public static Settings fromHashMap(HashMap<String, Object> settingsHashMap) {
        final Settings settings = new Settings();

        settings.url = (String) settingsHashMap.get("url");
        settings.clientId = (String) settingsHashMap.get("clientId");
        settings.privateKey = (String) settingsHashMap.get("privateKey");
        if (settingsHashMap.containsKey("googleApplicationId")) {
            settings.googleApplicationId = (String) settingsHashMap.get("googleApplicationId");
        }
        if (settingsHashMap.containsKey("configureLocationServices")) {
            settings.configureLocationServices = (Boolean) settingsHashMap.get("configureLocationServices");

        }
        settings.activityName = (String) settingsHashMap.get("fullyQualifiedNotificationActivityClassName");

        if (settingsHashMap.containsKey("notificationSmallIcon")) {
            settings.notificationSmallIcon = (String) settingsHashMap.get("notificationSmallIcon");
        }

        if (settingsHashMap.containsKey("notificationLargeIcon")) {
            settings.notificationLargeIcon = (String) settingsHashMap.get("notificationLargeIcon");
        }

        if(settingsHashMap.containsKey("notificationIconColor")) {
            settings.notificationIconColor = (String) settingsHashMap.get("notificationIconColor");
        }

        if (settingsHashMap.containsKey("addInAppMessageFromPushToInAppMessageList")) {
            settings.addInAppMessageFromPushToInAppMessageList = (Boolean) settingsHashMap.get("addInAppMessageFromPushToInAppMessageList");
        }

        if (settingsHashMap.containsKey("doNotFetchTheToken")) {
            settings.doNotFetchTheToken = (Boolean) settingsHashMap.get("doNotFetchTheToken");
        }

        if (settingsHashMap.containsKey("doNotListenToThePush")) {
            settings.doNotListenToThePush = (Boolean) settingsHashMap.get("doNotListenToThePush");
        }

        if (settingsHashMap.containsKey("loadCacheAsynchronously")) {
            settings.loadCacheAsynchronously = (Boolean) settingsHashMap.get("loadCacheAsynchronously");
        }
        if (settingsHashMap.containsKey("notificationChannelId")) {
            settings.notificationChannelId = (String) settingsHashMap.get("notificationChannelId");
        }
        if (settingsHashMap.containsKey("notificationChannelName")) {
            settings.notificationChannelName = (String) settingsHashMap.get("notificationChannelName");
        }
        if (settingsHashMap.containsKey("notificationChannelDescription")) {
            settings.notificationChannelDescription = (String) settingsHashMap.get("notificationChannelDescription");
        }

        final Double clearCacheIndex = (Double) settingsHashMap.get("clearCacheIntervalValue");
        if (clearCacheIndex != null) {
            settings.clearCacheIntervalValue = ClearCacheIntervalValue.valueOf(clearCacheIndex.intValue());
        }
        final Double inAppMsgRefreshIndex =  (Double) settingsHashMap.get("inAppMessageRefreshType");
        if (inAppMsgRefreshIndex != null) {
            settings.inAppMessageRefreshType = InAppMessageRefreshType.valueOf(inAppMsgRefreshIndex.intValue());
        }
        final Double remoteMsgRefreshIndex =  (Double) settingsHashMap.get("remoteMessageDisplayType");
        if (remoteMsgRefreshIndex != null) {
            settings.remoteMessageDisplayType = RemoteMessageDisplayType.valueOf(remoteMsgRefreshIndex.intValue());
        }

        return settings;
    }
}

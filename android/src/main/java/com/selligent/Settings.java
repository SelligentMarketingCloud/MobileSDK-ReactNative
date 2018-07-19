package com.selligent;


import java.util.HashMap;

class Settings {

    private String url;
    private String clientId;
    private String privateKey;
    private String googleApplicationId;
    private String activityName;
    private Boolean configureLocationServices;
    private ClearCacheIntervalValue clearCacheIntervalValue;
    private InAppMessageRefreshType inAppMessageRefreshType;
    private RemoteMessageDisplayType remoteMessageDisplayType;

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

    public Boolean getConfigureLocationServices() {
        return configureLocationServices;
    }

    public ClearCacheIntervalValue getClearCacheIntervalValue() {
        return clearCacheIntervalValue;
    }

    public InAppMessageRefreshType getInAppMessageRefreshType() {
        return inAppMessageRefreshType;
    }

    public RemoteMessageDisplayType getRemoteMessageDisplayType() {
        return remoteMessageDisplayType;
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

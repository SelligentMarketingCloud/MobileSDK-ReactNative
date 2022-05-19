package com.selligent;

import com.selligent.sdk.SMSettings;

class SMSettingsFactory {

    public static SMSettings getSMSettings(Settings settings) {
        final SMSettings smSettings = new SMSettings();
        smSettings.WebServiceUrl = settings.getUrl();
        smSettings.ClientId = settings.getClientId();
        smSettings.PrivateKey = settings.getPrivateKey();
        smSettings.GoogleApplicationId = settings.getGoogleApplicationId();
        smSettings.ConfigureGeolocation = settings.getConfigureLocationServices();
        smSettings.AddInAppMessageFromPushToInAppMessageList = settings.getAddInAppMessageFromPushToInAppMessageList();
        smSettings.DoNotFetchTheToken = settings.getDoNotFetchTheToken();
        smSettings.DoNotListenToThePush = settings.getDoNotListenToThePush();
        smSettings.LoadCacheAsynchronously = settings.getLoadCacheAsynchronously();
        smSettings.NotificationChannelId = settings.getNotificationChannelId();
        smSettings.NotificationChannelName = settings.getNotificationChannelName();
        smSettings.NotificationChannelDescription = settings.getNotificationChannelDescription();

        final ClearCacheIntervalValue clearCacheIntervalValue = settings.getClearCacheIntervalValue();
        if (clearCacheIntervalValue != null) {
            smSettings.ClearCacheIntervalValue = clearCacheIntervalValue.getSmClearCache();
        }
        final InAppMessageRefreshType inAppMessageRefreshType = settings.getInAppMessageRefreshType();
        if (inAppMessageRefreshType != null) {
            smSettings.InAppMessageRefreshType = inAppMessageRefreshType.getSmInAppRefreshType();
        }
        final RemoteMessageDisplayType remoteMessageDisplayType = settings.getRemoteMessageDisplayType();
        if (remoteMessageDisplayType != null) {
            smSettings.RemoteMessageDisplayType = remoteMessageDisplayType.getSmRemoteMessageDisplayType();
        }
        return smSettings;
    }

}
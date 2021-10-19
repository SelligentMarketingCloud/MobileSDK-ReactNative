
package com.selligent;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import android.graphics.Color;
import android.util.Log;

import com.facebook.react.bridge.ActivityEventListener;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.LifecycleEventListener;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.google.gson.Gson;
import com.google.gson.reflect.TypeToken;
import com.selligent.sdk.SMCallback;
import com.selligent.sdk.SMDeviceInfos;
import com.selligent.sdk.SMEvent;
import com.selligent.sdk.SMForegroundGcmBroadcastReceiver;
import com.selligent.sdk.SMInAppMessage;
import com.selligent.sdk.SMInAppMessageReturn;
import com.selligent.sdk.SMInAppRefreshType;
import com.selligent.sdk.SMManager;
import com.selligent.sdk.SMNotificationButton;
import com.selligent.sdk.SMRemoteMessageDisplayType;
import com.selligent.sdk.SMSettings;

import java.util.ArrayList;
import java.util.HashMap;

public class RNSelligent extends ReactContextBaseJavaModule implements LifecycleEventListener, ActivityEventListener {

    private final ReactApplicationContext reactContext;
    private final SMManager smManager;
    private EventReceiver eventReceiver;
    private SMForegroundGcmBroadcastReceiver receiver;

    public static final String REACT_CLASS = "SelligentReactNative"; // for logging purposes


    public RNSelligent(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
        reactContext.addLifecycleEventListener(this);
        reactContext.addActivityEventListener(this);
        this.smManager = SMManager.getInstance();
    }

    @Override
    public String getName() {
        return "RNSelligent";
    }

    public static void configure(Application application) {
        try {
            final HashMap<String, Object> settingsHashMap = new Gson().fromJson(
                    BuildConfig.SELLIGENT_SETTINGS, new TypeToken<HashMap<String, Object>>() {}.getType()
            );
            final Settings settings = Settings.fromHashMap(settingsHashMap);
            final SMSettings smSettings = SMSettingsFactory.getSMSettings(settings);
            final String notificationActivityName = settings.getActivityName();

            SMManager.NOTIFICATION_ACTIVITY = (Class<? extends Activity>) Class.forName(notificationActivityName);

            final SMManager smManager = SMManager.getInstance();
            smManager.start(smSettings, application);

            final Resources resources = application.getResources();

            if (settings.getNotificationSmallIcon() != null && !settings.getNotificationSmallIcon().isEmpty()) {
                final int smallIconResourceId = resources.getIdentifier(settings.getNotificationSmallIcon(), "drawable", application.getPackageName());
                if(smallIconResourceId != 0) {
                    smManager.setNotificationSmallIcon(smallIconResourceId);
                }
            }

            if (settings.getNotificationLargeIcon() != null && !settings.getNotificationLargeIcon().isEmpty()) {
                final int largeIconResourceId = resources.getIdentifier(settings.getNotificationLargeIcon(), "drawable", application.getPackageName());
                if (largeIconResourceId != 0) {
                    smManager.setNotificationLargeIcon(largeIconResourceId);
                }
            }

            if (settings.getNotificationIconColor() != null && !settings.getNotificationIconColor().isEmpty()) {
                try {
                    final int color = Color.parseColor(settings.getNotificationIconColor());
                    smManager.setNotificationIconColor(color);
                } catch (IllegalArgumentException e) {
                    Log.e("RNSelligent", "notificationIconColor must be a color hex string.");
                }
            }

        } catch (ClassNotFoundException e) {
            Log.e("RNSelligent", "SMManager start failed: an error occurred while setting the NotificationActivity", e);
        }
    }

    /* Our methods: */

    @ReactMethod
    public void getVersionLib(Callback successCallback) {
        final String versionLib = SMManager.VERSION_LIB;
        successCallback.invoke(versionLib);
    }

    @ReactMethod
    public void enableInAppMessages(ReadableMap enabled) {
        final ReadableType enabledType = enabled.getType("enabled");
        if (enabledType == ReadableType.Boolean) {
            enableInAppMessages(enabled.getBoolean("enabled"));
        } else if (enabledType == ReadableType.Number) {
            enableInAppMessages(enabled.getInt("enabled"));
        }
    }

    private void enableInAppMessages(Boolean enable) {
        if (enable) {
            smManager.enableInAppMessages(SMInAppRefreshType.Daily);
        } else {
            smManager.disableInAppMessages();
        }
    }

    private void enableInAppMessages(Integer inAppMessageRefreshTypeIndex) {
        final InAppMessageRefreshType inAppMessageRefreshType = InAppMessageRefreshType.valueOf(inAppMessageRefreshTypeIndex);
        final SMInAppRefreshType smInAppRefreshType = inAppMessageRefreshType.getSmInAppRefreshType();

        smManager.enableInAppMessages(smInAppRefreshType);
    }

    @ReactMethod
    public void areInAppMessagesEnabled(Callback successCallback) {
        final Boolean areInAppMessagesEnabled = smManager.areInAppMessagesEnabled();
        successCallback.invoke(areInAppMessagesEnabled);
    }

    @ReactMethod
    public void displayMessage(String messageId) {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {
            smManager.displayMessage(messageId, currentActivity);
        }
    }

    @ReactMethod
    public void getInAppMessages(final Callback successCallback) {
        smManager.getInAppMessages(new SMInAppMessageReturn() {
            @Override
            public void onRetrieve(ArrayList<SMInAppMessage> inAppMessages) {
                WritableArray resultingMessagesArray = new WritableNativeArray();

                for (SMInAppMessage message : inAppMessages) {
                    WritableMap messageMap = new WritableNativeMap();

                    messageMap.putString("id", message.id);
                    messageMap.putString("title", message.title);
                    messageMap.putString("body", message.getBody());
                    messageMap.putDouble("creationDate", message.getCreationDate());
                    messageMap.putDouble("expirationDate", message.getExpirationDate());
                    messageMap.putDouble("receptionDate", message.getReceptionDate());
                    messageMap.putBoolean("hasBeenSeen", message.hasBeenSeen());
                    messageMap.putDouble("type", message.getType().getValue());

                    WritableArray buttonsArray = new WritableNativeArray();

                    SMNotificationButton buttons[] = message.getButtons();

                    if(buttons != null) {
                        for(SMNotificationButton button : buttons) {
                            WritableMap buttonMap = new WritableNativeMap();

                            buttonMap.putString("id", button.id);
                            buttonMap.putString("value", button.value);
                            buttonMap.putString("label", button.label);
                            buttonMap.putInt("action", button.action);
                            buttonMap.putInt("type", button.type);

                            buttonsArray.pushMap(buttonMap);
                        }
                    }

                    messageMap.putArray("buttons", buttonsArray);

                    resultingMessagesArray.pushMap(messageMap);
                }

                successCallback.invoke(resultingMessagesArray);
            }
        });
    }

    @ReactMethod
    public void setInAppMessageAsSeen(final String messageId, final Callback successCallback, final Callback errorCallback) {
        smManager.getInAppMessages(new SMInAppMessageReturn() {
            @Override
            public void onRetrieve(ArrayList<SMInAppMessage> inAppMessages) {
                for(SMInAppMessage message : inAppMessages) {
                    if(message.id.equals(messageId)) {
                        smManager.setInAppMessageAsSeen(message);
                        successCallback.invoke();
                        return;
                    }
                }
                errorCallback.invoke(String.format("No message with id %s found", messageId));
            }
        });
    }

    @ReactMethod
    public void executeButtonAction(final String buttonId, final String messageId, final Callback successCallback, final Callback errorCallback) {
        smManager.getInAppMessages(new SMInAppMessageReturn() {
            @Override
            public void onRetrieve(ArrayList<SMInAppMessage> inAppMessages) {
                for(SMInAppMessage message : inAppMessages) {
                    if(message.id.equals(messageId)) {
                        for(SMNotificationButton button : message.getButtons()) {
                            if(button.id.equals(buttonId)) {
                                smManager.executeButtonAction(reactContext, button, message);
                                successCallback.invoke();
                                return;
                            }
                        }
                        errorCallback.invoke("buttonId does not exist in message.");
                        return;
                    }
                }
                errorCallback.invoke(String.format("No message with id %s found", messageId));
            }
        });
    }

    @ReactMethod
    public void setDebug(Boolean enable) {
        SMManager.DEBUG = enable;
    }

    @ReactMethod
    public void enableGeolocation(Boolean enable) {
        if (enable) {
            smManager.enableGeolocation();
        } else {
            smManager.disableGeolocation();
        }
    }

    @ReactMethod
    public void isGeolocationEnabled(Callback successCallback) {
        final Boolean isGeolocationEnabled = smManager.isGeolocationEnabled();
        successCallback.invoke(isGeolocationEnabled);
    }

    @ReactMethod
    public void sendEvent(ReadableMap eventMap, final Callback successCallback, final Callback errorCallback) {
        final Event event = Event.fromHashMap(eventMap.toHashMap());
        final SMEvent smEvent = SMEventFactory.getSMEvent(event, new SMCallback() {
            @Override
            public void onSuccess(String message) {
                successCallback.invoke(message);
            }

            @Override
            public void onError(int responseCode, Exception e) {
                errorCallback.invoke(responseCode);
            }
        });

        smManager.sendSMEvent(smEvent);
    }

    @ReactMethod
    public void getDeviceId(Callback successCallback) {
        final String deviceId = smManager.getDeviceId();
        successCallback.invoke(deviceId);
    }

    @ReactMethod
    public void enableNotifications(Boolean enable) {
        if (enable) {
            smManager.enableNotifications();
        } else {
            smManager.disableNotifications();
        }
    }

    @ReactMethod
    public void displayLastReceivedRemotePushNotification() {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {
            smManager.displayLastReceivedRemotePushNotification(currentActivity);
        }
    }

    @ReactMethod
    public void getLastRemotePushNotification(Callback successCallback) {
        final HashMap<String, String> notificationMap = smManager.getLastRemotePushNotification();

        WritableMap resultingNotificationMap = new WritableNativeMap();
        if (notificationMap != null) {
            final String id = notificationMap.get("id");
            final String title = notificationMap.get("title");

            resultingNotificationMap.putString("id", id);
            resultingNotificationMap.putString("title", title);
        }

        successCallback.invoke(resultingNotificationMap);
    }

    @ReactMethod
    public void setNotificationSmallIcon(String iconName) {
        final int resourceId = processNotificationIcon(iconName);
        smManager.setNotificationSmallIcon(resourceId);
    }

    @ReactMethod
    public void setNotificationLargeIcon(String iconName) {
        final int resourceId = processNotificationIcon(iconName);

        smManager.setNotificationLargeIcon(resourceId);
    }

    private int processNotificationIcon(String iconName) {
        final Resources resources = reactContext.getResources();
        final int resourceId = resources.getIdentifier(iconName, "drawable", reactContext.getPackageName());

        if (resourceId == 0) {
            throw new IllegalArgumentException("Could not find a drawable with the name " + iconName);
        }

        return resourceId;
    }

    @ReactMethod
    public void setNotificationIconColor(final String colorString, final Callback successCallback, final Callback errorCallback) {
        try {
            final int color = Color.parseColor(colorString);
            smManager.setNotificationIconColor(color);
            successCallback.invoke();
        } catch (IllegalArgumentException e) {
            errorCallback.invoke("color must be a color hex string.");
        }
    }

    @ReactMethod
    public void setNotificationActivity(final String activityName, final Callback successCallback, final Callback errorCallback) {
        try {
            SMManager.NOTIFICATION_ACTIVITY = (Class<? extends Activity>) Class.forName(activityName);
            successCallback.invoke();
        } catch (ClassNotFoundException e) {
            errorCallback.invoke(String.format("Activity %s not found.", activityName));
        }
    }

    @ReactMethod
    public void getGCMToken(Callback callback) {
        final String gcmToken = smManager.getGCMToken();
        callback.invoke(gcmToken);
    }

    @ReactMethod
    public void getRemoteMessagesDisplayType(Callback successCallback) {
        final SMRemoteMessageDisplayType smRemoteMessageDisplayType = smManager.getRemoteMessagesDisplayType();
        final RemoteMessageDisplayType remoteMessageDisplayType = RemoteMessageDisplayType.valueOf(smRemoteMessageDisplayType);
        final Integer resultingRemoteMessageDisplayTypeIndex = remoteMessageDisplayType.getIndex();

        successCallback.invoke(resultingRemoteMessageDisplayTypeIndex);
    }

    @ReactMethod
    public void areNotificationsEnabled(Callback successCallback) {
        final Boolean areNotificationsEnabled = smManager.areNotificationEnabled();

        successCallback.invoke(areNotificationsEnabled);
    }

    @ReactMethod
    public void subscribeToEvents(ReadableArray customEvents) {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {

            final LocalBroadcastManager localBroadcastManager = LocalBroadcastManager.getInstance(currentActivity);

            if (eventReceiver == null) {
                eventReceiver = new EventReceiver(reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class));
            } else {
                localBroadcastManager.unregisterReceiver(eventReceiver);
            }

            final IntentFilter filter = new IntentFilter();
            filter.addAction(SMManager.BROADCAST_EVENT_RECEIVED_IN_APP_MESSAGE);
            filter.addAction(SMManager.BROADCAST_EVENT_RECEIVED_IN_APP_CONTENTS);
            filter.addAction(SMManager.BROADCAST_EVENT_WILL_DISPLAY_NOTIFICATION);
            filter.addAction(SMManager.BROADCAST_EVENT_WILL_DISMISS_NOTIFICATION);
            filter.addAction(SMManager.BROADCAST_EVENT_BUTTON_CLICKED);
            filter.addAction(SMManager.BROADCAST_EVENT_RECEIVED_GCM_TOKEN);
            for (int i = 0; i < customEvents.size(); i++) {
                filter.addAction(customEvents.getString(i));
            }

            localBroadcastManager.registerReceiver(eventReceiver, filter);
        }
    }

    @ReactMethod
    public void setFirebaseToken(String token) {
        smManager.setFirebaseToken(token);
    }

    @Override
    public void onHostResume() {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {
            if (receiver == null)
            {
                receiver = new SMForegroundGcmBroadcastReceiver(currentActivity);
            }
            currentActivity.registerReceiver(receiver, receiver.getIntentFilter());

            smManager.checkAndDisplayMessage(currentActivity.getIntent(), currentActivity);
        }
    }

    @Override
    public void onHostPause() {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {
            currentActivity.unregisterReceiver(receiver);
        }
    }

    @Override
    public void onHostDestroy() { }

    @Override
    public void onNewIntent(Intent intent) {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {
            currentActivity.setIntent(intent);
            smManager.checkAndDisplayMessage(intent, currentActivity);
        }
    }

    @Override
    public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent data) { }

}

package com.selligent;

import android.app.Activity;
import android.app.Application;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;

import androidx.appcompat.app.AppCompatActivity;
import androidx.lifecycle.Observer;
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
import com.selligent.rnmobilesdk.BroadcastEventType;
import com.selligent.rnmobilesdk.ButtonBroadcastEventDataParser;
import com.selligent.rnmobilesdk.DeviceIdBroadcastEventDataParser;
import com.selligent.rnmobilesdk.Event;
import com.selligent.rnmobilesdk.GCMTokenBroadcastEventDataParser;
import com.selligent.rnmobilesdk.InAppMessageBroadcastEventDataParser;
import com.selligent.rnmobilesdk.InAppMessageRefreshType;
import com.selligent.rnmobilesdk.NotificationMessageBroadcastEventDataParser;
import com.selligent.rnmobilesdk.RemoteMessageDisplayType;
import com.selligent.rnmobilesdk.SMEventFactory;
import com.selligent.rnmobilesdk.SMSettingsFactory;
import com.selligent.rnmobilesdk.Settings;
import com.selligent.sdk.SMCallback;
import com.selligent.sdk.SMEvent;
import com.selligent.sdk.SMForegroundGcmBroadcastReceiver;
import com.selligent.sdk.SMInAppMessage;
import com.selligent.sdk.SMInAppRefreshType;
import com.selligent.sdk.SMManager;
import com.selligent.sdk.SMNotificationButton;
import com.selligent.sdk.SMNotificationMessage;
import com.selligent.sdk.SMObserverManager;
import com.selligent.sdk.SMRemoteMessageDisplayType;
import com.selligent.sdk.SMSettings;

import java.util.HashMap;

public class RNSelligent extends ReactContextBaseJavaModule implements LifecycleEventListener, ActivityEventListener {

    private static final String RN_SELLIGENT_NAME = "RNSelligent";
    private final ReactApplicationContext reactContext;
    private final SMManager smManager;
    EventReceiver eventReceiver;
    SMForegroundGcmBroadcastReceiver receiver;
    private static SMInAppRefreshType inAppMessageRefreshType;

    public static final String REACT_CLASS = "SelligentReactNative"; // for logging purposes

    boolean areObserverStarted = false;

    //region getter
    static SMManager getSMManager()
    {
        return SMManager.getInstance();
    }

    static String getSelligentSettings()
    {
        return BuildConfig.SELLIGENT_SETTINGS;
    }

    static Class<? extends Activity> getActivityClass(String notificationActivityName) throws Exception
    {
        return (Class<? extends Activity>) Class.forName(notificationActivityName);
    }
    //endregion


    public RNSelligent(ReactApplicationContext reactContext) {
        super(reactContext);
        this.reactContext = reactContext;
        reactContext.addLifecycleEventListener(this);
        reactContext.addActivityEventListener(this);
        this.smManager = getSMManager();
    }

    @Override
    public String getName() {
        return RN_SELLIGENT_NAME;
    }

    public static void configure(Application application) {
        try {
            final HashMap<String, Object> settingsHashMap = new Gson().fromJson(
                    getSelligentSettings(), new TypeToken<HashMap<String, Object>>() {}.getType()
            );
            final Settings settings = Settings.fromHashMap(settingsHashMap);
            final SMSettings smSettings = SMSettingsFactory.getSMSettings(settings);
            final String notificationActivityName = settings.getActivityName();

            SMManager.NOTIFICATION_ACTIVITY = getActivityClass(notificationActivityName);
            inAppMessageRefreshType = settings.getInAppMessageRefreshType().getSmInAppRefreshType();

            final SMManager smManager = getSMManager();
            SMManager.DEBUG = BuildConfig.BUILD_TYPE.equals("debug") || settings.getEnableAndroidLogging();
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
                    Log.e(RN_SELLIGENT_NAME, "notificationIconColor must be a color hex string.");
                }
            }

        } catch (Exception e) {
            Log.e(RN_SELLIGENT_NAME, "SMManager start failed: an error occurred while setting the NotificationActivity", e);
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
        final String enabledProperty = "enabled";
        final ReadableType enabledType = enabled.getType(enabledProperty);

        if (enabledType == ReadableType.Boolean) {
            enableInAppMessages(enabled.getBoolean(enabledProperty));
        } 
        else if (enabledType == ReadableType.Number) {
            enableInAppMessages(enabled.getInt(enabledProperty));
        }
    }

    private void enableInAppMessages(boolean enable) {
        if (enable) {
            smManager.enableInAppMessages(inAppMessageRefreshType);
        } else {
            smManager.disableInAppMessages();
        }
    }

    private void enableInAppMessages(Integer inAppMessageRefreshTypeIndex) {
        final InAppMessageRefreshType refreshType = InAppMessageRefreshType.valueOf(inAppMessageRefreshTypeIndex);
        final SMInAppRefreshType smInAppRefreshType = refreshType.getSmInAppRefreshType();

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
            smManager.displayInAppMessage(messageId, currentActivity);
        }
    }

    @ReactMethod
    public void getInAppMessages(final Callback successCallback) {
        smManager.getInAppMessages(inAppMessages -> {
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

                SMNotificationButton[] buttons = message.getButtons();

                if(buttons != null) {
                    for(SMNotificationButton button : buttons) {
                        WritableMap buttonMap = new WritableNativeMap();

                        buttonMap.putString("id", button.id);
                        buttonMap.putString("value", button.value);
                        buttonMap.putString("label", button.label);
                        buttonMap.putInt("type", button.type);

                        buttonsArray.pushMap(buttonMap);
                    }
                }

                messageMap.putArray("buttons", buttonsArray);

                resultingMessagesArray.pushMap(messageMap);
            }

            successCallback.invoke(resultingMessagesArray);
        });
    }

    @ReactMethod
    public void setInAppMessageAsSeen(final String messageId, final Callback successCallback, final Callback errorCallback) {
        smManager.getInAppMessages(inAppMessages ->
        {
            for(SMInAppMessage message : inAppMessages)
            {
                if(message.id.equals(messageId))
                {
                    smManager.setInAppMessageAsSeen(message);
                    successCallback.invoke();
                    return;
                }
            }
            errorCallback.invoke(String.format("No message with id %s found", messageId));
        });
    }

    @ReactMethod
    public void setInAppMessageAsUnseen(final String messageId, final Callback successCallback, final Callback errorCallback)
    {
        smManager.getInAppMessages(inAppMessages ->
        {
            for(SMInAppMessage message : inAppMessages)
            {
                if(message.id.equals(messageId))
                {
                    smManager.setInAppMessageAsUnseen(message);
                    successCallback.invoke();
                    return;
                }
            }
            errorCallback.invoke(String.format("No message with id %s found", messageId));
        });
    }

    @ReactMethod
    public void setInAppMessageAsDeleted(final String messageId, final Callback successCallback, final Callback errorCallback)
    {
        smManager.getInAppMessages(inAppMessages ->
        {
            for(SMInAppMessage message : inAppMessages)
            {
                if(message.id.equals(messageId))
                {
                    smManager.deleteInAppMessage(messageId);
                    successCallback.invoke();
                    return;
                }
            }
            errorCallback.invoke(String.format("No message with id %s found", messageId));
        });
    }

    @ReactMethod
    public void executeButtonAction(final String buttonId, final String messageId, final Callback successCallback, final Callback errorCallback) {
        smManager.getInAppMessages(inAppMessages -> {
            for(SMInAppMessage message : inAppMessages) {
                if(message.id.equals(messageId))
                {
                    SMNotificationButton[] buttons = message.getButtons();
                    if (buttons != null)
                    {
                        for (SMNotificationButton button : message.getButtons())
                        {
                            if (button.id.equals(buttonId))
                            {
                                smManager.executeButtonAction(reactContext, button, message);
                                successCallback.invoke();
                                return;
                            }
                        }
                    }
                    errorCallback.invoke("buttonId does not exist in message.");
                    return;
                }
            }
            errorCallback.invoke(String.format("No message with id %s found", messageId));
        });
    }

    @ReactMethod
    public void setDebug(Boolean enable) {
        SMManager.DEBUG = enable;
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
        if (Boolean.TRUE.equals(enable)) {
            smManager.enableNotifications();
        } else {
            smManager.disableNotifications();
        }
    }

    public static void enableNotifications() {
        SMManager.getInstance().enableNotifications();
    }

    @ReactMethod
    public void displayLastReceivedRemotePushNotification(String templateId) {
        final Activity currentActivity = getCurrentActivity();

        if (currentActivity != null) {
            smManager.displayLastReceivedNotificationContent(currentActivity);
        }
    }

    @ReactMethod
    public void displayLastReceivedNotification()
    {
        smManager.displayLastReceivedNotification();
    }

    @ReactMethod
    public void getLastRemotePushNotification(Callback successCallback) {
        final SMNotificationMessage notification = smManager.retrieveLastReceivedNotificationContent();

        WritableMap resultingNotificationMap = new WritableNativeMap();
        
        if (notification != null) {
            resultingNotificationMap.putString("id", notification.getId());
            resultingNotificationMap.putString("title", notification.getNotificationTitle());
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

        if (currentActivity != null)
        {
            if (currentActivity instanceof AppCompatActivity)
            {
                AppCompatActivity thisActivity = (AppCompatActivity)currentActivity;
                DeviceEventManagerModule.RCTDeviceEventEmitter rctDeviceEventEmitter = reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class);

                thisActivity.runOnUiThread(() -> {
                    if (!areObserverStarted)
                    {
                        Log.d(RN_SELLIGENT_NAME, "Instantiating the observers on the UI thread");
                        SMObserverManager observerManager = smManager.getObserverManager();

                        // Token received
                        final Observer<String> tokenObserver = token -> {
                            String eventName = BroadcastEventType.ReceivedGCMToken.getBroadcastEventType();
                            GCMTokenBroadcastEventDataParser broadcastEventDataParser = new GCMTokenBroadcastEventDataParser();
                            final WritableMap data = broadcastEventDataParser.wrap(token);
                            rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, data));
                        };
                        observerManager.observeToken(thisActivity, tokenObserver);

                        // Device id received
                        final Observer<String> deviceIdObserver = deviceId -> {
                            String eventName = BroadcastEventType.ReceivedDeviceId.getBroadcastEventType();
                            DeviceIdBroadcastEventDataParser broadcastEventDataParser = new DeviceIdBroadcastEventDataParser();
                            final WritableMap data = broadcastEventDataParser.wrap(deviceId);
                            rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, data));
                        };
                        observerManager.observeDeviceId(thisActivity, deviceIdObserver);

                        // InApp messages received
                        final Observer<SMInAppMessage[]> inAppMessageObserver = inAppMessages -> {
                            if (inAppMessages != null)
                            {
                                String eventName = BroadcastEventType.ReceivedInAppMessage.getBroadcastEventType();
                                InAppMessageBroadcastEventDataParser broadcastEventDataParser = new InAppMessageBroadcastEventDataParser();
                                final WritableMap data = broadcastEventDataParser.wrap(inAppMessages);
                                rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, data));
                            }
                        };
                        observerManager.observeInAppMessages(thisActivity, inAppMessageObserver);

                        // Button clicked
                        final Observer<SMNotificationButton> clickedButtonObserver = button -> {
                            if (button != null)
                            {
                                String eventName = BroadcastEventType.ButtonClicked.getBroadcastEventType();
                                ButtonBroadcastEventDataParser broadcastEventDataParser = new ButtonBroadcastEventDataParser();
                                final WritableMap data = broadcastEventDataParser.wrap(button);
                                rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, data));
                            }
                        };
                        observerManager.observeClickedButton(thisActivity, clickedButtonObserver);

                        // Message dismissed
                        final Observer<Void> dismissedMessageObserver = object -> {
                            String eventName = BroadcastEventType.WillDismissNotification.getBroadcastEventType();
                            rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, null));
                        };
                        observerManager.observeDismissedMessage(thisActivity, dismissedMessageObserver);

                        // Message displayed
                        final Observer<Void> displayedMessageObserver = object -> {
                            String eventName = BroadcastEventType.WillDisplayNotification.getBroadcastEventType();
                            rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, null));
                        };
                        observerManager.observeDisplayedMessage(thisActivity, displayedMessageObserver);

                        // Push received
                        final Observer<SMNotificationMessage> pushReceivedObserver = notificationMessage -> {
                            if (notificationMessage != null)
                            {
                                String eventName = BroadcastEventType.ReceivedNotification.getBroadcastEventType();
                                NotificationMessageBroadcastEventDataParser broadcastEventDataParser = new NotificationMessageBroadcastEventDataParser();
                                final WritableMap data = broadcastEventDataParser.wrap(notificationMessage);
                                rctDeviceEventEmitter.emit(eventName, getBroadcastData(eventName, data));
                            }
                        };
                        observerManager.observePushReceived(thisActivity, pushReceivedObserver);

                        // Custom events
                        final Observer<String> customEventObserver = event -> rctDeviceEventEmitter.emit(BroadcastEventType.TriggeredCustomEvent.getBroadcastEventType(), getBroadcastData(event, null));
                        observerManager.observeEvent(thisActivity, customEventObserver);

                        areObserverStarted = true;
                    }
                    else
                    {
                        Log.d(RN_SELLIGENT_NAME, "Observers already instantiated");
                    }
                });
            }
            else
            {
                final LocalBroadcastManager localBroadcastManager = LocalBroadcastManager.getInstance(currentActivity);

                if (eventReceiver == null) {
                    eventReceiver = new EventReceiver(reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class));
                } else {
                    localBroadcastManager.unregisterReceiver(eventReceiver);
                }

                final IntentFilter filter = new IntentFilter();
                filter.addAction(SMManager.BROADCAST_EVENT_RECEIVED_IN_APP_MESSAGE);
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
    }

    WritableMap getBroadcastData(String eventName, WritableMap data)
    {
        final WritableMap broadcastData = new WritableNativeMap();

        broadcastData.putString("broadcastEventType", eventName);
        broadcastData.putMap("data", data);

        return broadcastData;
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
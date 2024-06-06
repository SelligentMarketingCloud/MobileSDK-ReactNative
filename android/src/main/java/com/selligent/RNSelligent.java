package com.selligent;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.Application;
import android.content.Context;
import android.content.Intent;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.localbroadcastmanager.content.LocalBroadcastManager;

import com.facebook.react.bridge.ActivityEventListener;
import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.LifecycleEventListener;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.ReadableType;
import com.facebook.react.modules.core.DeviceEventManagerModule;
import com.selligent.rnmobilesdk.DelayedEvent;
import com.selligent.rnmobilesdk.Manager;
import com.selligent.sdk.SMForegroundGcmBroadcastReceiver;

import java.util.ArrayList;
import java.util.Map;

public class RNSelligent extends ReactContextBaseJavaModule implements LifecycleEventListener, ActivityEventListener {
    private final ReactApplicationContext reactContext;
    private final Manager manager;
    EventReceiver eventReceiver;
    SMForegroundGcmBroadcastReceiver receiver;

    static Manager getManager() {
        return Manager.getInstance();
    }

    static String getSelligentSettings() {
        return BuildConfig.SELLIGENT_SETTINGS;
    }

    Activity getActivity()
    {
        return this.getCurrentActivity();
    }

    public RNSelligent(ReactApplicationContext reactContext) {
        super(reactContext);

        this.reactContext = reactContext;
        reactContext.addLifecycleEventListener(this);
        reactContext.addActivityEventListener(this);
        this.manager = RNSelligent.getManager();
    }

    @NonNull
    @Override
    public String getName() {
        return Manager.RN_SELLIGENT_NAME;
    }

    public static void configure(Application application) {
        RNSelligent.getManager().configure(application, RNSelligent.getSelligentSettings(), BuildConfig.BUILD_TYPE.equals("debug"));
    }

    @ReactMethod
    public void getVersionLib(Callback successCallback) {
        successCallback.invoke(manager.getVersionLib());
    }

    @ReactMethod
    public void enableInAppMessages(ReadableMap enabled) {
        String enabledProperty = "enabled";
        ReadableType enabledType = enabled.getType(enabledProperty);

        if (enabledType == ReadableType.Boolean) {
            this.manager.enableInAppMessages(enabled.getBoolean(enabledProperty));
        }
        else if (enabledType == ReadableType.Number) {
            this.manager.enableInAppMessages(enabled.getInt(enabledProperty));
        }
    }

    @ReactMethod
    public void areInAppMessagesEnabled(Callback successCallback) {
        successCallback.invoke(this.manager.areInAppMessagesEnabled());
    }

    @ReactMethod
    public void displayMessage(String messageId) {
        this.manager.displayMessage(messageId, this.getCurrentActivity());
    }

    @ReactMethod
    public void getInAppMessages(Callback successCallback) {
        this.manager.getInAppMessages(list ->
            successCallback.invoke(RNHelpers.convertListToWritableArray(list))
        );
    }

    @ReactMethod
    public void setInAppMessageAsSeen(String messageId, Callback successCallback, Callback errorCallback) {
        this.manager.setInAppMessageAsSeen(messageId, error ->
            processErrorStringToCallback(error, successCallback, errorCallback)
        );
    }

    @ReactMethod
    public void setInAppMessageAsUnseen(String messageId, Callback successCallback, Callback errorCallback) {
        this.manager.setInAppMessageAsUnseen(messageId, error ->
            processErrorStringToCallback(error, successCallback, errorCallback)
        );
    }

    @ReactMethod
    public void setInAppMessageAsDeleted(String messageId, Callback successCallback, Callback errorCallback) {
        this.manager.setInAppMessageAsDeleted(messageId, error ->
            processErrorStringToCallback(error, successCallback, errorCallback)
        );
    }

    @ReactMethod
    public void executeButtonAction(String buttonId, String messageId, Callback successCallback, Callback errorCallback) {
        this.manager.executeButtonAction(this.getCurrentActivity(), buttonId, messageId, error ->
            processErrorStringToCallback(error, successCallback, errorCallback)
        );
    }

    @ReactMethod
    public void setDebug(Boolean enable) {
        Manager.setDebug(enable);
    }

    @ReactMethod
    public void sendEvent(ReadableMap eventMap, Callback successCallback, Callback errorCallback) {
        this.manager.sendEvent(eventMap.toHashMap(), successCallback::invoke, errorCallback::invoke);
    }

    @ReactMethod
    public void getDeviceId(Callback successCallback) {
        successCallback.invoke(this.manager.getDeviceId());
    }

    @ReactMethod
    public void enableNotifications(Boolean enable) {
        this.manager.enableNotifications(enable);
    }

    public static void enableNotifications() {
        RNSelligent.getManager().enableNotifications(true);
    }

    @ReactMethod
    @SuppressWarnings("unused")
    public void displayLastReceivedRemotePushNotification(String templateId) {
        this.manager.displayLastReceivedRemotePushNotification(this.getCurrentActivity());
    }

    @ReactMethod
    public void displayLastReceivedNotification() {
        this.manager.displayLastReceivedNotification();
    }

    @ReactMethod
    public void getLastRemotePushNotification(Callback successCallback) {
        successCallback.invoke(
            RNHelpers.convertMapToWritableMap(this.manager.getLastRemotePushNotification())
        );
    }

    @ReactMethod
    public void setNotificationSmallIcon(String iconName) {
        this.manager.setNotificationSmallIcon(this.reactContext, iconName);
    }

    @ReactMethod
    public void setNotificationLargeIcon(String iconName) {
        this.manager.setNotificationLargeIcon(this.reactContext, iconName);
    }

    @ReactMethod
    public void setNotificationIconColor(String colorString, Callback successCallback, Callback errorCallback) {
        processErrorStringToCallback(
            this.manager.setNotificationIconColor(colorString),
            successCallback,
            errorCallback
        );
    }

    @ReactMethod
    public void setNotificationActivity(String activityName, Callback successCallback, Callback errorCallback) {
        processErrorStringToCallback(
            Manager.setNotificationActivity(activityName),
            successCallback,
            errorCallback
        );
    }

    @ReactMethod
    public void getGCMToken(Callback callback) {
        callback.invoke(this.manager.getGCMToken());
    }

    @ReactMethod
    public void getRemoteMessagesDisplayType(Callback successCallback) {
        successCallback.invoke(this.manager.getRemoteMessagesDisplayType());
    }

    @ReactMethod
    public void areNotificationsEnabled(Callback successCallback) {
        successCallback.invoke(this.manager.areNotificationsEnabled());
    }

    @ReactMethod
    public void subscribeToEvents(ReadableArray customEvents) {
        Activity currentActivity = this.getCurrentActivity();

        if (currentActivity == null) { return; }

        if (currentActivity instanceof AppCompatActivity) {
            AppCompatActivity activity = (AppCompatActivity)currentActivity;

            activity.runOnUiThread(() ->
                this.manager.initializeObservers(activity, this::broadcastEvent)
            );

            return;
        }

        LocalBroadcastManager localBroadcastManager = LocalBroadcastManager.getInstance(currentActivity);

        if (this.eventReceiver == null) {
            this.eventReceiver = new EventReceiver(
                reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class
            ));
        }
        else {
            localBroadcastManager.unregisterReceiver(this.eventReceiver);
        }

        localBroadcastManager.registerReceiver(
            this.eventReceiver,
            Manager.eventsIntentFilter(customEvents.toArrayList())
        );
    }

    @ReactMethod
    public void executePushAction() {
        this.emitDelayedEvents();

        Activity currentActivity = this.getActivity();

        if (currentActivity == null) { return; }

        this.manager.executePushAction(currentActivity);
    }

    void emitDelayedEvents()
    {
        ArrayList<DelayedEvent> delayedEvents = this.manager.getStoredEvents();

        if (delayedEvents.size() > 0)
        {
            for (DelayedEvent delayedEvent: delayedEvents)
            {
                this.reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class).emit(
                        delayedEvent.Name,
                        RNHelpers.convertMapToWritableMap(delayedEvent.Data)
                );
            }
            delayedEvents.clear();
        }
    }

    @ReactMethod
    public void setFirebaseToken(String token) {
        this.manager.setFirebaseToken(token);
    }

    @SuppressLint("UnspecifiedRegisterReceiverFlag")
    @Override
    public void onHostResume() {
        Activity currentActivity = this.getCurrentActivity();

        if (currentActivity == null) { return; }

        if (this.receiver == null) {
            this.receiver = new SMForegroundGcmBroadcastReceiver(currentActivity);
        }

        if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.TIRAMISU) {
            currentActivity.registerReceiver(this.receiver, this.receiver.getIntentFilter(), Context.RECEIVER_NOT_EXPORTED);
        }
        else {
            currentActivity.registerReceiver(this.receiver, this.receiver.getIntentFilter());
        }

        this.manager.checkAndDisplayMessage(currentActivity.getIntent(), currentActivity, this::broadcastEvent);
    }

    @Override
    public void onHostPause() {
        Activity currentActivity = this.getCurrentActivity();

        if (currentActivity == null) { return; }

        currentActivity.unregisterReceiver(this.receiver);
    }

    @Override
    public void onHostDestroy() { }

    @Override
    public void onNewIntent(Intent intent) {
        Activity currentActivity = this.getCurrentActivity();

        if (currentActivity == null) { return; }

        currentActivity.setIntent(intent);
        this.manager.checkAndDisplayMessage(intent, currentActivity, this::broadcastEvent);
    }

    @Override
    public void onActivityResult(Activity activity, int requestCode, int resultCode, Intent data) { }

    private void broadcastEvent(String eventName, Map<String, Object> data) {
        if (RNSelligent.getManager().canEmitEvent())
        {
            this.reactContext.getJSModule(DeviceEventManagerModule.RCTDeviceEventEmitter.class).emit(
                    eventName,
                    RNHelpers.convertMapToWritableMap(data)
            );
        }
        else
        {
            RNSelligent.getManager().storeEvent(eventName, data);
        }
    }


    private void processErrorStringToCallback(String error, Callback successCallback, Callback errorCallback) {
        if (error == null) {
            successCallback.invoke();
            return;
        }

        errorCallback.invoke(error);
    }
}
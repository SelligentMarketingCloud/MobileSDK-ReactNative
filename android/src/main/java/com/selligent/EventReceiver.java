package com.selligent;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.text.TextUtils;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.modules.core.DeviceEventManagerModule.RCTDeviceEventEmitter;
import com.selligent.rnmobilesdk.BroadcastDataFactory;


class EventReceiver extends BroadcastReceiver {

    private RCTDeviceEventEmitter rctDeviceEventEmitter;

    public EventReceiver(RCTDeviceEventEmitter rctDeviceEventEmitter) {
        this.rctDeviceEventEmitter = rctDeviceEventEmitter;
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        final String smBroadcastEventType = intent.getAction();
        if (TextUtils.isEmpty(smBroadcastEventType)) return;

        final WritableMap broadcastData = BroadcastDataFactory.getBroadcastData(smBroadcastEventType, intent);
        final String eventName = broadcastData.getString("broadcastEventType");

        rctDeviceEventEmitter.emit(eventName, broadcastData);
    }

}

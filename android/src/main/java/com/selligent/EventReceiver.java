package com.selligent;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import com.facebook.react.modules.core.DeviceEventManagerModule.RCTDeviceEventEmitter;
import com.selligent.rnmobilesdk.BroadcastDataFactory;

class EventReceiver extends BroadcastReceiver {
    private final RCTDeviceEventEmitter rctDeviceEventEmitter;

    public EventReceiver(RCTDeviceEventEmitter rctDeviceEventEmitter) {
        this.rctDeviceEventEmitter = rctDeviceEventEmitter;
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        String smBroadcastEventType = intent.getAction();

        if (smBroadcastEventType == null || smBroadcastEventType.isEmpty()) return;

        this.rctDeviceEventEmitter.emit(
            smBroadcastEventType,
            BroadcastDataFactory.getBroadcastData(smBroadcastEventType, intent)
        );
    }
}

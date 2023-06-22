package com.selligent;

import android.content.Intent;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.selligent.sdk.SMManager;

class GCMTokenBroadcastEventDataParser implements BroadcastEventDataParser {
    @Override
    public WritableMap parse(Intent intent) {
        final String token = intent.getStringExtra(SMManager.BROADCAST_DATA_GCM_TOKEN);

        return wrap(token);
    }

    public WritableMap wrap(String token) {
        final WritableMap resultingMap = new WritableNativeMap();

        resultingMap.putString("token", token);

        return resultingMap;
    }
}

package com.selligent;

import android.content.Intent;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.selligent.sdk.SMManager;

class GCMTokenBroadcastEventDataParser implements BroadcastEventDataParser {
    @Override
    public WritableMap parse(Intent intent) {
        final WritableMap resultingMap = new WritableNativeMap();

        final String token = intent.getStringExtra(SMManager.BROADCAST_DATA_GCM_TOKEN);
        resultingMap.putString("token", token);

        return resultingMap;
    }
}

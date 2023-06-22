package com.selligent;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;

class DeviceIdBroadcastEventDataParser {

    public WritableMap wrap(String deviceId) {
        final WritableMap resultingMap = new WritableNativeMap();

        resultingMap.putString("deviceId", deviceId);

        return resultingMap;
    }
}

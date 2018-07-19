package com.selligent;

import android.content.Intent;

import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeArray;
import com.facebook.react.bridge.WritableNativeMap;
import com.selligent.sdk.SMInAppMessage;
import com.selligent.sdk.SMManager;

class InAppMessageBroadcastEventDataParser implements BroadcastEventDataParser {
    @Override
    public WritableMap parse(Intent intent) {
        final WritableMap resultingMap = new WritableNativeMap();

        SMInAppMessage[] messages = (SMInAppMessage[])intent.getSerializableExtra(SMManager.BROADCAST_DATA_IN_APP_MESSAGES);
        final WritableArray messageArray = new WritableNativeArray();
        for (SMInAppMessage message : messages) {
            WritableMap messageMap = new WritableNativeMap();
            messageMap.putString("id", message.id);
            messageMap.putString("title", message.title);
            messageArray.pushMap(messageMap);
        }
        resultingMap.putArray("messages", messageArray);

        return resultingMap;
    }
}

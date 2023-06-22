package com.selligent;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.selligent.sdk.SMNotificationMessage;

class NotificationMessageBroadcastEventDataParser
{
    public WritableMap wrap(SMNotificationMessage message)
    {
        final WritableMap resultingMap = new WritableNativeMap();

        resultingMap.putString("pushId", message.getId());
        resultingMap.putString("name", message.getNotificationTitle());


        return resultingMap;
    }
}

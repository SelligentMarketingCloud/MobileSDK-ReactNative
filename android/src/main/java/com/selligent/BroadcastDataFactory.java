package com.selligent;

import android.content.Intent;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.selligent.sdk.SMManager;

import java.util.HashMap;
import java.util.Map;

class BroadcastDataFactory {

    private static Map<String, BroadcastEventDataParser> broadcastDataParserMap = new HashMap<String, BroadcastEventDataParser>() {{
        put(SMManager.BROADCAST_EVENT_RECEIVED_IN_APP_MESSAGE, new InAppMessageBroadcastEventDataParser());
        put(SMManager.BROADCAST_EVENT_BUTTON_CLICKED, new ButtonBroadcastEventDataParser());
        put(SMManager.BROADCAST_EVENT_RECEIVED_GCM_TOKEN, new GCMTokenBroadcastEventDataParser());
    }};

    public static WritableMap getBroadcastData(String smBroadcastEventType, Intent intent) {
        final WritableMap broadcastData = new WritableNativeMap();

        final BroadcastEventType broadcastEventType = BroadcastEventType.fromSMBroadcastEventType(smBroadcastEventType);
        String resultingBroadcastEventType = smBroadcastEventType;
        if (broadcastEventType != null) {
            resultingBroadcastEventType = broadcastEventType.getBroadcastEventType();
        }
        broadcastData.putString("broadcastEventType", resultingBroadcastEventType);

        final BroadcastEventDataParser broadcastEventDataParser = broadcastDataParserMap.get(smBroadcastEventType);

        if (broadcastEventDataParser != null) {
            final WritableMap resultingData = broadcastEventDataParser.parse(intent);
            broadcastData.putMap("data", resultingData);
        } else {
            broadcastData.putMap("data", null);
        }

        return broadcastData;
    }
}

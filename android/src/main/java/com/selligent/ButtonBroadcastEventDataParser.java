package com.selligent;

import android.content.Intent;

import com.facebook.react.bridge.WritableMap;
import com.facebook.react.bridge.WritableNativeMap;
import com.selligent.sdk.SMManager;
import com.selligent.sdk.SMNotificationButton;

class ButtonBroadcastEventDataParser implements BroadcastEventDataParser {
    @Override
    public WritableMap parse(Intent intent) {
        final WritableMap resultingMap = new WritableNativeMap();

        SMNotificationButton button = (SMNotificationButton)intent.getSerializableExtra(SMManager.BROADCAST_DATA_BUTTON);
        resultingMap.putString("id", button.id);
        resultingMap.putInt("type", button.type);
        resultingMap.putString("value", button.value);
        resultingMap.putString("label", button.label);
        resultingMap.putInt("action", button.action.getValue());
        if (button.data != null) {
            final WritableMap buttonData = new WritableNativeMap();
            for(String dataKey : button.data.keySet()) {
                buttonData.putString(dataKey, button.data.get(dataKey));
            }

            if (!buttonData.toHashMap().isEmpty()) {
                resultingMap.putMap("data", buttonData);
            } else {
                resultingMap.putMap("data", null);
            }
        }

        return resultingMap;
    }
}

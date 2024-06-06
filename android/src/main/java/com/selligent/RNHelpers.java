package com.selligent;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.WritableArray;
import com.facebook.react.bridge.WritableMap;

import java.util.List;
import java.util.Map;

final class RNHelpers {
    private RNHelpers() { }

    static WritableArray convertListToWritableArray(List<Map<String, Object>> list) {
        WritableArray array = Arguments.createArray();

        if (list.isEmpty()) { return array; }

        for (Map<String, Object> map : list) {
            array.pushMap(RNHelpers.convertMapToWritableMap(map));
        }

        return array;
    }

    static WritableMap convertMapToWritableMap(Map<String, Object> map) {
        WritableMap writableMap = Arguments.createMap();

        if (map.entrySet().isEmpty()) { return writableMap; }

        for (Map.Entry<String, Object> entry : map.entrySet()) {
            Object value = entry.getValue();
            String key = entry.getKey();

            if (value instanceof Map) {
                writableMap.putMap(key, RNHelpers.convertMapToWritableMap((Map<String, Object>) value));
            }
            else if (value instanceof List) {
                writableMap.putArray(key, RNHelpers.convertListToWritableArray((List<Map<String, Object>>) value));
            }
            else if (value instanceof Boolean) {
                writableMap.putBoolean(key, (Boolean) value);
            }
            else if (value instanceof Integer) {
                writableMap.putInt(key, (Integer) value);
            }
            else if (value instanceof Double) {
                writableMap.putDouble(key, (Double) value);
            }
            else if (value instanceof String) {
                writableMap.putString(key, (String) value);
            }
            else if (value instanceof Long) {
                writableMap.putDouble(key, (Long) value);
            }
            else {
                writableMap.putNull(key);
            }
        }

        return writableMap;
    }
}

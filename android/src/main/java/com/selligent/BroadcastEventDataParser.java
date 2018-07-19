package com.selligent;

import android.content.Intent;

import com.facebook.react.bridge.WritableMap;

interface BroadcastEventDataParser {
    WritableMap parse(Intent intent);
}

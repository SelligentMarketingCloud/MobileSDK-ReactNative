package com.selligent;

import com.selligent.sdk.SMCallback;
import com.selligent.sdk.SMEvent;
import com.selligent.sdk.SMEventUserLogin;
import com.selligent.sdk.SMEventUserLogout;
import com.selligent.sdk.SMEventUserRegister;
import com.selligent.sdk.SMEventUserUnregister;


import java.util.Hashtable;

class SMEventFactory {

    public static SMEvent getSMEvent(Event event, SMCallback callback) {
        final EventType type = event.getType();
        final String email = event.getEmail();
        final Hashtable<String, String> data = event.getData();

        switch (type) {
            case UserRegister:
                return new SMEventUserRegister(email, data, callback);
            case UserUnregister:
                return new SMEventUserUnregister(email, data, callback);
            case UserLogin:
                return new SMEventUserLogin(email, data, callback);
            case UserLogout:
                return new SMEventUserLogout(email, data, callback);
            case Custom:
                return new SMEvent(data, callback);
            default:
                throw new IllegalArgumentException("SMManager sendEvent failed: you provided an invalid EventType");
        }
    }

}
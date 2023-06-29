package com.selligent;

import java.util.HashMap;
import java.util.Hashtable;
import java.util.Map;

class Event {

    private EventType type;
    private String email;
    private Hashtable<String, String> data;

    private Event() { }

    public EventType getType() {
        return type;
    }

    public String getEmail() {
        return email;
    }

    public Hashtable<String, String> getData() {
        return data;
    }

    static Event fromHashMap(HashMap<String, Object> eventHashMap) {
        final Integer typeIndex = ((Double) eventHashMap.get("type")).intValue();
        final EventType type = EventType.valueOf(typeIndex);
        String email = null;
        if (eventHashMap.containsKey("email")) {
            email = (String) eventHashMap.get("email");
        }

        Hashtable<String, String> data = null;
        if (eventHashMap.containsKey("data")) {
            final HashMap<String, String> dataHashMap = (HashMap<String, String>) eventHashMap.get("data");
            data = new Hashtable<>();
            for (Map.Entry<String, String> entry : dataHashMap.entrySet()) {
                data.put(entry.getKey(), entry.getValue());
            }
        }

        final Event event = new Event();
        event.type = type;
        event.email = email;
        event.data = data;
        return event;
    }

}
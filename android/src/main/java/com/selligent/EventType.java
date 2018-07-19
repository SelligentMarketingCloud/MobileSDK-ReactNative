package com.selligent;

enum EventType {
    UserRegister(90),
    UserUnregister(91),
    UserLogin(92),
    UserLogout(93),
    Custom(94);

    private Integer index;

    EventType(Integer index) {
        this.index = index;
    }

    public static EventType valueOf(Integer index) {
        EventType result = null;
        for (EventType eventType: values()) {
            if(index.equals(eventType.index)) {
                result = eventType;
            }
        }

        if (result == null) throw new IllegalArgumentException("Invalid eventType");
        return result;
    }
}
package com.selligent;

import com.selligent.sdk.SMManager;

enum BroadcastEventType {
    ButtonClicked("ButtonClicked", SMManager.BROADCAST_EVENT_BUTTON_CLICKED),
    ReceivedInAppMessage("ReceivedInAppMessage", SMManager.BROADCAST_EVENT_RECEIVED_IN_APP_MESSAGE),
    WillDisplayNotification("WillDisplayNotification", SMManager.BROADCAST_EVENT_WILL_DISPLAY_NOTIFICATION),
    WillDismissNotification("WillDismissNotification", SMManager.BROADCAST_EVENT_WILL_DISMISS_NOTIFICATION),
    ReceivedGCMToken("ReceivedGCMToken", SMManager.BROADCAST_EVENT_RECEIVED_GCM_TOKEN);

    private String broadcastEventType;
    private String smBroadcastEventType;

    public String getBroadcastEventType() {
        return broadcastEventType;
    }

    BroadcastEventType(String broadcastEventType, String smBroadcastEventType) {
        this.broadcastEventType = broadcastEventType;
        this.smBroadcastEventType = smBroadcastEventType;
    }

    public static BroadcastEventType fromSMBroadcastEventType(String smEventType) {
        BroadcastEventType result = null;
        for (BroadcastEventType broadcastEventType: values()) {
            if(smEventType.equals(broadcastEventType.smBroadcastEventType)) {
                result = broadcastEventType;
            }
        }

        return result;
    }
}

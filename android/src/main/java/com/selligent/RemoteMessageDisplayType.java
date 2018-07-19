package com.selligent;

import com.selligent.sdk.SMRemoteMessageDisplayType;

enum RemoteMessageDisplayType {
    AUTOMATIC(20, SMRemoteMessageDisplayType.Automatic),
    NONE(21, SMRemoteMessageDisplayType.None),
    NOTIFICATION(22, SMRemoteMessageDisplayType.Notification);

    private Integer index;
    private SMRemoteMessageDisplayType smRemoteMessageDisplayType;

    RemoteMessageDisplayType(Integer index, SMRemoteMessageDisplayType smRemoteMessageDisplayType) {
        this.index = index;
        this.smRemoteMessageDisplayType = smRemoteMessageDisplayType;
    }

    public Integer getIndex() {
        return index;
    }

    public SMRemoteMessageDisplayType getSmRemoteMessageDisplayType() {
        return smRemoteMessageDisplayType;
    }

    public static RemoteMessageDisplayType valueOf(Integer index) {
        RemoteMessageDisplayType result = null;
        for (RemoteMessageDisplayType remoteMessageDisplayType : values()) {
            if(index.equals(remoteMessageDisplayType.index)) {
                result = remoteMessageDisplayType;
            }
        }

        if (result == null) throw new IllegalArgumentException("Invalid remoteMessageDisplayType");
        return result;
    }

    public static RemoteMessageDisplayType valueOf(SMRemoteMessageDisplayType smRemoteMessageDisplayType) {
        RemoteMessageDisplayType result = null;
        for (RemoteMessageDisplayType remoteMessageDisplayType : values()) {
            if(smRemoteMessageDisplayType == remoteMessageDisplayType.smRemoteMessageDisplayType) {
                result = remoteMessageDisplayType;
            }
        }

        if (result == null) throw new IllegalArgumentException("Invalid SMRemoteMessageDisplayType");
        return result;
    }

}

package com.selligent;

import com.selligent.sdk.SMInAppRefreshType;

enum InAppMessageRefreshType {
    NONE(10, SMInAppRefreshType.None),
    MINUTELY(11, SMInAppRefreshType.Minutely),
    HOURLY(12, SMInAppRefreshType.Hourly),
    DAILY(13, SMInAppRefreshType.Daily);

    private Integer index;
    private SMInAppRefreshType smInAppRefreshType;

    InAppMessageRefreshType(Integer index, SMInAppRefreshType smInAppRefreshType) {
        this.index = index;
        this.smInAppRefreshType = smInAppRefreshType;
    }

    public SMInAppRefreshType getSmInAppRefreshType() {
        return smInAppRefreshType;
    }

    public static InAppMessageRefreshType valueOf(Integer index) {
        InAppMessageRefreshType result = null;
        for (InAppMessageRefreshType inAppMessageRefreshType: values()) {
            if(index.equals(inAppMessageRefreshType.index)) {
                result = inAppMessageRefreshType;
            }
        }

        if (result == null) throw new IllegalArgumentException("Invalid inAppMessageRefreshType");
        return result;
    }
}

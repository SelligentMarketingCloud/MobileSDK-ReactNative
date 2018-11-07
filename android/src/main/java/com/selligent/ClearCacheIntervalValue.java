package com.selligent;

import com.selligent.sdk.SMClearCache;

enum ClearCacheIntervalValue {
    AUTO(1, SMClearCache.Auto),
    NONE(2, SMClearCache.None),
    DAY(3, SMClearCache.Day),
    WEEK(4, SMClearCache.Week),
    MONTH(5, SMClearCache.Month),
    QUARTER(6, SMClearCache.Quarter);

    private Integer index;
    private SMClearCache smClearCache;

    ClearCacheIntervalValue(Integer index, SMClearCache smClearCache) {
        this.index = index;
        this.smClearCache = smClearCache;
    }

    public SMClearCache getSmClearCache() {
        return smClearCache;
    }

    public static ClearCacheIntervalValue valueOf(Integer index) {
        ClearCacheIntervalValue result = null;
        for(ClearCacheIntervalValue clearCacheIntervalValue : values()) {
            if(index.equals(clearCacheIntervalValue.index)) {
                result = clearCacheIntervalValue;
            }
        }

        if(result == null) throw new IllegalArgumentException("Invalid clearCacheIntervalValue");
        return result;
    }
}

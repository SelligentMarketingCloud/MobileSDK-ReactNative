typedef enum NotificationButtonType : NSInteger {
    nbtUnknown = 100,
    nbtSimple = 101,
    nbtOpenPhoneCall = 102,
    nbtOpenSms = 103,
    nbtOpenMail = 104,
    nbtOpenBrowser = 105,
    nbtOpenApplication = 106,
    nbtRateApplication = 107,
    nbtCustomActionBroadcastEvent = 108,
    nbtReturn_Text = 109,
    nbtReturn_Photo = 110,
    nbtReturn_TextAndPhoto = 111,
    nbtPassbook = 112
} NotificationButtonType;
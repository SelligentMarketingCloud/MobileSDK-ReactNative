package com.selligent;

import com.selligent.sdk.SMLinkAction;

public enum ButtonAction
{
  unknown(100),
  phone(101),
  sms(102),
  mail(103),
  url(104),
  externalApp(105),
  rateApp(106),
  broadcastEvent(107),
  passbook(111),
  deeplink(112),
  simple(113);

  private final int buttonAction;

  ButtonAction(int action) { this.buttonAction = action; }

  public static ButtonAction valueOf(int x)
  {
    switch(x) {
      case 101:
        return phone;
      case 102:
        return sms;
      case 103:
        return mail;
      case 104:
        return url;
      case 105:
        return externalApp;
      case 106:
        return rateApp;
      case 107:
        return broadcastEvent;
      case 111:
        return passbook;
      case 112:
        return deeplink;
      case 113:
        return simple;
    }
    return unknown;
  }

  public static ButtonAction valueOf(SMLinkAction linkAction)
  {
    switch(linkAction) {
      case phone:
        return phone;
      case sms:
        return sms;
      case mail:
        return mail;
      case url:
        return url;
      case externalApp:
        return externalApp;
      case rateApp:
        return rateApp;
      case broadcastEvent:
        return broadcastEvent;
      case passbook:
        return passbook;
      case deeplink:
        return deeplink;
      case simple:
        return simple;
    }
    return unknown;
  }

  public int getValue()
  {
    return buttonAction;
  }
}

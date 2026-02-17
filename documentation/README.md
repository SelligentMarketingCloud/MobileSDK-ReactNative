# ReactNative – Using the SDK

## Foreword

Copyright

The contents of this manual cover material copyrighted by Selligent. Selligent reserves all intellectual property rights on the manual, which should be treated as confidential information as defined under the agreed upon software licence/lease terms and conditions.

The use and distribution of this manual is strictly limited to authorised users of the Selligent Interactive Marketing Software (hereafter the "Software") and can only be used for the purpose of using the Software under the agreed upon software licence/lease terms and conditions. Upon termination of the right to use the Software, this manual and any copies made must either be returned to Selligent or be destroyed, at the latest two weeks after the right to use the Software has ended.

With the exception of the first sentence of the previous paragraph, no part of this manual may be reprinted or reproduced or distributed or utilised in any form or by any electronic, mechanical or other means, not known or hereafter invented, included photocopying and recording, or in any information storage or retrieval or distribution system, without the prior permission in writing from Selligent.

Selligent will not be responsible or liable for any accidental or inevitable damage that may result from unauthorised access or modifications.

User is aware that this manual may contain errors or inaccuracies and that it may be revised without advance notice. This manual is updated frequently.

Selligent welcomes any recommendations or suggestions regarding the manual, as it helps to continuously improve the quality of our products and manuals.

## Table of Contents

- [ReactNative – Using the SDK](#reactnative--using-the-sdk)
  - [Foreword](#foreword)
  - [Table of Contents](#table-of-contents)
  - [Working with the `selligent.json`](#working-with-the-selligentjson)
  - [Push notifications](#push-notifications)
    - [Rich Push Notifications](#rich-push-notifications)
    - [Deep Linking](#deep-linking)
      - [Background Modes](#background-modes)
      - [Universal Linking - iOS](#universal-linking---ios)
    - [Notification helper methods](#notification-helper-methods)
      - [Disable Selligent Push Notifications](#disable-selligent-push-notifications)
      - [Display last remote notification](#display-last-remote-notification)
      - [Display last remote notification content](#display-last-remote-notification-content)
      - [Retrieve last remote notification](#retrieve-last-remote-notification)
    - [Broadcasts](#broadcasts)
  - [In-App Messages](#in-app-messages)
    - [Display IAM](#display-iam)
    - [Selligent.displayMessage](#selligentdisplaymessage)
      - [IAM Customization - Android](#iam-customization---android)
      - [IAM Customization - iOS](#iam-customization---ios)
    - [IAM Helper methods](#iam-helper-methods)
  - [Events](#events)
  - [Miscellaneous](#miscellaneous)
    - [Get lib version](#get-lib-version)
    - [Get device id](#get-device-id)
    - [Logging](#logging)
    - [GCM Token - Android](#gcm-token---android)
  - [Constants](#constants)
    - [ClearCacheIntervalValue](#clearcacheintervalvalue)
    - [InAppMessageType](#inappmessagetype)
    - [InAppMessageRefreshType](#inappmessagerefreshtype)
    - [RemoteMessagesDisplayType](#remotemessagesdisplaytype)
    - [iOSLogLevel](#iosloglevel)
    - [EventType](#eventtype)
    - [NotificationButtonType](#notificationbuttontype)
    - [BroadcastEventType](#broadcasteventtype)

## Working with the `selligent.json`

The following properties can be used in the `selligent.json` to further configure the behaviour of the native SDKs.

> The values should be relevant to your configuration. There are parameters that can only be used on a specific platform, but can be set and will be ignored in the other platform.

| Property                                    | Type | Description |
| ------------------------------------------- | ------ | ------- |
| url                                         | string | The Selligent webservice url to be used to integrate with your Selligent platform |
| clientId                                    | string | The Selligent client id to be used to integrate with your Selligent platform |
| privateKey                                  | string | The Selligent private key to be used to integrate with your Selligent platform |
| customInAppUi                               | boolean| When this is enabled and a "push + inapp" notification is clicked, the SDK will NOT display the inApp message and instead a `SelligentConstants.BroadcastEventType.DISPLAYING_IN_APP_MESSAGE` event will be sent |
| delayedPushAction                           | boolean| Optin for a specific push action handling (wait for React UI to be ready) when coming from a push message and having the app killed |
| interceptSelligentUniversalLinks            | boolean| (iOS Only) Optin to customly handle the execution of universal links coming from a Push/IAM [more information](#universal-linking---ios) |
| clearCacheIntervalValue                     | [enum](#clearcacheintervalvalue) | How much time the SDK will keep things in cache |  
| inAppMessageRefreshType                     | [enum](#inappmessagerefreshtype) | How often the SDK will check for new inapp messages |
| addInAppMessageFromPushToInAppMessageList   | boolean| Adds inapp messages that are linked to push notifications in the internal inapp message list that can be later [retrieved](#display-iam) |
| remoteMessageDisplayType                    | [enum](#remotemessagesdisplaytype) | The behaviour when receiving a push notification with the app in foreground |
| appGroupId                                  | string |(iOS Only) The appgroup id necessary for the correct communication between the app and the app extensions |
| shouldClearBadge                            | boolean | (iOS Only) Whether or not, clicking a push notification should reset the badge number |
| shouldDisplayRemoteNotification             | boolean | (iOS Only) Whether or not, the SDK should try to display the content linked to a push message (usually, inapp messages) or it will be handled customly
| enableiOSLogging                            | [enum](#iosloglevel) | Log level used since the app launch |
| enableAndroidLogging                        | boolean | (Android Only) Whether or not, the SDK logging will be enabled since the app launch |
| doNotListenToThePush                        | boolean | (Android Only) Whether or not, the SDK will listen for pushs from google |
| doNotFetchTheToken                          | boolean | (Android Only) Whether or not, the SDK will listen for push tokens from google |
| loadCacheAsynchronously                     | boolean | (Android Only) Whether or not, the SDK load the cache asynchronously |
| fullyQualifiedNotificationActivityClassName | string | (Android Only) The activity that will be opened after clicking in any push notification |
| notificationSmallIcon                       | string | (Android Only) Icon name, for the [small icon of push notifications](https://developer.android.com/guide/topics/resources/drawable-resource#BitmapFile) |
| notificationLargeIcon                       | string | (Android Only) Icon name, for the [large icon of push notifications](https://developer.android.com/guide/topics/resources/drawable-resource#BitmapFile) |
| notificationIconColor                       | string | (Android Only) A hex color code to customize the notification icon in push notifications |
| notificationChannelId                       | string | (Android Only) The channel id used by the push notifications received |
| notificationChannelName                     | string | (Android Only) The channel name used by the push notifications received |
| notificationChannelDescription              | string | (Android Only) The channel description used by the push notifications received |

## Push notifications

Follow the [iOS](https://github.com/SelligentMarketingCloud/MobileSDK-iOS/tree/master/Documentation#create-an-apns-key) & [Android](https://github.com/SelligentMarketingCloud/MobileSDK-Android/tree/master/Documentation#creating-an-application) native SDKs guides in order to optin for push notifications in Apple & Google.

**For Android**, if targeting API level 33 and above:

1. Add the following line to AndroidManifest.xml:

    ```xml
    <uses-permission android:name="android.permission.POST_NOTIFICATIONS"/>
    ```

2. Add this native code to request the push permission and let the SDK know when it is accepted, in the activity where you want to:

    ```java
    import com.selligent.RNSelligent;
    
    public class MainActivity extends ReactActivity {
      final int NOTIFICATION_PERMISSION_REQUEST_CODE = 1111;
    
      @Override
      public void onStart()
      {
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.S_V2)
        {
          if (ContextCompat.checkSelfPermission(this, Manifest.permission.POST_NOTIFICATIONS) != PackageManager.PERMISSION_GRANTED)
          {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.POST_NOTIFICATIONS}, NOTIFICATION_PERMISSION_REQUEST_CODE);
          }
        }
        
        super.onStart();
      }
    
      @Override
      public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
      {
          super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    
          if (requestCode == NOTIFICATION_PERMISSION_REQUEST_CODE)
          {
              if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED)
              {
                  RNSelligent.enableNotifications();
              }
          }
      }
    ```

**For iOS**:

1. For push notifications you need to delegate some of the `AppDelegate` methods to the SDK:

    Swift

    ```swift
    // Import the SDK
    import RNSelligentMobileSDK

    // Use UNUserNotificationCenterDelegate
    @UIApplicationMain
    public class AppDelegate: ExpoAppDelegate, UNUserNotificationCenterDelegate {

    // In didFinishLaunchingWithOptions function
    UNUserNotificationCenter.current().delegate = self
    RNSelligent.configureWithLaunchOptions(launchOptions ?? [:])

    // Notification delegates
    override public func application(_ application: UIApplication, didRegisterForRemoteNotificationsWithDeviceToken deviceToken: Data) {
      RNSelligent.didRegisterForRemoteNotifications(withDeviceToken: deviceToken)
      super.application(application, didRegisterForRemoteNotificationsWithDeviceToken: deviceToken)
    }
    
    override public func application(_ application: UIApplication, didFailToRegisterForRemoteNotificationsWithError error: Error) {
      RNSelligent.didFailToRegisterForRemoteNotificationsWithError(error)
      super.application(application, didFailToRegisterForRemoteNotificationsWithError: error)
    }
    
    public func userNotificationCenter(_ center: UNUserNotificationCenter, willPresent notification: UNNotification, withCompletionHandler completionHandler: @escaping(UNNotificationPresentationOptions) -> Void) {
      RNSelligent.willPresentNotification(notification, withCompletionHandler: completionHandler)
    }
    
    public func userNotificationCenter(_ center: UNUserNotificationCenter, didReceive response: UNNotificationResponse, withCompletionHandler completionHandler: @escaping () -> Void) {
      RNSelligent.didReceiveNotificationResponse(response, withCompletionHandler: completionHandler)
    }
    ```

    Objective-C

    ```objc
    // In AppDelegate.h
    #import <React/RCTBridgeDelegate.h>
    #import <UIKit/UIKit.h>

    @import UserNotifications;

    @interface AppDelegate : UIResponder <UIApplicationDelegate, RCTBridgeDelegate, UNUserNotificationCenterDelegate>

    @property (nonatomic, strong) UIWindow *window;

    @end
    ```

    ```objc
    // In AppDelegate.m
    #import "AppDelegate.h"
    #import <React/RCTBundleURLProvider.h>
    #import <React/RCTRootView.h>

    #import <React/RCTAppSetupUtils.h>
    
    @import RNSelligentMobileSDK;
    // OR
    // #import <RNSelligentMobileSDK/RNSelligentMobileSDK-Swift.h>

    @implementation AppDelegate

    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        center.delegate = self;

        // RN Setup Code

        [RNSelligent configureWithLaunchOptions:launchOptions];
      
        return YES;
    }

    - (void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken {
        [RNSelligent didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
    }

    - (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
        [RNSelligent didFailToRegisterForRemoteNotificationsWithError:error];
    }

    - (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler {
        [RNSelligent willPresentNotification:notification withCompletionHandler:completionHandler];
    }

    - (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler {
        [RNSelligent didReceiveNotificationResponse:response withCompletionHandler:completionHandler];
    }

    @end
    ```

2. Follow section [**Create an APNS Key**](https://github.com/SelligentMarketingCloud/MobileSDK-iOS/tree/master/Documentation#apns_key), of the native documentation.

3. Somewhere in your ReactNative app (normally done as soon as possible but can also be done when certain page is reached), you will need to call `Selligent.enableNotifications` to prompt the user for the push notification permission or the `Selligent.registerForProvisionalRemoteNotification` (This option is only available for iOS 12+) if you want to get a provisional permission before asking the user for the normal one.

    ```javascript
    import Selligent from "@selligent-marketing-cloud/selligent-react-native"; // Add Selligent import
    
      if (Platform.OS === "ios") {
        Selligent.registerForProvisionalRemoteNotification(() => {
          // success callback
        })
      }

      Selligent.enableNotifications(
        (response) => {
          // success callback
        },
        (error) => {
          // error callback
        },
        true
      )
    ```

### Rich Push Notifications

**For iOS**, you will need to implement notification extensions and set the `appGroupId` in the `selligent.json` file.
Then, follow the [native iOS SDK documentation](https://github.com/SelligentMarketingCloud/MobileSDK-iOS/edit/master/Documentation/README.md#notification-extensions).

### Deep Linking

Depending on your React version, it might be that deeplinks behind push notifications do not work when the App is killed.
This is because the JS layer is loaded **after** the native SDK executes the deeplink, so the JS event listeners are not there yet. If you want to fix this, follow the below steps (make sure to build for Release when testing this).

1. Add the `delayedPushAction` property in `selligent.json` file and set it to `true`

2. Implement (if not there yet) a linking handler in your ReactNative codebase (i.e <https://facebook.github.io/react-native/docs/linking>)

3. Add a call to `Selligent.executePushAction()` in your main `App.js` file, after adding the ReactNative linking handler (and after calling `Selligent.subscribeToEvents`, if being used)

    ```javascript
    import Selligent from "@selligent-marketing-cloud/selligent-react-native" // Add Selligent import

    const App = () => {
    // Deeplinking handling library (i.e Linking.getInitialURL() & Linking.addEventListener...)
    // useHandleDeepLink()

    /* Tells the Selligent SDK to execute the action associated to the last push clicked, when using `delayedPushAction` feature.
    If you are having problems with deeplinks or 'Push + InApp Message' where the splash screen gets stuck or the push action not visible,
    make sure you control when the splash screen is dismissed (i.e https://docs.expo.dev/versions/latest/sdk/splash-screen/) and call this method afterwards (if the dismiss is async, call this method once the async process is completely finished)
    */
    Selligent.executePushAction()
    ```

#### Background Modes

**For iOS**, (if your app supports Background Modes) it is possible that after the app is launched from the background (location update, background push notification...) if the next action the user performs is executing a deeplink (via safari, push notification click...) the deeplink won't do anything. This is because the communication between the native part and the RN layer is not ready yet when the deeplink is executed from the native side. To workaround this, you can catch when the app is launched from the background and add a bit of delay before the `RCTLinkingManager openUrl` gets executed.

```objective-c
static BOOL launchedFromBackground = false;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  if ([[UIApplication sharedApplication] applicationState] == UIApplicationStateBackground) {
    launchedFromBackground = true;
  }
  
  // Other setup code
  
  return [super application:application didFinishLaunchingWithOptions:launchOptions];
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *)options {
  if (launchedFromBackground) {
    launchedFromBackground = false;
    
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 0.5 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
      [RCTLinkingManager application:application openURL:url options:options];
    });
    
    return [super application:application openURL:url options:options];
  }
  
  return [super application:application openURL:url options:options] || [RCTLinkingManager application:application openURL:url options:options];
}
```

#### Universal Linking - iOS

By default, universal links in a button from a Push/IAM will open the default browser, to avoid this and catch them on the App and apply any logic you want, you will need to add a property `interceptSelligentUniversalLinks` in the `selligent.json` with `true` as value.

You can then subscribe to `SelligentConstants.BroadcastEventType.UNIVERSAL_LINK_EXECUTED` event through the `Selligent.subscribeToEvents` whose execution callback will get triggered when a `deeplink` button type is defined in Selligent (whose URL scheme is `http` or `https`).
The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| data               | object                                                  | Contains more information specific to the type of broadcast event |
| broadcastEventType | [enum](#broadcasteventtype)                             | The type of broadcast event                                       |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

- UNIVERSAL_LINK_EXECUTED:

    | Property | Type   | Description                                |
    | -------- | ------ | ------------------------------------------ |
    | url      | string | The executed URL as a string               |

```javascript
Selligent.subscribeToEvents(
    () => {}, 
    () => {},
    (response) => {
        if (response?.broadcastEventType === SelligentConstants.BroadcastEventType.UNIVERSAL_LINK_EXECUTED) {
            Alert.alert(response.data.url)
        }
    }
)
```

### Notification helper methods

#### Disable Selligent Push Notifications

You can enable or disable Selligent push notifications (not all push notifications for your app) by calling `Selligent.enableNotifications` anytime you want (do note that for iOS, the first call to this method will prompt the user for the push permission).

```javascript
Selligent.enableNotifications(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    true
)
```

#### Display last remote notification

If you want to display the last received push notification you can call `Selligent.displayLastReceivedNotification`.

```javascript
Selligent.displayLastReceivedRemotePushNotification()
```

#### Display last remote notification content

If you want to display the last received push notification content (usually an inapp message) you can call `Selligent.displayLastReceivedRemotePushNotification`. If the last push didn't have any content attached (just a simple push) then nothing will happen.
You can optionally pass a `templateId` parameter, which is a string, to specify which template should be used to personalize the styles of the inapp message (if any).

```javascript
Selligent.displayLastReceivedRemotePushNotification(
    (response) => { // success callback
    },
    "some template id" // If you want to use any specific template
)
```

#### Retrieve last remote notification

You can get the last received push notification banner details by calling `Selligent.getLastRemotePushNotification`.
The response is an object containing the `id`(string) and `title`(string) properties (or `null` if there was nothing to be retrieved).

```javascript
Selligent.getLastRemotePushNotification(
    (response) => { // success callback
    }
)
```

### Broadcasts

You can subscribe to `SelligentConstants.BroadcastEventType.RECEIVED_REMOTE_NOTIFICATION`, `SelligentConstants.BroadcastEventType.WILL_DISPLAY_NOTIFICATION`, `SelligentConstants.BroadcastEventType.WILL_DISMISS_NOTIFICATION` and `SelligentConstants.BroadcastEventType.BUTTON_CLICKED` events through the `Selligent.subscribeToEvents`.
The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| broadcastEventType | [enum](#broadcasteventtype)                             | The type of broadcast event                                       |
| data               | object                                                  | Contains more information specific to the type of broadcast event |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

- RECEIVED_REMOTE_NOTIFICATION:

    | Property | Type   | Description                                |
    | -------- | ------ | ------------------------------------------ |
    | pushId   | string | The id of the remote push notification     |
    | name     | string | The title of the remote push notification  |

- WILL_DISPLAY_NOTIFICATION and WILL_DISMISS_NOTIFICATION: the `data` prop is `null`.

- BUTTON_CLICKED:

    | Property | Type                                                                       | Description                             |
    | -------- | -------------------------------------------------------------------------- | --------------------------------------- |
    | type     | iOS: [enum](#notificationbuttontype)                                       | Tye type of the button (deeplink, url...) |
    | value    | string                                                                     | The value of the button (url value, deeplink value...)  |
    | id       | string                                                                     | The internal id of the button               |
    | label    | string                                                                     | The label of the button       |
    | data     | object                                                                     | Additional data embedded to the button   |

```javascript
Selligent.subscribeToEvents(
    () => {}, 
    () => {},
    (response) => {
      Alert.alert(response.broadcastEventType + ' - ' + JSON.stringify(response.data))
    }
)
```

## In-App Messages

In-App messages are messages retrieved periodically by the SDK.

They are retrieved when the app becomes active (ie. at startup, when going from background to foreground and when the orientation changes) ONLY if the last refresh is older than the value [inAppMessageRefreshType](#inappmessagerefreshtype) in the `selligent.json`.

You can later call the `Selligent.enableInAppMessages` function (if you want) to further optin/optout from the functionality; this function expects an `enabled` parameter that can either be a boolean or an [enum](#inappmessagerefreshtype) value.

> On iOS, if you are using the enum variant when calling the `Selligent.enableInAppMessages` method, it will not change the recurrency of the check for new messages but just enable/disable it. The source of truth for the recurrency is the `selligent.json`.

```javascript
// To enable in-app messages
Selligent.enableInAppMessages(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    true
)
```

### Display IAM

You can subscribe to `SelligentConstants.BroadcastEventType.RECEIVED_IN_APP_MESSAGE` events through the `Selligent.subscribeToEvents`, to know when new messages are received.
The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| broadcastEventType | [enum](#broadcasteventtype)                             | The type of broadcast event                                       |
| data               | object                                                  | Contains more information specific to the type of broadcast event |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

- RECEIVED_IN_APP_MESSAGE

    | Property | Type  | Description      |
    | -------- | ----- | ---------------- |
    | messages | array | List of messages |

    And the detailed overview for items in the `messages` array is:

    | Property | Type   | Description        |
    | -------- | ------ | ------------------ |
    | id       | string | Internal id of the message |
    | title    | string | Title of the message |

```javascript
Selligent.subscribeToEvents(
    () => {}, 
    () => {},
    (response) => {
      if (response?.broadcastEventType === SelligentConstants.BroadcastEventType.RECEIVED_IN_APP_MESSAGE) {
      }
    }
)
```

You can also call `Selligent.getInAppMessages` anywhere in your App to get the list of the currently known IAM.

```javascript
// Get all in app messages
Selligent.getInAppMessages(
    (response) => { // success callback
    }
)
```

The response of the success callback is an array of objects which contain the in app message(s) information:

| Property       | Type                                                                            | Description                                                 |
| -------------- | ------------------------------------------------------------------------------- | ---------------------------------------------------------- |
| id             | string                                                                          | Internal id of the IAM                                 |
| title          | string                                                                          | Title of the IAM                               |
| body           | string                                                                          | Body of the IAM. For message of type `ALERT` it will be the text corresponding to the body of the Alert, for type `HTML` it will be the html code, for type `URL`, `IMAGE` and `PASSBOOK` it will be an URL.                          |
| type           | [enum](#inappmessagetype) | Type of the IAM                                  |
| creationDate   | number                                                                          | Creation date of the IAM in unix time            |
| expirationDate | number                                                                          | Expiration date of the IAM in unix time         |
| receptionDate  | number                                                                          | Reception date of the IAM in unix time             |
| hasBeenSeen    | boolean                                                                         | Indication if the IAM is already seen                    |
| buttons        | array of objects                                                                | Buttons that are linked to the IAM   |

The `buttons` property is an array of button-objects which contain the information of a button linked to the in app message:

| Property | Type   | Description                                | Platform     |
| -------- | ------ | ------------------------------------------ | ------------ |
| id       | string | Id of the button of the in app message     | Both         |
| label    | string | Label of the button of the in app message  | Both         |
| value    | string | Value of the button of the in app message  | Both         |
| type     | number | Type of the button of the in app message   | Both         |

- When the IAM is linked to a push notification, you can set `customInAppUi` to `true` in `selligent.json` and subscribe to `SelligentConstants.BroadcastEventType.DISPLAYING_IN_APP_MESSAGE` events through the `Selligent.subscribeToEvents`, to know when messages are about to be displayed.
You will also need to set `addInAppMessageFromPushToInAppMessageList` to `true` in `selligent.json` to be able to retrieve the full object calling `Selligent.getInAppMessages` and do not forget to use the [IAM Helper methods](#iam-helper-methods) to properly track Open and Click interactions.
For Android, to avoid the SDK directly displaying the IAM if the App is in foreground, do also set `remoteMessageDisplayType` to `22` (NOTIFICATION) in `selligent.json`.
The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| broadcastEventType | [enum](#broadcasteventtype)                             | The type of broadcast event                                       |
| data               | object                                                  | Contains more information specific to the type of broadcast event |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

- DISPLAYING_IN_APP_MESSAGE

    | Property | Type   | Description        |
    | -------- | ------ | ------------------ |
    | id       | string | Internal id of the message |
    | title    | string | Title of the message |

```javascript
Selligent.subscribeToEvents(
    () => {}, 
    () => {},
    (response) => {
      if (response?.broadcastEventType === SelligentConstants.BroadcastEventType.DISPLAYING_IN_APP_MESSAGE) {
      }
    }
)
```

To display any of these messages, you can call `Selligent.displayMessage`:

### Selligent.displayMessage

Display an IAM based on its `id`, which is a string that needs to be passed to the method with the `messageId` parameter.
You can optionally pass a `templateId` parameter, which is a string, to specify which template should be used to personalize the styles of the inapp message (if any), this will only be used on iOS.

```javascript
Selligent.displayMessage(
  (response) => { // success callback
  },
  (error) => { // error callback
  },
  "some message id",
  "some template id" // (iOS only) If you want to use any specific template
)
```

#### IAM Customization - Android

On Android, if you want to customize the IAM styles, you can refer to the [native documentation](https://github.com/SelligentMarketingCloud/MobileSDK-Android/tree/master/Documentation#design-customization).

#### IAM Customization - iOS

On iOS, if you want to customize the IAM styles, you can define the templates, to do so you will need to do it in the native part, in the `UIAppDelegate/didFinishLaunchingWithOptions:` method by calling the `RNSelligent/setInAppMessageStylingTemplates:defaultTemplateId:` method, which expects an array of templates and (optionally) a default template id. If the default template is set, it will be used for all type of in-app messages (when a templateId wasn't provided or couldn't be found) and you will not need to use any specific templateId anywhere around your App.

In the other hand, you can also use the native methods `RNSelligent/willPresentNotification:templateId:withCompletionHandler:` and `RNSelligent/didReceiveNotificationResponse:templateId:withCompletionHandler:` if you want to give different styles to the in app messages that are displayed based on a push message.

> You can refer to the [native documentation](https://github.com/SelligentMarketingCloud/MobileSDK-iOS/tree/master/Documentation#styling-iam) to know more about all possible customizations that are offered.

```objective-c
@import RNSelligentMobileSDK;
@import SelligentMobileSDK;
// OR
// #import <RNSelligentMobileSDK/RNSelligentMobileSDK-Swift.h>
// #import <MapKit/MapKit.h>
// #import <WebKit/WebKit.h>
// #import <SelligentMobileSDK/SMHelperSwift.h>

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
  center.delegate = self;

  // RN Setup code
  
  [RNSelligent configureWithLaunchOptions:launchOptions];
  
  // Example style templates
  SMInAppMessageStyleOptions* styleOptions = [[SMInAppMessageStyleOptions alloc] init];
  styleOptions.presentWithTransition = true;
  styleOptions.transition = kSMViewTransition_VerticalSlide;
  
  InAppMessageStylingTemplate* defaultTemplate = [[InAppMessageStylingTemplate alloc] initWithTemplateId:@"defaultTemplate" styleOptions:styleOptions];
  
  SMInAppMessageStyleOptions* styleOptionsUseCase2 = [[SMInAppMessageStyleOptions alloc] init];
  styleOptionsUseCase2.presentWithTransition = true;
  styleOptionsUseCase2.transition = kSMViewTransition_HorizontalSlide;
  
  InAppMessageStylingTemplate* templateUseCase2 = [[InAppMessageStylingTemplate alloc] initWithTemplateId:@"usecase2" styleOptions:styleOptionsUseCase2];
  
  [RNSelligent setInAppMessageStylingTemplates:@[ defaultTemplate, templateUseCase2 ] defaultTemplateId:@"defaultTemplate"];

  return YES;
}
```

### IAM Helper methods

If you decide to display the IAM on your own (without `Selligent.displayMessage` and `Selligent.displayNotification`), listening for new messages with the `Selligent.subscribeToEvents` and/or getting the full list with `Selligent.getInAppMessages`. You will be able to build your own layout with the object provided from the mentioned functions and then you can use the helper methods described here to still push KPI statistics to the Selligent platform:

- setInAppMessageAsSeen: sets an IAM as seen and sends the corresponding `Opened` event to the Selligent platform

    ```javascript
    Selligent.setInAppMessageAsSeen(
        (response) => { // success callback
        },
        (error) => { // error callback
        },
        "id-of-message"
    )
    ```

- setInAppMessageAsUnseen: sets an IAM as unseen

    ```javascript
    Selligent.setInAppMessageAsUnseen(
        (response) => { // success callback
        },
        (error) => { // error callback
        },
        "id-of-message"
    )
    ```

- setInAppMessageAsDeleted: sets an IAM as deleted

    ```javascript
    Selligent.setInAppMessageAsDeleted(
        (response) => { // success callback
        },
        (error) => { // error callback
        },
        "id-of-message"
    )
    ```

- executeButtonAction: executes the action linked to an IAM button and sends the corresponding `Clicked` event to the Selligent platform

    ```javascript
    Selligent.executeButtonAction(
        (response) => { // success callback
        },
        (error) => { // error callback
        },
        "id-of-button",
        "id-of-message"
    )
    ```

## Events

Sending any set of data to the backend can be done with `Selligent.sendEvent`.
The method accepts an `event` object which requires certain properties, depending on the type of the event:

| Property    | Type                                  | Description      |
| ----------- | ------------------------------------- | ---------------- |
| type        | [enum](#eventtype)                    | The type of event to send |
| email       | string                                | The custom profile identifier (`mail` in our v1 platform) of the user as a String. |
| data        | object                                | Additional data you want to provide to Selligent (you can specify here a key/value pair to use as an alternative lookup for your device identification process) |

For events of type `SelligentConstants.EventType.CUSTOM` the `data` property is mandatory.

```javascript
Selligent.sendEvent(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    {
        type: SelligentConstants.EventType.USER_LOGIN,
        data: { // optional
            description: "this is some extra information concerning this event"
        },
        email: "someone@somedomain.com"
    }
)
Selligent.sendEvent(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    {
        type: SelligentConstants.EventType.CUSTOM,
        data: { // required
            description: "this is some extra information concerning this event"
        }
    }
)
```

## Miscellaneous

### Get lib version

Returns the version of the installed native Selligent SDK (string).

```javascript
Selligent.getVersionLib((versionLib) => {
})
```

### Get device id

Returns the currently known Selligent device Id (string).

```javascript
Selligent.getDeviceId((deviceId) => {
})
```

You can also subscribe to the `SelligentConstants.BroadcastEventType.RECEIVED_DEVICE_ID` event through the `Selligent.subscribeToEvents`, to know when a new device is received.
The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| broadcastEventType | [enum](#broadcasteventtype)                             | The type of broadcast event                                       |
| data               | object                                                  | Contains more information specific to the type of broadcast event |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

- RECEIVED_DEVICE_ID

    | Property | Type   | Description                     |
    | -------- | ------ | ------------------------------- |
    | deviceId | string | The Selligent id of the device  |

### Logging

For iOS, you can use `Selligent.enableiOSLogging` passing the desired logLevel.

```javascript
// to enable logging of info, warning and error statements
Selligent.enableiOSLogging(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    [Selligent.iOSLogLevel.INFO]
)
```

For Android, you can use `Selligent.enableAndroidLogging` passing the enabled flag.

```javascript
Selligent.enableAndroidLogging(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    true
)
```

### GCM Token - Android

To get the current token being used, you can call `Selligent.getGCMToken` which will return it (string).

```javascript
Selligent.getGCMToken(
  (response) => { // success callback
  }
)
```

To set the token manually (if you integrate with GCM directly and do set `doNotFetchTheToken` property to `true`), you can call `Selligent.setFirebaseToken`

```javascript
Selligent.setFirebaseToken(
    (response) => { // success callback
    },
    (error) => { // error callback
    },
    "token value"
)
```

You can also subscribe to the `SelligentConstants.BroadcastEventType.RECEIVED_GCM_TOKEN` event through the `Selligent.subscribeToEvents`, to know when a new token is received.
The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| broadcastEventType | [enum](#broadcasteventtype)                             | The type of broadcast event                                       |
| data               | object                                                  | Contains more information specific to the type of broadcast event |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

- RECEIVED_GCM_TOKEN

    | Property | Type   | Description                     |
    | -------- | ------ | ------------------------------- |
    | token    | string | The token attached to the event |

## Constants

Add the following import to work with the constants:

```javascript
import SelligentConstants from "@selligent-marketing-cloud/selligent-react-native/constants"
```

### ClearCacheIntervalValue

Defines the interval value to clear the cache.

| Name        | Type   | Value | Description                                  |
| ----------- | ------ | ----- | -------------------------------------------- |
| AUTO        | number | 1     | Clear cache automatically (weekly)           |
| NONE        | number | 2     | Don't clear cache                            |
| DAY         | number | 3     | Clear cache daily                            |
| WEEK        | number | 4     | Clear cache weekly                           |
| MONTH       | number | 5     | Clear cache monthly                          |
| QUARTER     | number | 6     | Clear cache quarterly                        |

### InAppMessageType

Defines the type of the IAM.

| Name     | Type   | Value | Description                     |
| -------- | ------ | ----- | ------------------------------- |
| UNKNOWN  | number | -2    | In App message of unknown type  |
| HIDDEN   | number | -1    | In App message of hidden type   |
| ALERT    | number | 0     | In App message of alert type    |
| HTML     | number | 1     | In App message of html type     |
| URL      | number | 2     | In App message of url type      |
| IMAGE    | number | 3     | In App message of image type    |
| MAP      | number | 4     | In App message of map type      |
| PASSBOOK | number | 5     | In App message of passbook type |

### InAppMessageRefreshType

Defines how often the SDK must retrieve the IAM.

| Name           | Type   | Value | Description                        |
| -------------- | ------ | ----- | ---------------------------------- |
| NONE           | number | 10    | Don't fetch the IAM                |
| MINUTE         | number | 11    | Refresh minutely (do not set this for production builds) |
| HOUR           | number | 12    | Refresh hourly                     |
| DAY            | number | 13    | Refresh weekly                     |

### RemoteMessagesDisplayType

Defines if and how remote messages must be displayed when the App is in foreground.

| Name         | Type   | Value | Description                             |
| ------------ | ------ | ----- | --------------------------------------- |
| AUTOMATIC    | number | 20    | Display the IAM (if any) linked to the push, directly    |
| NONE         | number | 21    | Don't display anything        |
| NOTIFICATION | number | 22    | Display the push notification banner (default behaviour) |

### iOSLogLevel

Defines the level of output of logging messages on iOS.

| Name      | Type   | Value | Description       |
| --------- | ------ | ----- | ----------------- |
| NONE      | number | 50    | Output nothing    |
| INFO      | number | 51    | Output info       |
| WARNING   | number | 52    | Output warning    |
| ERROR     | number | 53    | Output error      |
| HTTP_CALL | number | 54    | Output http calls |
| ALL       | number | 56    | Output all        |

### EventType

Defines the type of an event.

| Name            | Type   | Value | Description       |
| --------------- | ------ | ----- | ----------------- |
| USER_REGISTER   | number | 90    | Used to send a register event to the server with the custom email/profile identifier of the user, with the purpose of linking the device to an user and optionally storing some data at Selligent platform side. This event will create a new user in your Selligent database, if none was found (you can use an alternate key/value field to search for the user, in the data object, since by default the `email` one will use the `MAIL` column in your Selligent database). |
| USER_UNREGISTER | number | 91    | Used to send an unregister event to the server with the custom email/profile identifier of the user, with the purpose of keeping track of a REGISTERED flag and optionally storing some data at Selligent platform side (this event is not unlinking the user from the device (automatically), at the moment). |
| USER_LOGIN      | number | 92    | Used to send a login event to the server with the custom email/profile identifier of the user, with the purpose of linking the device to an user and optionally storing some data at Selligent platform side. This event will **NOT** create a new user in your Selligent database, if none found. |
| USER_LOGOUT     | number | 93    | Used to send a logout event to the server with the custom email/profile identifier of the user, with the purpose of keeping track of a LOGGED flag and optionally storing some data at Selligent platform side (this event is not unlinking the user from the device (automatically), at the moment). |
| CUSTOM          | number | 94    | Used to send a custom event to the server, with the purpose of keeping track of storing some data at Selligent platform side. |

### NotificationButtonType

Defines the type of buttons for notifications or inapp messages.

| Name                          | Type   | Value | Description                               |
| ----------------------------- | ------ | ----- | ----------------------------------------- |
| UNKNOWN                       | number | 100   | Unknown button type                       |
| SIMPLE_OPEN_PHONE_CALL        | number | 101   | Opens a phone call dialog                 |
| OPEN_SMS                      | number | 102   | Opens a new sms dialog                    |
| OPEN_MAIL                     | number | 103   | Opens a new email dialog                  |
| OPEN_BROWSER                  | number | 104   | Opens an URL in the default device's browser |
| OPEN_APPLICATION              | number | 105   | Opens an external App                     |
| RATE_APPLICATION              | number | 106   | Opens a 'rate this app' dialog            |
| CUSTOM_ACTION_BROADCAST_EVENT | number | 107   | Sends a custom broadcast to the App       |
| PASSBOOK                      | number | 111   | Opens a passbook URL                      |
| DEEPLINK                      | number | 112   | Executes a deeplink                       |
| SIMPLE                        | number | 113   | Nothing done except forwarding the corresponding `Clicked` event to the Selligent platform |

### BroadcastEventType

Defines the type of a broadcast event.

| Name                             | Type   | Value                      | Description                                           |
| -------------------------------- | ------ | -------------------------- | ----------------------------------------------------- |
| BUTTON_CLICKED                   | string | ButtonClicked              | A button was clicked                                  |
| RECEIVED_IN_APP_MESSAGE          | string | ReceivedInAppMessage       | An IAM has been received                              |
| WILL_DISPLAY_NOTIFICATION        | string | WillDisplayNotification    | A notification will be displayed                      |
| WILL_DISMISS_NOTIFICATION        | string | WillDismissNotification    | A notification will be dismissed                      |
| RECEIVED_DEVICE_ID               | string | ReceivedDeviceId           | A device id has been received                         |
| Android.RECEIVED_GCM_TOKEN       | string | ReceivedGCMToken           | A GCM token has been received (only on Android)       |
| RECEIVED_REMOTE_NOTIFICATION     | string | ReceivedRemoteNotification | A remote notification has been received               |
| iOS.UNIVERSAL_LINK_EXECUTED      | string | UniversalLinkExecuted      | An universal link has been executed                   |
| TRIGGERED_CUSTOM_EVENT           | string | TriggeredCustomEvent       | A custom event has been triggered                     |
| DISPLAYING_IN_APP_MESSAGE        | string | DisplayingInAppMessage     | An IAM is about to be displayed (when `customInAppUi` is set to `true` in `selligent.json`) |

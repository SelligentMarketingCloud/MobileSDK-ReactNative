# Changelog

- __4.3.1__
  - (Android) Add robustness to avoid potential crashes
  
- __4.3.0__
  - (iOS) Fix in-app messages date properties format same as Android (seconds -> milliseconds, no decimals)
  - (Android) Update native SDK 4.7.1 (IAM creation date empty bug)

- __4.2.0__
  - Compatibility checks with Expo SDK 54, ReactNative 0.81.4
  - (iOS) Update native SDK 3.8.7
  - (Android) Update native SDK 4.7.0
  
- __4.1.0__
  - Compatibility checks with Expo SDK 52, ReactNative 0.76.5
  - (Android) Update minSdkVersion to 23

- __4.0.2__
  - Add missing properties `listeningEvents` and `pendingEvents`

- __4.0.1__
  - Fix bug that caused events to not be forwarded to the subscribers when the JS layer loading was slower than the native operation
  
- __4.0.0__
  - BREAKING (Android) Add `delayedPushAction` behaviour to Android. If already being used for iOS, remove any `if (Platform.OS === 'ios')` surrounding `Selligent.executePushAction()` to keep things working on Android
  - (Android) Fix IAM date properties not properly exposing the native value
  - (Android) Fix `selligent.executeButtonAction` not working properly
  - (iOS) Update to native SDK 3.8.5

- __3.9.2__
  - (iOS) Update to native SDK 3.8.3

- __3.9.1__
  - (iOS) Update to native SDK 3.8.2

- __3.9.0__
  - Compatibility checks with Expo SDK 50, ReactNative 0.73.4
  - (iOS) Raise minimum deployment version to iOS 13.4

- __3.8.0__
  - (Android) Remove the aar file and replaced it by a dependency to the same package on Maven Central
  - (Android) Update to native SDK 4.5.0
  - (Android) Update Android Gradle plugin to version 8.2.2

- __3.7.1__
  - (Android) Modify build.gradle so now the `selligent.json` file or even the variant folder(s) (i.e. `dev/selligent.json`) are also read from an unified folder `selligent` apart from the root folder of the project like before (i.e. `root/selligent/dev/selligent.json`).
  - (Android) Fix `selligent.json` loading when using `bundle` tasks instead of `assemble`
  - (Android) Fix problem when no default `selligent.json` existed and gradle:sync task was executed, no exception is thrown anymore and just a warning message is logged
  - (iOS) The full path can be used as as the alternate filename like for example: `[launchOptions setValue:@"selligent/dev/selligent.json" forKey:@"RN_SELLIGENT_JSON"];` (remember to drag&drop the full folder into the xCode project and check the "copy folder references" option)

- __3.7.0__
  - (Android) Refactor of the package
  - Documentation fixes

- __3.6.0__
  - Update to native Android SDK 4.4.1
  - Fix `buttons/type` property value from InApp Messages returned when using `Selligent.getInAppMessages`
  - Add option to intercept and customly display InApp Messages linked to a push notification via `customInAppUi` boolean setting in `selligent.json` + listening to `SelligentConstants.BroadcastEventType.DISPLAYING_IN_APP_MESSAGE` event. Do note that `addInAppMessageFromPushToInAppMessageList` setting in `selligent.json` must also be enabled to properly work with `Selligent.getInAppMessages`, `Selligent.setInAppMessageAsSeen`, `Selligent.setInAppMessageAsUnseen`, `Selligent.setInAppMessageAsDeleted` and `Selligent.executeButtonAction`. For Android, to avoid the SDK directly displaying the IAM if the App is in foreground, do also set `remoteMessageDisplayType` to `22` (NOTIFICATION) in `selligent.json`.

- __3.5.1__
  - (iOS) Update to native SDK 3.8.1
  - `email` property is no longer mandatory for `Selligent.sendEvent`

- __3.5.0__
  - (iOS) Update to native SDK 3.8.0
  - (Android) Update Android Gradle plugin to version 8.1.2
  - (Android) Update targetSdkVersion to 34 (Android 14)
  - (Android) Refactor of the package
  - (Android) Add namespace in AndroidManifest to avoid issues with older RN versions
  - (Android) Remove Huawei documentation
  - (Android) Properly fallback to default selligent.json when flavor file not found
  
- __3.4.1__
  - (iOS) Update to native SDK 3.7.0
  - (Android) Update to native SDK 4.4.0
  - Compatibility checks with Expo SDK 49, ReactNative 0.72.4 and ReactNative new architecture
  - (Android) Update minimum Android Gradle Plugin version to 7.0.0
  - (Android) Fix BuildConfig problem with latest Android Gradle Plugin versions
  - (Android) Update minimum Java JDK version to 17

- __3.3.2__
  - (Android) Fix bug where the native Android SDK would not start correctly if the `selligent.json` would not contain the `inAppMessageRefreshType` property

- __3.3.1__
  - (iOS) Update to native SDK 3.6.1

- __3.3.0__
  - (iOS) Update to native SDK 3.6.0
  - (Android) Update to native SDK 4.3.0
  - (iOS) Raise minimum supported version to iOS 12
  - (iOS) Add compatibility with xCode 15 and iOS 17
  - (iOS) Add Privacy manifest (PrivacyInfo.xcprivacy)
  - (iOS) Add codesigning to provided .xcframework
  - (iOS) Add support for MacCatalyst (minimum macCatalyst version: 13 (macOS 10.15))
  - (iOS) Add support of `enableiOSLogging` property in the `selligent.json` to be able to set the loglevel since the app launches (before the RN layer loads) ([see more](documentation/#working-with-the-selligentjson))
  - (Android) Add support of `enableAndroidLogging` property in the `selligent.json` to be able to set the loglevel since the app launches (before the RN layer loads) ([see more](documentation/#working-with-the-selligentjson))

- __3.2.7__
  - (iOS) Update to native SDK 3.5.1
  - (Android) Update to native SDK 4.2.0
  - (iOS) Add `executePushAction` fix to `Selligent.displayNotification` and `Selligent.displayLastReceivedRemotePushNotification` so they are executed when the react UI is ready (and splash screen dismissed, if any)
  - (iOS) Fix auto enabling of InApp Messages on first run (when configured in `selligent.json`) if not explicitly enabled/disabled by the app
  - `Selligent.areInAppMessagesEnabled` is now available both in iOS and Android
  
- __3.2.6__
  - (iOS) Update to native SDK 3.4.0
  - (Android) Update to native SDK 4.1.0
  - (iOS) Add support for InApp Message style templates to further customize their appearance
  - (iOS) Add support for intercepting universal link executions when coming from a Push/IAM
  - (iOS) Fix issue with deeplink/inapp from a push when the app is killed ([see more](documentation/#deep-linking))
  - (iOS) Rebuild wrapper in swift and provide as .xcframework
  - (Android) Fix how the build variants and flavors were treated to correctly load the `selligent.json` file(s)
  - (Android) Replace broadcasts by observers
  - (Android) `type` property exposed when listening to `SelligentConstants.BroadcastEventType.BUTTON_CLICKED` event is now correctly using `SelligentConstants.NotificationButtonType` enum
  - (Android) add listener for `SelligentConstants.BroadcastEventType.RECEIVED_REMOTE_NOTIFICATION`
  - Unify enableInAppMessages function, now in both platforms both boolean and enum values are accepted
  - Add displayLastReceivedNotification function to forcibly display the last push notification received
  - Add setInAppMessageAsUnseen function to forcibly set an IAM as unseen
  - Add setInAppMessageAsDeleted function to forcibly set an IAM as deleted
  - Remove geolocation dependencies and functions
  - (iOS) Remove iOS < 10 functions
  - Change native iOS & Android SDKs import methodology, from binaries to dependencies (Cocoapods & Maven)
  - Rebuild documentation
  - Fix some minor errors, inconsistencies and unalignments between platforms
  - Deprecate displayNotification in favor of displayMessage
  - Deprecate iOSNotificationButtonType in favor of NotificationButtonType
  
- __3.1.0__
  - Change development dependency versions of `react` `react-native` to `18.2.0` and `^0.71.3`, respectively
  - (Android) Upgrade the `compileSdkVersion` and `targetSdkVersion` to `33` in `android/build.gradle`
  - (Android) Upgrade the Gradle Plugin version to `7.3.1`

- __3.0.0__
  - (Android) Update to native SDK 4.0.1
  - (Android) Remove everything to do with `googleApplicationId`, as this setting was completely removed from Selligent's SDK
  - (Android) use an SMNotificationButton's button action's `getValue()` function to get the action value, in accordance with new API
  - Change development dependency version of `react-native` to `^0.70.6`

- __2.10.0__
  - (iOS) Add section on application lifecycle management split between `AppDelegate` and `SceneDelegate` with regards to Selligent push notification handling on iOS 15+ in README
  - (Android) Update to native SDK 3.10.1
  - (iOS) Update to native SDK 2.7.7
  - Change development dependency versions of  `react` and `react-native` to `18.1.0` and  `^0.70.0`, respectively
  - (Android) Upgrade the `compileSdkVersion` and `targetSdkVersion` to `32` in `android/build.gradle`
  - (Android) Upgrade the Gradle Plugin version to `7.2.2`
  - (Android) Upgrade the `om.google.code.gson:gson` and `androidx.work:work-runtime` dependencies to `2.8.9` and `2.7.1` respectively in `android/build.gradle`

- __2.9.0__
  - (Android) Add possibility to set the app's notification channel's ID, name and description via `notificationChannelId`, `notificationChannelName`, and `notificationChannelDescription` settings keys in `selligent.json`.
  - (Android) Update to native SDK 3.9.0
  - (iOS) Update native SDK 2.7.4

- __2.8.0__
  - (Android) Re-add plotProjects dependency in `android/build.gradle`
  - (Android) Re-add geolocation native module functions (`enableGeolocation`, `isGeoLocationEnabled`)
  - (iOS) Re-add geofencing header files in `ios/include` and module files in `ios/`
  - Re-add plotProjects and geolocation documentation to README
  - (Android) Update to native SDK 3.8.1
  - (Android) Swap the deprecated maven plugin and its archiving capabilities for the maven-publish plugin in `android/build.gradle`
  - (iOS) Update to native SDK 2.7.2

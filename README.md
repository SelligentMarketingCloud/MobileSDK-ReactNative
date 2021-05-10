# Selligent React Native Module (selligent-react-native)

This module provides an API for the usage of the Selligent SDK in React Native.

## Supported platforms

* Android
* iOS

> _**Important:** Since version 2.4.0 of this module we require your app to use the Android Gradle Plugin version 4.1.0 or higher in order to build on Android. This is the default Android Gradle Plugin version since React Native version 0.64.0 but can be manually increased in older versions of React Native._

## ToC

* [Installation](#installation)
  * [Android Specific Installation](#android-specific-installation)
  * [iOS Specific Installation](#ios-specific-installation)
* [Using the API](#using-the-api)
* [API Reference](#api-reference)
  * [Methods](#methods)
  * [Android Only/Specific Methods](#android-onlyspecific-methods)
  * [iOS Only/Specific Methods](#ios-onlyspecific-methods)
  * [Constants](#constants)

## Installation

1. Install the module

   ```shell
   npm install @selligent-marketing-cloud/selligent-react-native --save
   ```

2. Create a `selligent.json` file (name is case sensitive) in the root of the React Native project with the following content:

   ```json
   {
       "url": "someMobilePushUrl",
       "clientId": "someClientId",
       "privateKey": "somePrivateKey",
       "fullyQualifiedNotificationActivityClassName": "com.some.project.MainActivity"
   }
   ```

   Note: The values should be relevant to your configuration. There are parameters that can only be used on a specific platform, but can be passed to either and will be ignored when possible.

**Detailed overview:**

| Property                                    | Type                                                                                          | Required | Platform     |
| ------------------------------------------- | --------------------------------------------------------------------------------------------- | -------- | ------------ |
| url                                         | string                                                                                        | Yes      | Both         |
| clientId                                    | string                                                                                        | Yes      | Both         |
| privateKey                                  | string                                                                                        | Yes      | Both         |
| clearCacheIntervalValue                     | enum [Selligent.ClearCacheIntervalValue](#selligentclearcacheintervalvalue)                   | No       | Both         |
| configureLocationServices                   | boolean                                                                                       | No       | Both         |
| inAppMessageRefreshType                     | enum [Selligent.InAppMessageRefreshType](#selligentinappmessagerefreshtype)                   | No       | Both         |
| appGroupId                                  | string                                                                                        | No       | iOS Only     |
| shouldClearBadge                            | boolean                                                                                       | No       | iOS Only     |
| shouldDisplayRemoteNotification             | boolean                                                                                       | No       | iOS Only     |
| shouldPerformBackgroundFetch                | boolean                                                                                       | No       | iOS Only     |
| doNotListenToThePush                        | boolean                                                                                       | No       | Android Only |
| doNotFetchTheToken                          | boolean                                                                                       | No       | Android Only |
| loadCacheAsynchronously                     | boolean                                                                                       | No       | Android Only |
| fullyQualifiedNotificationActivityClassName | string                                                                                        | No       | Android Only |
| remoteMessageDisplayType                    | enum [Selligent.AndroidRemoteMessagesDisplayType](#selligentAndroidRemoteMessagesDisplayType) | No       | Android Only |

   ​

### Android Specific Installation

<details>
<summary>Without autolinking (RN 0.59 and below)</summary>

1. Create a Google application following the section **Creating a Google application** of the **Android - Using the SDK** pdf, and place the `google-services.json` file in the `./android/app` folder.

2. Add the following lines at the end of the `android/settings.gradle` file:

   ```groovy
   include ':selligent-react-native'
   project(':selligent-react-native').projectDir = new File(rootProject.projectDir, '../node_modules/@selligent-marketing-cloud/selligent-react-native/android')
   ```

3. Add the following in the `android/build.gradle` file:

   ```groovy
   buildscript {
       ...
       dependencies {
           ...
           // Add the following:
           classpath 'com.google.gms:google-services:4.3.3'
       }
   }

   allprojects {
       repositories {
           ...
           // Add the following:
           flatDir {
               dirs "$rootDir/../node_modules/@selligent-marketing-cloud/selligent-react-native/android/libs"
           }

           // Add the following:
           maven {
               url 'https://maven-repo.plotprojects.com'
           }
       }
   }
   ```

4. Add the following in the `android/app/build.gradle` file:

   ```groovy
   dependencies {
       // Add the following:
       compile project(path: ':selligent-react-native')
       ...
   }
   ...
   // Add the following:
   apply plugin: 'com.google.gms.google-services'
   ```

5. Add the following in the `android/app/src/../MainApplication.java` file:

   ```java
   // Add the following import statements:
   import com.selligent.RNSelligent;
   import com.selligent.RNSelligentPackage;
   ...

   public class MainApplication extends Application implements ReactApplication {

       private final ReactNativeHost mReactNativeHost = new ReactNativeHost(this) {
            ...
            @Override
            protected List<ReactPackage> getPackages() {
          
                List<ReactPackage> packages = new PackageList(this).getPackages();
                // Add the following:
                packages.add(new RNSelligentPackage());
                return packages;
            }
            ...
       };
       ...
       @Override
       public void onCreate() {
           super.onCreate();
           ...
           // Add the following:
           RNSelligent.configure(this);
       }
   }
   ```

</details>
<br>
<details open>
<summary>With autolinking (RN 0.60 and above)</summary>

1. Create a Google application following the section **Creating a Google application** of the **Android - Using the SDK** pdf, and place the `google-services.json` file in the `./android/app` folder.

2. Add the following lines at the end of the `android/settings.gradle` file:

   ```groovy
   include ':selligent-react-native'
   project(':selligent-react-native').projectDir = new File(rootProject.projectDir, '../node_modules/@selligent-marketing-cloud/selligent-react-native/android')
   ```

3. Add the following in the `android/build.gradle` file:

   ```groovy
   buildscript {
       ...
       dependencies {
           ...
           // Add the following:
           classpath 'com.google.gms:google-services:4.3.3'
       }
   }

   allprojects {
       repositories {
           ...
           // Add the following:
           flatDir {
               dirs "$rootDir/../node_modules/@selligent-marketing-cloud/selligent-react-native/android/libs"
           }

           // Add the following:
           maven {
               url 'https://maven-repo.plotprojects.com'
           }
       }
   }
   ```

4. Add the following in the `android/app/build.gradle` file:

   ```groovy
   // Add the following:
   apply plugin: 'com.google.gms.google-services'
   ```

5. Add the following in the `android/app/src/../MainApplication.java` file:

   ```java
   // Add the following import statements:
   import com.selligent.RNSelligent;
   import com.selligent.RNSelligentPackage;
   ...

   public class MainApplication extends Application implements ReactApplication {
       ...
       @Override
       public void onCreate() {
           super.onCreate();
           ...
           // Add the following:
           RNSelligent.configure(this);
       }
   }
   ```

</details>


#### Change default push notification icons

Add the following properties to the `selligent.json` file:

```
    "notificationSmallIcon": "ic_notification",
    "notificationLargeIcon": "ic_notification"
```

> _Note: only parse the name of the icon, without the path. The icon should reside in the res/drawable folder of the Android project, as explained in [Android's official guide](https://developer.android.com/guide/topics/resources/drawable-resource#BitmapFile)._


### iOS Specific installation

<details>
<summary>Without autolinking (RN 0.59 and below)</summary>

1. Copy the `node_modules/@selligent-marketing-cloud/selligent-react-native/ios/SelligentReactNative.xcodeproj` file to the **Xcode project**. Drop it under the `Libraries` Folder. This will link the module to the iOS project. (See the image in the next step)

2. Drag and drop the `selligent.json` you created from the root folder to the Xcode project inside the `Copy Bundle Resources` in `Build phases` of your target:

   > _Note: do not check the "copy if needed" option to make sure you only have to manage one selligent.json file_

   ![Add 'SelligentReactNative.xcodeproj' and 'selligent.json' file to 'Copy Bundle Resources'](/documentation/add_json_file.png)

3. Drag and drop the `libRNSelligent.a` to your `Linked Frameworks and Libraries`:

   ![Add 'libRNSelligent.a' file to your 'Linked Frameworks and Libraries'](/documentation/add_lib_file.png)

4. Add Selligent to `Header Search Paths` in `Build Settings` of your target:

    ```
    $(SRCROOT)/../node_modules/@selligent-marketing-cloud/selligent-react-native/ios/
    ```



4. Add Selligent to `Header Search Paths` in `Build Settings` of your target:

    ```
    $(SRCROOT)/../node_modules/@selligent-marketing-cloud/selligent-react-native/ios/
    ```

5. Create a `Podfile` (if there isn't one already) in the `/ios` folder and add the following:

   ```ruby
   target 'REPLACEWITHYOURTARGETNAME'
   pod 'PlotPlugin', '3.3.2'
   ```

6. Execute `pod install` in the `/ios` folder

7. From now on open the `.xcworkspace` file to make changes in Xcode

8. Bootstrap the SDK in the `application:didFinishLaunchingWithOptions:` of the `AppDelegate.m`

   ```objective-c
   #import <RNSelligent.h>
   [RNSelligent configureWithLaunchOptions:launchOptions];
   ```

</details>
<br>
<details open>
<summary>With autolinking (RN 0.60 and above)</summary>

1. Drag and drop the `selligent.json` you created from the root folder to the Xcode project inside the `Copy Bundle Resources` in `Build phases` of your target:

   > _Note: do not check the "copy if needed" option to make sure you only have to manage one selligent.json file_

2. Execute `pod install` in the `/ios` folder

3. Bootstrap the SDK in the `application:didFinishLaunchingWithOptions:` of the `AppDelegate.m`

   ```objective-c
   #import <RNSelligent.h>
   [RNSelligent configureWithLaunchOptions:launchOptions];
   ```

</details>



#### Push notifications

1. For push notifications you need to delegate some of the `AppDelegate.m` methods to the SDK:

   ````objective-c
   #import "AppDelegate.h"
   #import <React/RCTBundleURLProvider.h>
   #import <React/RCTRootView.h>
   #import <RNSelligent.h>

   #if defined(__IPHONE_10_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0
   @import UserNotifications;
   @interface AppDelegate () <UNUserNotificationCenterDelegate>
   @end
   #endif

   @implementation AppDelegate

   - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
     [self _prepareForPushNotifications];
     [RNSelligent configureWithLaunchOptions:launchOptions];
     // ...
     //react native setup code
     // ...
     return YES;
   }

   - (void)_prepareForPushNotifications {
   #if defined(__IPHONE_10_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0
     UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
     center.delegate = self;
   #endif
   }

   - (void)application:(UIApplication *)application performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
     [RNSelligent performIAMFetchWithCompletionHandler:completionHandler];
   }

   - (void)application:(UIApplication*)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken {
     [RNSelligent didRegisterForRemoteNotificationsWithDeviceToken:deviceToken];
   }

   - (void)application:(UIApplication*)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings {
     [RNSelligent didRegisterUserNotificationSettings:notificationSettings];
   }

   - (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
     [RNSelligent didFailToRegisterForRemoteNotificationsWithError:error];
   }

   - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
     [RNSelligent didReceiveRemoteNotification:userInfo];
   }

   #if defined(__IPHONE_10_0) && __IPHONE_OS_VERSION_MAX_ALLOWED >= __IPHONE_10_0
   - (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions options))completionHandler {
     [RNSelligent willPresentNotification:notification withCompletionHandler:completionHandler];
   }

   - (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void(^)(void))completionHandler {
     [RNSelligent didReceiveNotificationResponse:response withCompletionHandler:completionHandler];
   }
   #endif

   @end
   ````

2. Follow section 4 **Configure the APNS (Apple Push Notification Service)**, of the **IOS - Using the SDK** pdf.  

3. If you want rich push notifications, follow section 6.9 **Notification Extensions** as well.  
   Make sure you add your `appGroupId` to the `selligent.json`.
   > **IMPORTANT!** make sure your `appGroupId` has the following structure or it will not work: `group.{MAIN_APP_BUNDLE_ID}`

#### Geolocation

For geolocation services, follow section 6.5 **Geolocation**, of the **IOS - Using the SDK** pdf. You also need to configure several permissions described in 5.3.3 **Permission for geo location**.

#### Deeplinking
You can catch the deeplinks 2 ways:

1. Native in AppDelegate.m, add the following (example code that logs the URL)
```
-(BOOL)application:(UIApplication*) application openURL:(NSURL*) url sourceApplication:(NSString*) sourceApplication annotation:(id) annotation
{
  NSLog(@"%@", [url absoluteString]);
  return YES;
}
```

2. In your React Native codebase, https://facebook.github.io/react-native/docs/linking

## Using the API

1. In the `App.js` file:

   1. Add the `Button` import statement:

      ```javascript
      import {Platform, StyleSheet, Text, View, Button} from 'react-native'; // Add Button import
      ```

   2. Add the `Selligent` import statement:

      ```javascript
      import Selligent from '@selligent-marketing-cloud/selligent-react-native' // Add Selligent import
      ```

   3. Add a function to call the `Selligent.getVersionLib` function:

      ```javascript
      export default class App extends Component<Props> {
          ...
          // Add example function
          _getVersionLib() {
              Selligent.getVersionLib((versionLib) => {
                  alert(versionLib);
              })
          }
          ...
      }
      ```

   4. Add a `Button` component in the `render()` function calling the function of the previous step:

      ```javascript
      render() {
          return (
              <View style={styles.container}>
                  ...
                  // Add button
                  <Button
                    onPress={this._getVersionLib}
                    title='getVersionLib'
                  />
              </View>
          );
      }
      ```

   5. Your `App.js` file should look something like this:

      ```javascript
      import React, {Component} from 'react';
      import {Platform, StyleSheet, Text, View, Button} from 'react-native'; // Add Button import
      import Selligent from '@selligent-marketing-cloud/selligent-react-native' // Add Selligent import

      const instructions = Platform.select({
          ios: 'Press Cmd+R to reload,\n' + 'Cmd+D or shake for dev menu',
          android:
              'Double tap R on your keyboard to reload,\n' +
              'Shake or press menu button for dev menu',
      });

      type Props = {};
      export default class App extends Component<Props> {

          // Add example function
          _getVersionLib() {
              Selligent.getVersionLib((versionLib) => {
                  alert(versionLib);
              })
          }

          render() {
              return (
                  <View style={styles.container}>
                      <Text style={styles.welcome}>Welcome to React Native!</Text>
                      <Text style={styles.instructions}>To get started, edit App.js</Text>
                      <Text style={styles.instructions}>{instructions}</Text>
                      // Add button
                      <Button
                        onPress={this._getVersionLib}
                        title='getVersionLib'
                      />
                  </View>
              );
          }
      }

      const styles = StyleSheet.create({
          container: {
              flex: 1,
              justifyContent: 'center',
              alignItems: 'center',
              backgroundColor: '#F5FCFF',
          },
          welcome: {
              fontSize: 20,
              textAlign: 'center',
              margin: 10,
          },
          instructions: {
              textAlign: 'center',
              color: '#333333',
              marginBottom: 5,
          },
      });
      ```

## API Reference

* [Methods](#methods)
  * [Selligent.getVersionLib(successCallback)](#selligentgetversionlibsuccesscallback)
    * [getVersionLib example](#getversionlib-example)
  * [Selligent.enableGeolocation(successCallback, errorCallback, enabled)](#selligentenablegeolocationsuccesscallback-errorcallback-enabled)
    * [enableGeolocation example](#enablegeolocation-example)
  * [Selligent.isGeolocationEnabled(successCallback)](#selligentisgeolocationenabledsuccesscallback)
    * [isGeolocationEnabled example](#isgeolocationenabled-example)
  * [Selligent.enableNotifications(successCallback, errorCallback, enabled)](#selligentenablenotificationssuccesscallback-errorcallback-enabled)
    * [enableNotifications example](#enablenotifications-example)
  * [Selligent.displayLastReceivedRemotePushNotification(successCallback)](#selligentdisplaylastreceivedremotepushnotificationsuccesscallback)
    * [displayLastReceivedRemotePushNotification example](#displaylastreceivedremotepushnotification-example)
  * [Selligent.getLastRemotePushNotification(successCallback)](#selligentgetlastremotepushnotificationsuccesscallback)
    * [getLastRemotePushNotification Example](#getlastremotepushnotification-example)
  * [Selligent.enableInAppMessages(successCallback, errorCallback, enabled)](#selligentenableinappmessagessuccesscallback-errorcallback-enabled)
    * [enableInAppMessages example](#enableinappmessages-example)
  * [Selligent.getInAppMessages(successCallback)](#selligentgetinappmessagessuccesscallback)
    * [getInAppMessages example](#getinappmessages-example)
  * [Selligent.setInAppMessageAsSeen(successCallback, errorCallback, messageId)](#selligentsetinappmessageasseensuccesscallback-errorcallback-messageid)
    * [setInAppMessageAsSeen example](#setinappmessageasseen-example)
  * [Selligent.executeButtonAction(successCallback, errorCallback, buttonId, messageId)](#selligentexecutebuttonactionsuccesscallback-errorcallback-buttonid-messageid)
    * [executeButtonAction example](#executeButtonAction-example)
  * [Selligent.sendEvent(successCallback, errorCallback, event)](#selligentsendeventsuccesscallback-errorcallback-event)
    * [sendEvent example](#sendevent-example)
  * [Selligent.subscribeToEvents(successCallback, errorCallback, eventCallback)](#selligentsubscribetoeventssuccesscallback-errorcallback-eventcallback)
    * [subscribeToEvents example](#subscribetoevents-example)

* [Android Only/Specific Methods](#android-onlyspecific-methods)
  * [Selligent.subscribeToEvent(eventCallback, eventName)](#selligentsubscribetoeventeventcallback-eventname)
    * [subscribeToEvent example](#subscribetoevent-example)
  * [Selligent.areInAppMessagesEnabled(successCallback)](#selligentareinappmessagesenabledsuccesscallback)
    * [areInAppMessagesEnabled example](#areinappmessagesenabled-example)
  * [Selligent.enableAndroidLogging(successCallback, errorCallback, enabled)](#selligentenableandroidloggingsuccesscallback-errorcallback-enabled)
    * [enableAndroidLogging example](#enableandroidlogging-example)
  * [Selligent.displayMessage(successCallback, errorCallback, messageId)](#selligentdisplaymessagesuccesscallback-errorcallback-messageid)
    * [displayMessage example](#displaymessage-example)
  * [Selligent.areNotificationsEnabled(successCallback)](#selligentarenotificationsenabledsuccesscallback)
    * [areNotificationsEnabled example](#arenotificationsenabled-example)
  * [Selligent.setNotificationSmallIcon(successCallback, errorCallback, iconName)](#selligentsetnotificationsmalliconsuccesscallback-errorcallback-iconname)
    * [setNotificationSmallIcon example](#setnotificationsmallicon-example)
  * [Selligent.setNotificationLargeIcon(successCallback, errorCallback, iconName)](#selligentsetnotificationlargeiconsuccesscallback-errorcallback-iconname)
    * [setNotificationLargeIcon example](#setnotificationlargeicon-example)
  * [Selligent.getGCMToken(successCallback)](#selligentgetgcmtokensuccesscallback)
    * [getGCMToken Example](#getgcmtoken-example)
  * [Selligent.getRemoteMessagesDisplayType(successCallback, errorCallback)](#selligentgetremotemessagesdisplaytypesuccesscallback-errorcallback)
    * [getRemoteMessagesDisplayType Example](#getremotemessagesdisplaytype-example)
  * [Selligent.setFirebaseToken(successCallback, errorCallback, token)](#selligentsetfirebasetokensuccesscallback--errorcallback--token)
    * [setFirebaseToken Example](#setFirebaseToken-example)

* [iOS Only/Specific Methods](#ios-onlyspecific-methods)
  * [Selligent.enableiOSLogging(successCallback, errorCallback, logLevels)](#selligentenableiosloggingsuccesscallback-errorcallback-loglevels)
    * [enableiOSLogging example](#enableioslogging-example)
  * [Selligent.currentAuthorisationStatus(successCallback)](#selligentcurrentauthorisationstatussuccesscallback)
    * [currentAuthorisationStatus Example](#currentauthorisationstatus-example)
  * [Selligent.requestLocationAuthorisation(successCallback, errorCallback, iOSLocationAuthorisationType)](#selligentrequestlocationauthorisationsuccesscallback-errorcallback-ioslocationauthorisationtype)
    * [requestLocationAuthorisation Example](#requestlocationauthorisation-example)
  * [Selligent.displayNotification(successCallback, errorCallback, notificationId)](#selligentdisplaynotificationsuccesscallback-errorcallback-notificationid)
    * [displayNotification Example](#displaynotification-example)
  * [Selligent.registerRemoteNotificationFetchCompletionHandler(successCallback, errorCallback)](#selligentregisterremotenotificationfetchcompletionhandlersuccesscallback-errorcallback)
    * [registerRemoteNotificationFetchCompletionHandler example](#registerremotenotificationfetchcompletionhandler-example)
  * [Selligent.forceRemoteNotificationBackgroundFetchResult(successCallback, errorCallback, iOSBackgroundFetchResult)](#selligentforceremotenotificationbackgroundfetchresultsuccesscallback-errorcallback-iosbackgroundfetchresult)
    * [forceRemoteNotificationBackgroundFetchResult example](#forceremotenotificationbackgroundfetchresult-example)

* [Constants](#constants)
  * [SelligentConstants.ClearCacheIntervalValue](#selligentconstantsclearcacheintervalvalue)
  * [SelligentConstants.InAppMessageRefreshType](#selligentconstantsinappmessagerefreshtype)
  * [SelligentConstants.AndroidRemoteMessagesDisplayType](#selligentconstantsandroidremotemessagesdisplaytype)
  * [SelligentConstants.iOSLogLevel](#selligentconstantsiosloglevel)
  * [SelligentConstants.iOSBackgroundFetchResult](#selligentconstantsiosbackgroundfetchresult)
  * [SelligentConstants.iOSLocationAuthorisationStatus](#selligentconstantsioslocationauthorisationstatus)
  * [SelligentConstants.iOSLocationAuthorisationType](#selligentconstantsioslocationauthorisationtype)
  * [SelligentConstants.EventType](#selligentconstantseventtype)
  * [SelligentConstants.iOSNotificationButtonType](#selligentconstantsiosnotificationbuttontype)
  * [SelligentConstants.BroadcastEventType](#selligentconstantsbroadcasteventtype)

### Methods

#### Selligent.getVersionLib(successCallback)

Returns the version of the installed Selligent SDK.

The response of the success callback is a string containing the version of the SDK.

##### getVersionLib example

```javascript
Selligent.getVersionLib(
    (versionLib) => { // success callback
        alert(versionLib);
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>


#### Selligent.enableGeolocation(successCallback, errorCallback, enabled)

Enable or disable geolocation services.

The `enabled` parameter is a required boolean to enable or disable geolocation services.

##### enableGeolocation example

```javascript
Selligent.enableGeolocation(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    true
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.isGeolocationEnabled(successCallback)

Check if geolocation services are enabled or disabled.

The response of the success callback is a boolean stating geolocation services are enabled or disabled.

##### isGeolocationEnabled example

```javascript
Selligent.isGeolocationEnabled(
    (response) => { // success callback
        ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.enableNotifications(successCallback, errorCallback, enabled)

Enable or disable the usage of notifications.

The `enabled` parameter is a required boolean to enable or disable notifications.

##### enableNotifications example

```javascript
Selligent.enableNotifications(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    true
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.displayLastReceivedRemotePushNotification(successCallback)

Display the last received remote notification.

##### displayLastReceivedRemotePushNotification example

```javascript
Selligent.displayLastReceivedRemotePushNotification(
    (response) => { // success callback
        ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.getLastRemotePushNotification(successCallback)

Get the id and the title of the last received remote push notification.

The response of the success callback is an object containing the information about the last received remote push notification, or `null` if there is no last received remote push notification.

**Detailed overview:**

| Property | Type   | Description                                |
| -------- | ------ | ------------------------------------------ |
| id       | string | Id of the last remote push notification    |
| title    | string | Title of the last remote push notification |

##### getLastRemotePushNotification Example

```javascript
Selligent.getLastRemotePushNotification(
    (response) => { // success callback
        ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.enableInAppMessages(successCallback, errorCallback, enabled)

This method enables or disables the management of in-app messages.

The `enabled` parameter can be a boolean or a constant of the [InAppMessageRefreshType](#selligentinappmessagerefreshtype) enum.

_Note: on iOS the `enabled` parameter must be a boolean._

In the case of a boolean set to `false`, the in-app messages will be disabled.
When the passed `enabled` parameter is an [InAppMessageRefreshType](#selligentinappmessagerefreshtype) constant, the in-app messages will be enabled and the refresh frequency will be set to the provided value.
The method will return an error if the parsed boolean is set to `true`, as to enable the in-app messages a refresh type is expected.

##### enableInAppMessages example

```javascript
// to enable in-app messages
Selligent.enableInAppMessages(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    Selligent.InAppMessageRefreshType.DAY
);
// to disable in-app messages
Selligent.enableInAppMessages(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    false
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.getInAppMessages(successCallback)

This method returns all the in app messages send to you.

The response of the success callback is an array of objects which contain the in app message(s) information.

**Detailed overview:**

| Property           | Type                                                    | Description                                                       | Platform     |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- | ------------ |
| id                 | string                                                  | Id of the in app message                                          | Both         |
| title              | string                                                  | Title of the in app message                                       | Both         |
| body               | string                                                  | Body of the in app message                                        | Both         |
| creationDate       | number                                                  | Creation date of the in app message in unix time                  | Both         |
| expirationDate     | number                                                  | Expiration date of the in app message in unix time                | Both         |
| receptionDate      | number                                                  | Reception date of the in app message in unix time                 | Both         |
| hasBeenSeen        | boolean                                                 | Indication if the in app message is seen                          | Both         | 
| buttons            | array of objects                                        | Contains the buttons that are linked to the in app message        | Both         |

<br />

The `buttons` property is an array of button-objects which contain the information of a button linked to the in app message:

<br />

| Property           | Type                                                    | Description                                                       | Platform     |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- | ------------ |
| id                 | string                                                  | Id of the button of the in app message                            | Both         |
| label              | string                                                  | Label of the button of the in app message                         | Both         |
| value              | string                                                  | Value of the button of the in app message                         | Both         |
| type               | number                                                  | Type of the button of the in app message                          | Both         |
| action             | number                                                  | Action of the button of the in app message                        | Android only |

<br />

##### getInAppMessages example

```javascript
// Get all in app messages
Selligent.getInAppMessages(
    (response) => { // success callback
      ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.setInAppMessageAsSeen(successCallback, errorCallback, messageId)

Possibility to mark an in app message as seen.

This method requires beside the callbacks another property to indicate the current in app message. To accomplish this behavior,&nbsp; `messageId` is required.

##### setInAppMessageAsSeen example

```javascript
Selligent.setInAppMessageAsSeen(
    (response) => { // success callback
      ...
    },
    (error) => { // error callback
      ...
    },
    "id-of-message"
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.executeButtonAction(successCallback, errorCallback, buttonId, messageId)

Execute the action linked to the button.

This method requires beside the callbacks another property to execute the action behind the button of the in app message. To accomplish this behavior,&nbsp; `buttonId` and `messageId` are required.

##### executeButtonAction example

```javascript
Selligent.executeButtonAction(
    (response) => { // success callback
      ...
    },
    (error) => { // error callback
      ...
    },
    "id-of-button",
    "id-of-message"
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.sendEvent(successCallback, errorCallback, event)

This method provides the functionality to send a specific or custom event.

The method accepts an `event` object which requires certain properties, depending on the type of the event.

**Detailed overview:**

| Property    | Type                                  | Required                                          | Platform | Default value |
| ----------- | ------------------------------------- | ------------------------------------------------- | -------- | ------------- |
| type        | enum [EventType](#selligenteventtype) | Yes                                               | Both     | N/A           |
| email       | string                                | Yes if event type is specific, ignored if custom  | Both     | N/A           |
| data        | object                                | Yes if event type is custom, optional if specific | Both     | N/A           |
| shouldCache | boolean                               | No                                                | iOS Only | true          |

The `type` property is used to define the event as *custom* or *specific* event, using the [EventType](#selligenteventtype) constants.

To define it as a custom event, one should use the `SelligentConstants.EventType.CUSTOM` constant. All other event types can be used to define the event as something specific.

When an event is a *specific* event type, the `event` object requires an `email` property containing a string, and has an optional property `data` which is an object that can contain other information.
When an event is a *custom* event type, the `event` object requires a `data` property containing an object which contains other information, and ignores the `email` property.

**iOS specific:**

On iOS the `event` object can contain an additional optional `shouldCache` property, which is a boolean that can be used to cache and retry sending events in situations where the event could not be delivered.

By default it is set to `true`, setting it to `false` will disable it.

##### sendEvent example

```javascript
// send specific event
Selligent.sendEvent(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    {
        type: SelligentConstants.EventType.BUTTON_CLICKED // specific event
        data: { // optional
            id: 1337,
            randomFlag: true,
            description: "this is some extra information concerning this event"
        }
        email: "someone@somedomain.com" // required
    },
    shouldCache: false // iOS only, optional
);
// send custom event
Selligent.sendEvent(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    {
        type: SelligentConstants.EventType.CUSTOM  // custom event
        data: { // required
            id: 1337,
            someFlag: true,
            description: "this is some extra information concerning this event"
        }
        email: "someone@somedomain.com" // ignored
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.subscribeToEvents(successCallback, errorCallback, eventCallback)

This method is used to subscribe to events.

The response of the success callback is an object which contains information on the type of broadcast event and the data attached to it.

**Detailed overview:**

| Property           | Type                                                    | Description                                                       |
| ------------------ | ------------------------------------------------------- | ----------------------------------------------------------------- |
| broadcastEventType | enum [BroadcastEventType](#selligentbroadcasteventtype) | The type of broadcast event                                       |
| data               | object                                                  | Contains more information specific to the type of broadcast event |

The `data` property is an object itself containing more information specific to the type of the broadcast event:

In case of a broadcast event type _ButtonClicked_ the detailed overview for the `data` is as such:

| Property | Type                                                                       | Description                             |
| -------- | -------------------------------------------------------------------------- | --------------------------------------- |
| type     | iOS: enum [iOSNotificationButtonType](#selligentiosnotificationbuttontype) | The type of notification button clicked |
|          | Android: integer                                                           |                                         |
| value    | string                                                                     | A certain value the broadcof ast event  |
| id       | string                                                                     | A certain id of the event               |
| label    | string                                                                     | A certain label of the event            |
| data     | object                                                                     | Specific additional data of the event   |
| action   | integer                                                                    | Specific action of the event            |

In case of a broadcast event type _ReceivedInAppMessage_ the detailed overview for the `data` is as such:

| Property | Type  | Description      |
| -------- | ----- | ---------------- |
| messages | array | List of messages |

And the detailed overview for items in the `messages` array is as such:

| Property | Type   | Description        |
| -------- | ------ | ------------------ |
| id       | string | Id of a message    |
| title    | string | Title of a message |

In case of a broadcast event type _ReceivedGCMToken_ the detailed overview for the `data` is as such:

| Property | Type   | Description                     |
| -------- | ------ | ------------------------------- |
| token    | string | The token attached to the event |

In case of a broadcast event type _ReceivedRemoteNotification_ the detailed overview for the `data` is as such:

| Property | Type   | Description                                |
| -------- | ------ | ------------------------------------------ |
| pushId   | string | The id of the remote push notification     |
| name     | string | The name attached to the push notification |

In case of a broadcast event type _WillDisplayNotification_ or _WillDismissNotification_ the `data` prop is  `null`.

**Android specific:**

On the Android platform you can subscribe to custom events, by parsing an array of strings of these custom events. See the example for more information.

##### subscribeToEvents example

```javascript
Selligent.subscribeToEvents(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    (eventCallback) => {
        ...
    }
    ["some custom event x", "navigated to page y", "accepted request z"] // optional, android only
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

### Android Only/Specific Methods

#### Selligent.subscribeToEvent(eventCallback, eventName)

This method is used to subscribe to a single event on Android.

The response of the event callback is an object which contains information on the type of broadcast event and the data attached to it.

##### subscribeToEvent example

```javascript
Selligent.subscribeToEvents(
    (event) => { // event callback
        ...
    },
    "some custom event x" // custom event name
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.areInAppMessagesEnabled(successCallback)

Check if in-app messages are enabled or disabled.

The response of the success callback returns a boolean stating the in-app messages are enabled or disabled.

##### areInAppMessagesEnabled example

```javascript
Selligent.areInAppMessagesEnabled(
    (response) => { // success callback
        ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.enableAndroidLogging(successCallback, errorCallback, enabled)

Display different actions and information logged by the SDK in the Android Studio logcat.

The `enabled` parameter is a boolean to effectively enable or disable logging.

##### enableAndroidLogging example

```javascript
Selligent.enableAndroidLogging(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    true
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.displayMessage(successCallback, errorCallback, messageId)

Display a specific in-app message.
The method accepts a parameter `messageId` which is a string containing the id of the in-app message to display.

##### displayMessage example

```javascript
Selligent.displayMessage(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    "some in-app message id"
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.areNotificationsEnabled(successCallback)

Check if notifications are enabled or disabled.

The response of the success callback returns a boolean stating the notifications are enabled or disabled.

##### areNotificationsEnabled example

```javascript
Selligent.areNotificationsEnabled(
    (response) => { // success callback
        ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.setNotificationSmallIcon(successCallback, errorCallback, iconName)

Set the small icon of a notification on Android.

The method accepts an `iconName` parameter which is a string containing the name of the small icon. When the application is closed it will default back to the icons specified in `selligent.json`.
> _Note: only parse the name of the icon, without the path. The icon should reside in the res/drawable folder of the Android project, as explained in [Android's official guide](https://developer.android.com/guide/topics/resources/drawable-resource#BitmapFile)._

##### setNotificationSmallIcon example

```javascript
Selligent.setNotificationSmallIcon(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    "smallNotificationIcon"
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.setNotificationLargeIcon(successCallback, errorCallback, iconName)

Set the large icon of a notification on Android.

The method accepts an `iconName` parameter which is a string containing the name of the large icon. When the application is closed it will default back to the icons specified in `selligent.json`.
> _Note: only parse the name of the icon, without the path. The icon should reside in the res/drawable folder of the Android project, as explained in [Android's official guide](https://developer.android.com/guide/topics/resources/drawable-resource#BitmapFile)._

##### setNotificationLargeIcon example

```javascript
Selligent.setNotificationLargeIcon(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    "largeNotificationIcon"
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.getGCMToken(successCallback)

Get the GCM token being used.

The response of the success callback is a string containing the GCM token.

##### getGCMToken Example

```javascript
Selligent.getGCMToken(
  (response) => { // success callback
      ...
  }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.getRemoteMessagesDisplayType(successCallback, errorCallback)

Get the type of the remote messages that are being displayed.

The response of the success callback is a number corresponding with a constant of the [AndroidRemoteMessagesDisplayType](#selligentinappmessagerefreshtype) enum.

##### getRemoteMessagesDisplayType Example

```javascript
Selligent.getRemoteMessagesDisplayType(
  (response) => { // success callback
      ...
  },
  (error) => { // error callback
      ...
  }
);
```

#### Selligent.setFirebaseToken(successCallback, errorCallback, token)

Set the firebase token manually.

##### setFirebaseToken example

```javascript
window.Selligent.setFirebaseToken(
    function (response) { // success callback
      ...
    },
    function (error) { // error callback
      ...
    },
    '123xyz'
);
```

### iOS Only/Specific Methods

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.enableiOSLogging(successCallback, errorCallback, logLevels)

Display different actions and information logged by the SDK.

The `logLevels` parameter is an array of logging levels that you want to enable, using the [Selligent.iOSLogLevel](#selligentiosloglevel) enum.

To disable a certain level, the existing array of the enabled logging level(s), minus the one you want to disable, should be passed to the method.
To disable all log levels you need to use the iOSLogLevel.NONE constant.
To enable all log levels use the iOSLogLevel.ALL constant.

##### enableiOSLogging example

```javascript
// to enable logging of info, warning and error statements
Selligent.enableiOSLogging(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    [Selligent.iOSLogLevel.INFO, Selligent.iOSLogLevel.WARNING, Selligent.iOSLogLevel.ERROR]
);
// to disable all logging
Selligent.enableiOSLogging(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    [Selligent.iOSLogLevel.NONE]
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.currentAuthorisationStatus(successCallback)

Get the current status of location authorisation.

The response of the success callback is a number corresponding with a constant of the [Selligent.iOSLocationAuthorisationStatus](#selligentioslocationauthorisationstatus) enum.

##### currentAuthorisationStatus Example

```javascript
Selligent.currentAuthorisationStatus(
  (response) => { // success callback
      ...
  }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.requestLocationAuthorisation(successCallback, errorCallback, iOSLocationAuthorisationType)

Request an authorisation of using location on a device.

The method accepts an iOSLocationAuthorisationType parameter to define the type of authorisation which should be requested as there are two possibilities: "in use" and "always".
You can use constants of the [Selligent.iOSLocationAuthorisationType](#selligentioslocationauthorisationtype) enum to specify the authorisation request.

##### requestLocationAuthorisation Example

```javascript
Selligent.requestLocationAuthorisation(
  (response) => { // success callback
      ...
  },
  (error) => { // error callback
      ...
  },
  Selligent.iOSLocationAuthorisationType.IN_USE
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.displayNotification(successCallback, errorCallback, notificationId)

Display a notification based on its id, which is a string that needs to be parsed in the method with the `notificationId` parameter.

##### displayNotification Example

```javascript
Selligent.displayNotification(
  (response) => { // success callback
      ...
  },
  (error) => { // error callback
      ...
  },
  "some notification id"
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.registerRemoteNotificationFetchCompletionHandler(successCallback, errorCallback)

Register a completion handler for successfully fetching remote notifications.

The success callback is completion handler to be set.

##### registerRemoteNotificationFetchCompletionHandler example

```javascript
Selligent.registerRemoteNotificationFetchCompletionHandler(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    }
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### Selligent.forceRemoteNotificationBackgroundFetchResult(successCallback, errorCallback, iOSBackgroundFetchResult)

Force the result of a remote notification fetch to be a specific value.

##### forceRemoteNotificationBackgroundFetchResult example

```javascript
Selligent.forceRemoteNotificationBackgroundFetchResult(
    (response) => { // success callback
        ...
    },
    (error) => { // error callback
        ...
    },
    Selligent.iOSBackgroundFetchResult.NEW_DATA
);
```

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

### Constants

#### SelligentConstants.ClearCacheIntervalValue

Defines the interval value to clear the cache.

| Name        | Type   | Value | Description                                  |
| ----------- | ------ | ----- | -------------------------------------------- |
| AUTO        | number | 1     | Clear cache automatically (on startup?)      |
| NONE        | number | 2     | Don't clear cache                            |
| Android.DAY | number | 3     | Clear cache daily, only available on Android |
| WEEK        | number | 4     | Clear cache weekly                           |
| MONTH       | number | 5     | Clear cache monthly                          |
| QUARTER     | number | 6     | Clear cache quarterly                        |

_Note: `ClearCacheIntervalValue.Android.DAY` is only used on Android and can not be used on iOS._

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.InAppMessageRefreshType

Defines how often the SDK must retrieve the in-app messages.

| Name           | Type   | Value | Description                        |
| -------------- | ------ | ----- | ---------------------------------- |
| NONE           | number | 10    | Don't refresh the in-app messages  |
| Android.MINUTE | number | 11    | Refresh minutely (only on Android) |
| HOUR           | number | 12    | Refresh hourly                     |
| DAY            | number | 13    | Refresh weekly                     |

_Note: `InAppMessageRefreshType.Android.MINUTE` is only used on Android and can not be used on iOS._

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.AndroidRemoteMessagesDisplayType

Defines if and how remote messages can be displayed on Android.

| Name         | Type   | Value | Description                             |
| ------------ | ------ | ----- | --------------------------------------- |
| AUTOMATIC    | number | 20    | Display remote messages automatically   |
| NONE         | number | 21    | Don't display remote messages           |
| NOTIFICATION | number | 22    | Display remote messages as notification |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.iOSLogLevel

Defines the level of output of logging messages on iOS.

| Name      | Type   | Value | Description       |
| --------- | ------ | ----- | ----------------- |
| NONE      | number | 50    | Output nothing    |
| INFO      | number | 51    | Output info       |
| WARNING   | number | 52    | Output warning    |
| ERROR     | number | 52    | Output error      |
| HTTP_CALL | number | 52    | Output http calls |
| LOCATION  | number | 52    | Output location   |
| ALL       | number | 52    | Output all        |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.iOSBackgroundFetchResult

Description of the possible results of a background fetch on iOS.

| Name     | Type   | Value | Description                              |
| -------- | ------ | ----- | ---------------------------------------- |
| NEW_DATA | number | 60    | Background fetch resulted in new data    |
| NO_DATA  | number | 61    | Background fetch resulted in no new data |
| FAILED   | number | 62    | Background fetch failed                  |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.iOSLocationAuthorisationStatus

Description of the possible status of use of location services on a device.

| Name           | Type   | Value | Description                                     |
| -------------- | ------ | ----- | ----------------------------------------------- |
| UNKNOWN        | number | 70    | Status of use of location services is unknown   |
| REFUSED        | number | 71    | Use of location services is refused             |
| GRANTED_IN_USE | number | 72    | Use of location services is granted when in use |
| GRANTED_ALWAYS | number | 72    | Use of location services is always granted      |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.iOSLocationAuthorisationType

Defines the level of request for the authorisation of usage of location services on a device.

| Name   | Type   | Value | Description                                               |
| ------ | ------ | ----- | --------------------------------------------------------- |
| IN_USE | number | 80    | Request authorisation when location services are in use   |
| ALWAYS | number | 81    | Always request the authorisation of the location services |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.EventType

Defines the type of an event.

| Name            | Type   | Value | Description       |
| --------------- | ------ | ----- | ----------------- |
| USER_REGISTER   | number | 90    | User registered   |
| USER_UNREGISTER | number | 91    | User unregistered |
| USER_LOGIN      | number | 92    | User logged in    |
| USER_LOGOUT     | number | 93    | User logged out   |
| CUSTOM          | number | 94    | Custom event      |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.iOSNotificationButtonType

Defines the type of button for notifications on iOS.

| Name                          | Type   | Value | Description                               |
| ----------------------------- | ------ | ----- | ----------------------------------------- |
| UNKNOWN                       | number | 100   | Unknown button type                       |
| SIMPLE_OPEN_PHONE_CALL        | number | 101   | Simple open phone call button type        |
| OPEN_SMS                      | number | 102   | Open sms button type                      |
| OPEN_MAIL                     | number | 103   | Open mail button type                     |
| OPEN_BROWSER                  | number | 104   | Open browser button type                  |
| OPEN_APPLICATION              | number | 105   | Open application button type              |
| RATE_APPLICATION              | number | 105   | Rate application button type              |
| CUSTOM_ACTION_BROADCAST_EVENT | number | 105   | Custom action broadcast event button type |
| RETURN_TEXT                   | number | 105   | Return text button type                   |
| RETURN_PHOTO                  | number | 105   | Return photo button type                  |
| RETURN_TEXT_AND_PHOTO         | number | 105   | Return text and photo button type         |
| PASSBOOK                      | number | 105   | Passbook button type                      |

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>

#### SelligentConstants.BroadcastEventType

Defines the type of a broadcast event.

| Name                             | Type   | Value                        | Description                                           |
| -------------------------------- | ------ | ---------------------------- | ----------------------------------------------------- |
| BUTTON_CLICKED                   | string | "ButtonClicked"              | A button was clicked                                  |
| RECEIVED_IN_APP_MESSAGE          | string | "ReceivedInAppMessage"       | An in-app message has been received                   |
| WILL_DISPLAY_NOTIFICATION        | string | "WillDisplayNotification"    | A notification will be displayed                      |
| WILL_DISMISS_NOTIFICATION        | string | "WillDismissNotification"    | A notification will be dismissed                      |
| Android.RECEIVED_GCM_TOKEN       | string | "ReceivedGCMToken"           | A GCM token has been received (only on Android)       |
| iOS.RECEIVED_REMOTE_NOTIFICATION | string | "ReceivedRemoteNotification" | A remote notification has been received (only on iOS) |

_Notes: `BroadcastEventType.Android.RECEIVED_GCM_TOKEN` is only used on Android and can not be used on iOS. `BroadcastEventType.iOS.RECEIVED_REMOTE_NOTIFICATION` is only used on iOS and can not be used on Android._

<div align="right">
    <b><a href="#api-reference">back to API ToC</a></b>
</div>
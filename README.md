# Marigold Engage-ReactNative (selligent-react-native)

This module provides an API for the usage of the Marigold Engage Mobile SDKs in React Native.

## Marigold Engage-ReactNative Integration

This module supports the following SDK and tools:

> **IMPORTANT** This module isn't built using ReactNative's new architecture! It is however compatible with apps that do adopt the new architecture, as far as they are using latest ReactNative's versions.

| SDK                                                                            | Version |
| ------------------------------------------------------------------------------ |---------|
| [Android SDK](https://github.com/SelligentMarketingCloud/MobileSDK-Android)    | 4.5.0   |
| [iOS SDK](https://github.com/SelligentMarketingCloud/MobileSDK-iOS)            | 3.8.3   |
| ReactNative                                                                    | 0.73.4  |
| Expo SDK                                                                       | 50      |

## Installation

> Please refer to our [SDK full documentation](documentation/#reactnative--using-the-sdk) for a step-by-step guide on how to use the SDK, after installation.

1. Install the module

   ```shell
   npm install @selligent-marketing-cloud/selligent-react-native --save
   ```

2. Create a `selligent.json` file (name is case sensitive) in the root of the React Native project (you can alternatively place it inside another folder or inside a `selligent` folder which will automatically be checked by the wrapper) with the following content:

   ```json
   {
     "url": "someMobilePushUrl",
     "clientId": "someClientId",
     "privateKey": "somePrivateKey",
     "fullyQualifiedNotificationActivityClassName": "com.some.project.MainActivity",
     "delayedPushAction": true
   }
   ```

> Check all the options that can be used in our [SDK full documentation](documentation/#working-with-the-selligentjson)

### Android Specific Installation

> **IMPORTANT:** Since version 2.6.0 of this module we require your app to use the Android Gradle Plugin version 7.0.0 or higher in order to build on Android.

<details>
<summary>Without autolinking (RN 0.59 and below)</summary>

1. Create a Google application following the section [native documentation](https://github.com/SelligentMarketingCloud/MobileSDK-Android/tree/master/Documentation#creating_app), and place the `google-services.json` file in the `./android/app` folder.

2. Add the following lines at the end of the `android/settings.gradle` file:

   ```groovy
   include ':selligent-react-native'
   project(':selligent-react-native').projectDir = new File(rootProject.projectDir, '../node_modules/@selligent-marketing-cloud/selligent-react-native/android')
   ```

3. Add the following in the `android/build.gradle` file, and make sure that the Gradle version in `android/gradle/wrapper/gradle-wrapper.properties` is >= 6.7.1:

   ```groovy
   // android/build.gradle

   buildscript {
       dependencies {
           // Make sure your Gradle plugin version is >= 7.0.0
           classpath("com.android.tools.build:gradle:7.0.0")
           // Add the following:
           classpath 'com.google.gms:google-services:4.3.15'
       }
   }
   ```

   ```groovy
    // android/gradle/wrapper/gradle-wrapper.properties
    distributionUrl=https\://services.gradle.org/distributions/gradle-6.7.1-all.zip
   ```

4. Add the following in the `android/app/build.gradle` file:

   ```groovy
   dependencies {
       // Add the following:
       compile project(path: ':selligent-react-native')
   }
   // Add the following:
   apply plugin: 'com.google.gms.google-services'
   ```

5. Add the following in the `android/app/src/../MainApplication.java` file:

   ```java
   // Add the following import statements:
   import com.selligent.RNSelligent;
   import com.selligent.RNSelligentPackage;

   public class MainApplication extends Application implements ReactApplication {

       private final ReactNativeHost mReactNativeHost = new ReactNativeHost(this) {
            @Override
            protected List<ReactPackage> getPackages() {

                List<ReactPackage> packages = new PackageList(this).getPackages();
                // Add the following:
                packages.add(new RNSelligentPackage());
                return packages;
            }
       };

       @Override
       public void onCreate() {
           super.onCreate();

           // Add the following:
           RNSelligent.configure(this);
       }
   }
   ```

</details>

<details open>
<summary>With autolinking (RN 0.60 and above)</summary>

1. Create a Google application following the section **Creating a Google application** of the **Android - Using the SDK** pdf, and place the `google-services.json` file in the `./android/app` folder.

2. Add the following in the `android/build.gradle` file, and make sure that the Gradle version in `android/gradle/wrapper/gradle-wrapper.properties` is >= 6.7.1:

   ```groovy
   // android/build.gradle 

   buildscript {
       dependencies {
           // Add the following:
           classpath 'com.google.gms:google-services:4.3.15'
       }
   }
   ```

3. Add the following in the `android/app/build.gradle` file (at the bottom):

   ```groovy
   // Add the following:
   apply plugin: 'com.google.gms.google-services'
   ```

4. Add the following in the `android/app/src/../MainApplication.java` file:

    ```java
    // Add the following import statements:
    import com.selligent.RNSelligent;
    import com.selligent.RNSelligentPackage;

    public class MainApplication extends Application implements ReactApplication {
        @Override
        public void onCreate() {
            super.onCreate();

            // Add the following:
            RNSelligent.configure(this);
        }
    }
    ```

</details>

### iOS Specific installation

<details>
<summary>Without autolinking (RN 0.59 and below)</summary>

1. Copy the `node_modules/@selligent-marketing-cloud/selligent-react-native/ios` folder to the **Xcode project**. Drop it under the `Libraries` Folder. This will link the module to the iOS project.

2. Drag and drop the `selligent.json` you created (or the full folder(s) containing it) to the Xcode project inside the `Copy Bundle Resources` in `Build phases` of your target:

    > Do not check the "copy if needed" option to make sure you only have to manage one selligent.json file

3. Add the native iOS SDK dependency in your Podfile: `s.dependency "SelligentMobileSDK/Framework", "3.8.3"` or download it manually from [here](https://github.com/SelligentMarketingCloud/MobileSDK-iOS/tree/master/Framework) and drag and drop it into you **Xcode project**.

4. Add the RNSelligentMapper pod in your Podfile: `pod 'RNSelligentMapper', :path => '../node_modules/@selligent-marketing-cloud/selligent-react-native/RNSelligentMapper.podspec'`.

5. Execute `pod install` in the `/ios` folder

6. From now on, open the `.xcworkspace` file to make changes in Xcode

7. Bootstrap the SDK in the `application:didFinishLaunchingWithOptions:` of the `AppDelegate.mm`

    ```objective-c
    @import RNSelligentMobileSDK;
    // OR
    // #import <RNSelligentMobileSDK/RNSelligentMobileSDK-Swift.h>
    
    // You can alternatively specify a different file name (without the extension) from where to load the Marigold Engage configs (defaults to 'selligent')
    // if (!launchOptions) {
    //    launchOptions = [NSMutableDictionary new];
    // }
    // [launchOptions setValue:@"alternativeFileName" forKey:@"RN_SELLIGENT_JSON"];
    // [launchOptions setValue:@"selligent/alternativeFileName" forKey:@"RN_SELLIGENT_JSON"];
    // [launchOptions setValue:@"alternativeFolder/alternativeFileName" forKey:@"RN_SELLIGENT_JSON"];

    // At the end of application:didFinishLaunchingWithOptions:
    [RNSelligent configureWithLaunchOptions:launchOptions];
    ```

</details>

<details open>
<summary>With autolinking (RN 0.60 and above)</summary>

1. Drag and drop the `selligent.json` you created (or the full folder(s) containing it) to the Xcode project inside the `Copy Bundle Resources` in `Build phases` of your target:

    > Do not check the "copy if needed" option to make sure you only have to manage one selligent.json file

2. Execute `pod install` in the `/ios` folder

3. Import & bootstrap the SDK in the `application:didFinishLaunchingWithOptions:` of the `AppDelegate.m` (put it at the end of the method)

    ```objc
    @import RNSelligentMobileSDK;
    // OR
    // #import <RNSelligentMobileSDK/RNSelligentMobileSDK-Swift.h>
    
    // You can alternatively specify a different file name (without the extension) from where to load the Marigold Engage configs (defaults to 'selligent')
    // if (!launchOptions) {
    //    launchOptions = [NSMutableDictionary new];
    // }
    // [launchOptions setValue:@"alternativeFileName" forKey:@"RN_SELLIGENT_JSON"];
    // [launchOptions setValue:@"selligent/alternativeFileName" forKey:@"RN_SELLIGENT_JSON"];
    // [launchOptions setValue:@"alternativeFolder/alternativeFileName" forKey:@"RN_SELLIGENT_JSON"];

    // At the end of application:didFinishLaunchingWithOptions:
    [RNSelligent configureWithLaunchOptions:launchOptions];
    ```

</details>

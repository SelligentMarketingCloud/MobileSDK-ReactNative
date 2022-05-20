# Changelog

## [2.9.0] - 20 May 2022

### Added
- Add possibility to set the app's notification channel's ID, name and description on `Android` via `notificationChannelId`, `notificationChannelName`, and `notificationChannelDescription` settings keys in `selligent.json`.
- Add comment to README about rich push notification method invocation deprecation on iOS.

### Changed
- Add version 3.9.0 of the Android SDK to `android/libs`
- Add version 2.7.4 of the iOS SDK static library to `/ios`
- Change used native SDK version numbers to `3.9.0` and `2.7.4` for Android and iOS respectively in README

## [2.8.0] - 18 February 2022

### Added
- Re-add plotProjects dependency for Android in `android/build.gradle`
- Re-add geolocation native module functions (`enableGeolocation`, `isGeoLocationEnabled`) for Android
- Re-add geofencing header files for iOS in `ios/include` and module files in `ios/`
- Re-add plotProjects and geolocation documentation to README
- Add documentation regarding the Gradle build tool version and Gradle version compatability

### Changed
- Add version 3.8.1 of the Android SDK to `android/libs`
- Swap the deprecated maven plugin and its archiving capabilities for the maven-publish plugin in `android/build.gradle`
- Add version 2.7.2 of the iOS SDK static library to `ios/`
- Change used native SDK version numbers to `3.8.1` and `2.7.2` for Android and iOS respectively in README
- Bump the react-native library to `0.67.2` in `package.json`
- Bump wrapper version to `2.8.0` in `package.json`

### Fixed
 - Fix typos in README as duly noted in https://github.com/SelligentMarketingCloud/MobileSDK-ReactNative/issues/25

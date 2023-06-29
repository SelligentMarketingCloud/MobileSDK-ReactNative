require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "RNSelligent"
  s.authors      = package['author']
  s.version      = package["version"]
  s.summary      = package["description"]
  s.description  = "React Native wrapper for the Selligent Marketing Cloud Android and iOS SDKs"
  s.homepage     = package['homepage']
  s.license      = "MIT"
  s.platform     = :ios, "11.0"
  s.source       = { :git => "https://github.com/SelligentMarketingCloud/MobileSDK-ReactNative.git", :tag => "#{s.version}" }

  s.vendored_frameworks = "ios/RNSelligentMobileSDK.xcframework"
  s.source_files = "ios/*.{h,m}"
  
  s.dependency "React-Core"
  s.dependency "SelligentMobileSDK/Framework", "3.5.1"
end
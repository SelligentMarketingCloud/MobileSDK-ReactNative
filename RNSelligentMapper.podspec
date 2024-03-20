require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name          = "RNSelligentMapper"
  s.authors       = package['author']
  s.version       = package["version"]
  s.summary       = package["description"]
  s.description   = "React Native wrapper mapper for the Marigold Engage Android and iOS SDKs"
  s.homepage      = package['homepage']
  s.license       = "MIT"
  s.platform      = :ios, "13.4"
  s.source        = { :git => "https://github.com/SelligentMarketingCloud/MobileSDK-ReactNative.git", :tag => "v" + s.version.to_s }
  s.swift_version = "5.0"
  
  s.source_files  = "ios/*.{h,m}"
  
  s.dependency "React-Core"
  s.dependency "RNSelligent"
end
	
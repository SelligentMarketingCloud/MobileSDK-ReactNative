require "json"

package = JSON.parse(File.read(File.join(__dir__, "package.json")))

Pod::Spec.new do |s|
  s.name         = "SelligentReactNative"
  s.version      = package["version"]
  s.summary      = package["description"]
  s.authors      = "Selligent"
  s.description  = "Selligent Marketing Cloud Mobile SDK"
  
  s.homepage     = "https://github.com/SelligentMarketingCloud/MobileSDK-ReactNative"
  s.license      = "MIT"
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/SelligentMarketingCloud/MobileSDK-ReactNative.git", :tag => "v#{s.version}" }
  s.source_files = "ios/**/*.{h,m}"
  s.requires_arc = true
  s.dependency "React"
  s.dependency 'PlotPlugin', '2.1.0'
end

  
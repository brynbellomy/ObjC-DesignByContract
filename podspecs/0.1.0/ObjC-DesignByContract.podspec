Pod::Spec.new do |s|
  s.name         = "ObjC-DesignByContract"
  s.version      = "0.1.0"
  s.summary      = "Macros for implementing design-by-contract architecture into Objective-C programs."
  s.homepage     = "http://github.com/brynbellomy/ObjC-DesignByContract"
  s.license      = "LICENSE.md"

  s.author       = { "Bryn Austin Bellomy" => "bryn.bellomy@gmail.com" }
  s.source       = { :git => "https://github.com/brynbellomy/ObjC-DesignByContract.git" }

  s.source_files = "{Contracts.h,vendor/libextobjc/EXTScope.{h,m}}"
  s.requires_arc = true

  s.xcconfig = { "PUBLIC_HEADERS_FOLDER_PATH" => "include/$(TARGET_NAME)" }
end

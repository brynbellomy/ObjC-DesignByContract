Pod::Spec.new do |s|
  s.name         = "ObjC-DesignByContract"
  s.version      = "0.0.1"
  s.summary      = "A short description of ObjC-DesignByContract."
  s.homepage     = "http://EXAMPLE/ObjC-DesignByContract"
  s.license      = 'COPYING'

  s.author       = { "Bryn Austin Bellomy" => "bryn@signals.io" }
  s.source       = { :git => "/Users/bryn/repo/ObjC-DesignByContract.git" }

  # s.ios.deployment_target = '4.3'
  # s.osx.deployment_target = '10.6'

  s.source_files = 'Contracts.h'

  s.xcconfig = { 'PUBLIC_HEADERS_FOLDER_PATH' => 'include/$(TARGET_NAME)' }
end

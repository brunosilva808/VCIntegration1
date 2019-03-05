cordova plugin remove cordova-plugin-toastyplugin
cordova platform remove android
cordova platform add android
mkdir "C:\Users\carlo\Documents\Customers\Dubai Courts\dev\cordovavc\appcordova\testApp\platforms\android\app\libs"
xcopy /E "C:\Users\carlo\Documents\Customers\Dubai Courts\dev\cordovavc\VCIntegration1\libs" "C:\Users\carlo\Documents\Customers\Dubai Courts\dev\cordovavc\appcordova\testApp\platforms\android\app\libs"
cordova plugin add "C:\Users\carlo\Documents\Customers\Dubai Courts\dev\cordovavc\VCIntegration1"
cordova build android

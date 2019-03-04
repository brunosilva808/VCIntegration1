cordova plugin remove cordova-plugin-toastyplugin
cordova platform remove android
cordova platform add android
mkdir C:\Users\carlo\Desktop\DubaiCourts\toasty-plugin-test\platforms\android\app\libs
xcopy /E C:\Users\carlo\Documents\GitHub\COPlugin\libs C:\Users\carlo\Desktop\DubaiCourts\toasty-plugin-test\platforms\android\app\libs
cordova plugin add C:\Users\carlo\Documents\GitHub\ToastyPlugin1
cordova build android


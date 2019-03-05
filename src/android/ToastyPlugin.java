package com.askblue.cordova.plugin;
// The native Toast API
import android.widget.Toast;
import android.content.Context;
import android.content.Intent;
// Cordova-required packages
import org.apache.cordova.CallbackContext;
import org.apache.cordova.CordovaPlugin;
import org.apache.cordova.PluginResult;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import android.util.Log;

import android.app.Application;
import android.support.annotation.CallSuper;

import com.clearone.sptimpublicsdk.SptIMSDKApp;
import com.clearone.sptimpublicsdk.ISptIMSDK;


import android.util.Log;
import android.content.res.Resources;

public class ToastyPlugin extends CordovaPlugin {
  private static final String DURATION_LONG = "long";

  String serverName;
  String sessionID;
  String userName;
  ISptIMSDK _sdk;

  @Override
  public boolean execute(String action, JSONArray args,
    final CallbackContext callbackContext) {
      // Verify that the user sent a 'show' action
      if (!action.equals("show")) {
        callbackContext.error("\"" + action + "\" is not a recognized action.");
        return false;
      }


      try {

        JSONObject options = args.getJSONObject(0);
        serverName = options.getString("serverName");
        sessionID = options.getString("sessionID");
        userName = options.getString("userName");

      } catch (JSONException e) {
        callbackContext.error("Error encountered: " + e.getMessage());
        return false;
      }
      // Create the toast
      Toast toast = Toast.makeText(cordova.getActivity(), serverName + " " + sessionID + " " + userName, Toast.LENGTH_LONG);
      // Display toast
      //toast.show();

    //  Intent yourIntent = new Intent(this.getActivity().getApplicationContext(), MainActivity.class);
    //  cordova.getActivity().startActivity(yourIntent);
      final CordovaPlugin that = this;

      //SptIMSDKApp app1 = SptIMSDKApp.getInstance();
      //app1.getSptIMSDK(that.cordova.getActivity().getBaseContext());

      _sdk = SptIMSDKApp.getInstance().getSptIMSDK(null);

      cordova.getActivity().runOnUiThread(new Runnable() {
       @Override
       public void run() {

          Intent intentScan = new Intent(that.cordova.getActivity().getBaseContext(), MainActivity.class);
          intentScan.putExtra("serverName", serverName);
          intentScan.putExtra("sessionID", sessionID);
          intentScan.putExtra("userName", userName);

          //String package_name = cordova.getApplication().getPackageName();
          //Resources resources = getApplication().getResources();

          //Log.v("package name0: ", package_name);
         // Log.v("Resources name: ", resources.String);
        //  Log.v("view ID0: ", String.valueOf(resources.getIdentifier("activity_main", "layout", package_name)));

        //  intentScan.putExtra("activity_main_connect_button", String.valueOf(cordova.getActivity().getResources().getIdentifier("activity_main_connect_button", "layout", cordova.getActivity().getPackageName())));

        //  Log.v("activity_main_connect_button0 name: ", String.valueOf(cordova.getActivity().getResources().getIdentifier("activity_main_connect_button", "layout", cordova.getActivity().getPackageName())));
        //   Context context = cordova.getActivity()
          //         .getApplicationContext();
          // Intent intent = new Intent(context, MainActivity.class);
          that.cordova.getActivity().startActivity(intentScan);
       }
     });

  // return true;

      //Context context = cordova.getActivity().getApplicationContext();
    //  this.openNewActivity(context);
      // Send a positive result to the callbackContext
      PluginResult pluginResult = new PluginResult(PluginResult.Status.OK);
      callbackContext.sendPluginResult(pluginResult);
      return true;
  }

}

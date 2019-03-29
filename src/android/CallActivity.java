package com.askblue.cordova.plugin;

import android.os.Bundle;
import org.apache.cordova.*;
import android.util.Log;

import android.media.AudioManager;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.ActionBar;   // alterado
import android.support.v7.app.AppCompatActivity; // alterado para v4
import android.os.Bundle;
import android.support.v7.widget.Toolbar;  // alterado para v4
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.content.res.Resources;

import com.clearone.sptimpublicsdk.ISptCallData;
import com.clearone.sptimpublicsdk.ISptCallParticipant;
import com.clearone.sptimpublicsdk.ISptCallRequest;
import com.clearone.sptimpublicsdk.ISptCallServices;
import com.clearone.sptimpublicsdk.ISptIMSDK;
import com.clearone.sptimpublicsdk.SptCallFragment;
import com.clearone.sptimpublicsdk.SptCallID;
import com.clearone.sptimpublicsdk.SptCallParticipantID;
import com.clearone.sptimpublicsdk.SptIMSDKApp;

import com.askblue.cordova.plugin.TestConnectMeetingApplication;

import static com.clearone.sptimpublicsdk.ParticipantServices.eSptServiceActive;
import static com.clearone.sptimpublicsdk.SptCallParticipantID.SPT_LOCAL_CALLPARTICIPANT_ID;

public class CallActivity extends AppCompatActivity implements SptCallFragment.OnSptCallFragmentListener,
                                                              SharingOptionsDialog.SharingOptionsDialogListener,
                                                              ImageViewFragment.OnFragmentInteractionListener {

    public static final String EXTRA_CALL_ID = "EXTRA_CALL_ID";
    private static final int REQUEST_CODE_SHARE_GALLERY = 100;

    SptCallID _callID;
    SptCallParticipantID _localParticipantID = new SptCallParticipantID(SPT_LOCAL_CALLPARTICIPANT_ID);
    ISptIMSDK _sdk;
    CallActivitySptObserver _sptCallObserver;
    int _screenSharingRequestCode = -1;

    SptIMSDKApp _app1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
      //  setContentView(R.layout.activity_call);

        String package_name = getApplication().getPackageName();
        Resources resources = getApplication().getResources();
        setContentView(resources.getIdentifier("content_main", "layout", package_name));
        setTitle(" ");

        int callId = getIntent().getIntExtra(EXTRA_CALL_ID, SptCallID.SPT_INVALID_CALLID);

        _sdk = SptIMSDKApp.getInstance().getSptIMSDK(getApplicationContext());

        _callID = new SptCallID(callId);

        if(_callID != null) {
          Log.v("two: ","call Id valid");
        } else {
          Log.v("two: ","bolas");
        }

      //  TestConnectMeetingApplication _app = (TestConnectMeetingApplication) getApplication();
      //  _sdk = _app.getSptIMSDK();


      //  _app = SptIMSDKApp.getInstance();
        //Toolbar tb = (Toolbar)findViewById(R.id.activity_call_tool_bar);
        Toolbar tb = (Toolbar)findViewById(resources.getIdentifier("activity_call_tool_bar", "id", package_name));
        setSupportActionBar(tb);
        //Keep screen always on during a call
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        // Show even if screen locked
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_SHOW_WHEN_LOCKED | WindowManager.LayoutParams.FLAG_DISMISS_KEYGUARD);
        View rootView = getWindow().getDecorView().getRootView();
        rootView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN);
        //Attach hardware volume controls to our application volume
        setVolumeControlStream(AudioManager.STREAM_VOICE_CALL);
        if(savedInstanceState == null)
        {
            FragmentManager fm = getSupportFragmentManager();
            FragmentTransaction ft = fm.beginTransaction();
            Fragment f = SptCallFragment.newInstance(_callID, true, null);
            ft.replace(resources.getIdentifier("activity_call_content", "id", package_name), f);
            //ft.replace(R.id.activity_call_content, f);
            ft.commit();
        }

        _sptCallObserver = new CallActivitySptObserver();
        _sdk.addCallObserver(_sptCallObserver);

    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        _sdk.removeCallObserver(_sptCallObserver);
    }

    private void requestServiceState(int serviceId, boolean bActivate)
    {
        //_app = SptIMSDKApp.getInstance();
        //_app.getSptIMSDK(getApplicationContext()).setServiceState(_callID, _localParticipantID,serviceId, bActivate);

        _sdk.setServiceState(_callID, _localParticipantID,serviceId, bActivate);
    //    TestConnectMeetingApplication app = (TestConnectMeetingApplication) getApplication();
      //  app.getSptIMSDK().setServiceState(_callID, _localParticipantID,serviceId, bActivate);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {

      String package_name = getApplication().getPackageName();
      Resources resources = getApplication().getResources();
    //  setContentView(resources.getIdentifier("content_main", "layout", package_name));
    //  setTitle(" ");

        getMenuInflater().inflate(resources.getIdentifier("call_menu", "layout", package_name), menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {

        ISptCallData callData = _sdk.getActiveCallbyID(_callID);
        boolean bSharingActive = false;
        if(callData != null)
        {
         ISptCallParticipant localParticipant = callData.getParticipantByID(_localParticipantID);
         if(localParticipant != null)
             bSharingActive = (localParticipant.getServices().iSharingService & eSptServiceActive)!=0;
        }

        String package_name = getApplication().getPackageName();
        Resources resources = getApplication().getResources();

        //MenuItem item = menu.findItem(R.id.call_menu_start_sharing_item);

        MenuItem item = menu.findItem(resources.getIdentifier("call_menu_start_sharing_item", "id", package_name));
        item.setVisible(!bSharingActive);
        //item = menu.findItem(R.id.call_menu_stop_sharing_item);
        item = menu.findItem(resources.getIdentifier("call_menu_stop_sharing_item", "id", package_name));
        item.setVisible(bSharingActive);
        return super.onPrepareOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {

        String package_name = getApplication().getPackageName();
        Resources resources = getApplication().getResources();

        int id1 = resources.getIdentifier("call_menu_start_sharing_item", "id", package_name);
        int id2 = resources.getIdentifier("call_menu_stop_sharing_item", "id", package_name);

        if (item.getItemId() == id1) {
            requestSharingService(true);
        }

        if (item.getItemId() == id2) {
            requestSharingService(false);
        }

        switch (item.getItemId())
        {
         /*  case R.id.call_menu_start_sharing_item:
              requestSharingService(true);
              break;
          case R.id.call_menu_stop_sharing_item:
              requestSharingService(false);
              break;*/
        }
        return super.onOptionsItemSelected(item);
    }

    private void requestSharingService(boolean bActive)
    {
        _sdk.setServiceState(_callID, _localParticipantID,ISptCallServices.eSptCallServiceSharing, bActive);
    }

    @Override
    public boolean isActionBarShowing() {
        return false;
    }

    @Override
    public void onCallHangButtonPressed() {
            _sdk.hangUpCall(_callID);
            finish();
    }

  //  @Override
  //  public void onCallHangButtonPressed() {
        //TestConnectMeetingApplication app = (TestConnectMeetingApplication) getApplication();

    //    _app.getSptIMSDK(getApplicationContext()).hangUpCall(_callID);
      //  app.getSptIMSDK().hangUpCall(_callID);
      //  finish();
  //  }




    @Override
    public void OnRotateCamera() {

    }

    @Override
    public void onVideoButtonPressed(boolean b) {
        requestServiceState(ISptCallServices.eSptCallServiceVideo, b);

    }

    @Override
    public void onMicButtonPressed(boolean b) {
        requestServiceState(ISptCallServices.eSptCallServiceAudio, b);

    }

    @Override
    public void onSpeakerButtonPressed() {

    }

    @Override
    public void showActionBar() {
        ActionBar a = getSupportActionBar();
        if(a != null) {
            View rootView = getWindow().getDecorView().getRootView();
            rootView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_VISIBLE);
            a.show();
        }
    }

    @Override
    public void hideActionBar() {
        ActionBar a = getSupportActionBar();
        if(a != null)
            a.hide();
        hideColorPicker();
        View rootView = getWindow().getDecorView().getRootView();
        rootView.setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN);
    }

    @Override
    public void showColorPicker() {

    }

    @Override
    public void hideColorPicker() {

    }

    @Override
    public Fragment getLocalSharingFragment(SptCallFragment.eSharingType eSharingType) {
      Fragment res = null;
      switch (eSharingType) {
          case eSharingTypeGallery:
              res = ImageViewFragment.newInstance(_callID, true);
              break;
      }
      return res;
    }

    @Override
    public void onBackPressed()
    {
        super.onBackPressed();
        _sdk.hangUpCall(_callID);
        _callID = null;
    }


    @Override
        public void activateWhiteboard(boolean b) {
           _sdk.setServiceState(_callID, _localParticipantID, ISptCallServices.eSptCallServiceWhiteboard, b);

    }
  //  @Override
  //  public void activateWhiteboard(boolean b) {
      //  TestConnectMeetingApplication app = (TestConnectMeetingApplication) getApplication();
    //    _app.getSptIMSDK(getApplicationContext()).setServiceState(_callID, _localParticipantID, ISptCallServices.eSptCallServiceWhiteboard, b);
      //  app.getSptIMSDK().setServiceState(_callID, _localParticipantID, ISptCallServices.eSptCallServiceWhiteboard, b);

  //  }
  @Override
  public void onFinisSharingOptionsDialog(SptCallFragment.eSharingType sharingSelected) {
      switch (sharingSelected)
      {
          case eSharingTypeScreen:
              requestScreenSharing();
              break;
          case eSharingTypeGallery:
              shareGallery();
              break;
          default:
              requestSharingService(false);
      }
  }

  private void requestScreenSharing()
  {
     _sdk.startSharingScreen(_callID);
  }

  private void shareGallery()
  {
      Boolean result = checkPermission
              (this, MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE);
      if (result)
          showGallerySelector();
  }

  private void showGallerySelector()
  {
      Intent intent = new Intent();
      intent.setType("*/*");
      String[] mimetypes = {"image/*"};
      intent.putExtra(Intent.EXTRA_MIME_TYPES, mimetypes);
      intent.setAction(Intent.ACTION_GET_CONTENT);
      startActivityForResult(intent, REQUEST_CODE_SHARE_GALLERY);
  }

  public static final int MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE = 123;

  @Override
  public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults)
  {
      super.onRequestPermissionsResult(requestCode, permissions, grantResults);
      if(requestCode == MY_PERMISSIONS_REQUEST_READ_EXTERNAL_STORAGE)
      {
          for (int i = 0; i < permissions.length; i++)
          {
              if (permissions[i].equals(Manifest.permission.READ_EXTERNAL_STORAGE)
                      && grantResults[i] != PackageManager.PERMISSION_GRANTED)
              {
                  showGallerySelector();
              }
          }
      }
  }
  
  @Override
  private void onActivityResult(int requestCode, int resultCode, Intent data) {
      super.onActivityResult(requestCode, resultCode, data);
      switch (requestCode)
      {
          case REQUEST_CODE_SHARE_GALLERY:
              if(resultCode == Activity.RESULT_OK)
                  onShareGalleryResult(data);
              break;
      }

      if(requestCode == _screenSharingRequestCode)
      {
          onShareScreenResult(resultCode, data);
          _screenSharingRequestCode = -1;
      }
  }

  @Override
  public void onBackPressed()
  {
      super.onBackPressed();
      _sdk.hangUpCall(_callID);
      _callID = null;
  }

  private void goToBackground()
  {
      Intent homeIntent = new Intent(Intent.ACTION_MAIN);
      homeIntent.addCategory(Intent.CATEGORY_HOME);
      homeIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
      startActivity(homeIntent);
  }

  private void onShareScreenResult(int resultCode, Intent data)
  {
      if(resultCode == Activity.RESULT_OK)
          goToBackground();
      else
          requestSharingService(false);
      _sdk.onRequestUserAutorizationResult(_callID, _screenSharingRequestCode, resultCode, data);
  }

  private void onShareGalleryResult(Intent data)
  {
      Fragment f = getSupportFragmentManager().findFragmentByTag(SptCallFragment.TAG);
      if(f != null && f instanceof  SptCallFragment) {
          Bundle args = new Bundle();
          args.putString(ImageViewFragment.ARG_CONTENT_URI, data.getData().toString());
          args.putInt(ImageViewFragment.ARG_CALLID, _callID.intValue());
          args.putBoolean(ImageViewFragment.ARG_ANNOTATION_ENABLED, true);
          ((SptCallFragment) f).onAddLocalSharing(SptCallFragment.eSharingType.eSharingTypeGallery, args);
      }
  }

  @Override
  public void onUriSet(Uri uri) {

  }

  @Override
  public void onFragmentClick() {
      Fragment f = getSupportFragmentManager().findFragmentByTag(SptCallFragment.TAG);
      if(f != null && f instanceof  SptCallFragment) {
          ((SptCallFragment) f).onTapDetected();
      }
  }

  @Override
  public void onStopLocalSharing()
  {
      Fragment f = getSupportFragmentManager().findFragmentByTag(SptCallFragment.TAG);
      if(f != null && f instanceof  SptCallFragment) {
          ((SptCallFragment) f).onRemoveLocalSharing();
      }
  }




  public class CallActivitySptObserver extends SptCallObserver
      {
          @Override
          public void onCallEventRequestUpdated(SptCallID sptCallID, ISptCallRequest iSptCallRequest) {
              switch(iSptCallRequest.getType()) {
                  case eSptCallRequestTypeShareApplication:
                      if (iSptCallRequest.getState() == ISptCallRequest.eSptCallRequestState.eSptCallRequestStatePending) {
                          runOnUiThread(new Runnable() {
                              @Override
                              public void run() {
                                  FragmentManager fm = getSupportFragmentManager();
                                  //SharingOptionsDialog sharingDialogFragment = SharingOptionsDialog.newInstance("Some Title");
                                  //sharingDialogFragment.show(fm, "fragment_edit_name");
                              }
                          });
                      }
                      break;
              }
          }

          @Override
          public void onCallEventDisconnected(SptCallID sptCallID, ISptCallData iSptCallData)
          {
              runOnUiThread(new Runnable() {
                  @Override
                  public void run()
                  {
                      finish();
                  }
              });
          }

      //    @Override
      //    public void requestUserAutorization(Intent intent, int i) {
      //        _screenSharingRequestCode = i;
      //        startActivityForResult(intent, i);
      //    }
      }

}

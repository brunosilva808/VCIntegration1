package com.askblue.cordova.plugin;

import android.os.Bundle;
import org.apache.cordova.*;
import android.util.Log;

import android.Manifest;
import android.content.Intent;
import android.support.annotation.Nullable;
import android.content.pm.PackageManager;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;  // alterado
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.content.res.Resources;
import android.view.Menu;
import android.view.MenuItem;
import android.app.AlertDialog;
import android.content.DialogInterface;

import com.clearone.sptimpublicsdk.ISptCallData;
import com.clearone.sptimpublicsdk.ISptIMSDK;
import com.clearone.sptimpublicsdk.ISptSDKCallObserver;
import com.clearone.sptimpublicsdk.ISptIMSDKObserver;
import com.clearone.sptimpublicsdk.SptCallID;
import com.clearone.sptimpublicsdk.SptJoinCall;
import com.clearone.sptimpublicsdk.SptIMSDKApp;

import com.clearone.sptimpublicsdk.ISptIMContact;
import com.clearone.sptimpublicsdk.ISptSchMeeting;
import com.clearone.sptimpublicsdk.ISptSchMeetingSequence;
import com.clearone.sptimpublicsdk.SptIMContactID;
import com.clearone.sptimpublicsdk.SptSchJoinMeeting;
import com.clearone.sptimpublicsdk.SptSchMeetingSequenceID;
import com.clearone.sptcore.sptim.SptTokenDataResult;

import com.askblue.cordova.plugin.TestConnectMeetingApplication;

import static com.clearone.sptimpublicsdk.ISptIMSDK.eSptResult.eSptIMResultError;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private static int REQUEST_CODE_ASK_PERMISSIONS = 1;
    public static String EXTRA_JOIN_TO_MEETING = "EXTRA_JOIN_TO_MEETING";

    TextConnectSptIMObserver _sptObserver;
    //MainActivitySptIMObserver _sptIMObserver;
    TestConnectSptCallObserver _callObserver;
  //  ViewPager _viewPager;
  //  MainPagerAdapter _pageAdapter;
  //  TabLayout _tabLayout;
    SptSchMeetingSequenceID _tokenSequenceID;
    ISptIMSDK _sdk;
    SptCallID _callID;

    EditText _serverView;
    EditText _sessionIdView;
    EditText _userView;
    Button _connectButton;
  //  SptCallID _callID;
    SptIMSDKApp _app;
    AlertDialog _callDialog;

    //TestConnectMeetingApplication _app;

    //ISptIMSDK _sdk;
    //TestConnectSptCallObserver _callObserver;

    class TextConnectSptIMObserver extends SptIMObserver
    {
        @Override
        public void onConnected()
        {
            runOnUiThread(new Runnable() {
                @Override
                public void run()
                {
                    if(_tokenSequenceID == null)
                    {
                      //  Intent i = new Intent(MainActivity.this, CallActivity.class);
                      //  startActivity(i);
                      //  finish();
                    }
                    else if(_sdk.areMeetingsSynchronized())
                    {
                      //  Intent i = new Intent(MainActivity.this, CallActivity.class);

                      //  i.putExtra(EXTRA_JOIN_TO_MEETING, _tokenSequenceID.intValue());
                      //  startActivity(i);
                      //  finish();
                    }
                }
            });
        }

        @Override
        public void onSchMeetingsSynchronized()
        {
          Log.v("main: ", "onSchMeetingsSynchronized");
            runOnUiThread(new Runnable() {
                @Override
                public void run()
                {
                    if(_tokenSequenceID != null)
                    {
                //        Intent i = new Intent(MainActivity.this, CallActivity.class);

                //        i.putExtra(EXTRA_JOIN_TO_MEETING, _tokenSequenceID.intValue());
                //        startActivity(i);

                  //        Intent i = new Intent(MainActivity.this, CallActivity.class);

                  //        if(_callID != null)
                  //            i.putExtra(CallActivity.EXTRA_CALL_ID, _callID.intValue());


                    //    finish();
                    }
                }
            });
        }

        @Override
        public void onDisconnected()
        {
            super.onDisconnected();
        }

        @Override
        public void onConnectionError(final ISptIMSDK.eSptConnectionResult eResult)
        {
            runOnUiThread(new Runnable() {
                @Override
                public void run()
                {
                  //  _progressView.setVisibility(View.GONE);
                    switch (eResult)
                    {
                        case eSptIMConnect_AuthError:
                  //          showToast("eSptIMConnect_AuthError");
                            break;
                        case eSptIMConnect_GDPRPending:
                    //        showGdprDialog();
                            break;
                        case eSptIMConnect_CredentialsError:
                      //      _emailView.setError("Credentials Error");
                      //      _passwordView.setError("Credentials Error");
                            break;
                        case eSptIMConnect_NetworkError:
                      //      _serverView.setError("Server Not Reachable");
                            break;
                    }
                }
            });
        }

        @Override
        public void onGetTokenDataRes(final SptTokenDataResult tokenDataRes)
        {

           Log.v("main: ", "onGetTokenDataRes");
            runOnUiThread(new Runnable() {
                @Override
                public void run()
                {
                    switch(tokenDataRes.getResult())
                    {
                        case SptTokenDataResultJoinMeeting:
                             Log.v("main: ", "SptTokenDataResultJoinMeeting");
                            _tokenSequenceID = tokenDataRes.getMeetingSequenceID();
                            if(!tokenDataRes.contactAlreadyLogged())
                                _sdk.loginWithTokenDataResult(tokenDataRes);
                            processLaunchFromToken(_tokenSequenceID);
                            break;
                        case SptTokenDataResultLogin:
                            if(!tokenDataRes.contactAlreadyLogged())
                                _sdk.loginWithTokenDataResult(tokenDataRes);
                            break;
                        case SptTokenDataResultInvalidToken:
                          //  _tokenView.setError("Invalid Token");
                          //  _progressView.setVisibility(View.GONE);
                            break;
                        case SptTokenDataResultServerNotReachable:
                          //  _passwordView.setError("Server Not Reachable");
                        //    _progressView.setVisibility(View.GONE);
                            break;
                        case SptTokenDataResultError:
                          //  showToast("SptTokenDataResultError");
                            break;
                    }

                }
            });
        }
    }

    class TestConnectSptCallObserver extends SptCallObserver
    {
        @Override
        public void onCallEventConnected(SptCallID sptCallID, ISptCallData iSptCallData) {

          Log.v("main: ", "SptCallObserver");
            runOnUiThread(new Runnable() {

                @Override
                public void run() {
                    Intent i = new Intent(MainActivity.this, CallActivity.class);
                    //_tokenSequenceID = new SptSchMeetingSequenceID();
                    if(_callID != null)
                        i.putExtra(CallActivity.EXTRA_CALL_ID, _callID.intValue());
                    startActivity(i);
                    finish();
                }
            });
        }

        @Override
        public void onCallEventDisconnected(SptCallID sptCallID, ISptCallData iSptCallData) {
            super.onCallEventDisconnected(sptCallID, iSptCallData);
        }

//        @Override
//        public void onCallEventStateUpdated(SptCallID sptCallID, ISptCallData iSptCallData) {
//            super.onCallEventStateUpdated(sptCallID, iSptCallData);
//        }

        @Override
        public void onCallEventStateUpdated(final SptCallID sptCallID, final ISptCallData iSptCallData) {
            runOnUiThread(new Runnable() {
                @Override
                public void run()
                {
                  Log.v("main: ", "SptCallObserver1");
                    if(_callID == null)
                        _callID = sptCallID;
                    Log.d("call state", iSptCallData.getCallState().name());
                    switch (iSptCallData.getCallState())
                    {

                        case eCallStateCreating:
                            showCallDialog();
                            break;
                        case eCallStateRinging:
                            break;
                        case eCallStateAccepted:
                            break;
                        case eCallStateConnecting:
                            break;
                        case eCallStateWaitingParticipants:
                            break;
                        case eCallStateReconnecting:
                            break;
                        case eCallStateConnected:
                            break;
                        case eCallStateConnectedInOtherDevice:
                            break;
                        case eCallStateDisconnecting:
                            break;
                        case eCallStateDisconnected:
                            _callID = null;
                            break;
                        case eCallStateRejected:
                            _callID = null;
                            break;
                        case eCallStateError:
                            _callID = null;
                            break;
                    }
                }
            });
        }

        @Override
        public void onCallEventIncomingCall(SptCallID sptCallID, ISptCallData iSptCallData)
        {

          Log.v("main: ", "SptCallObserver2");
            if(_callID == null)
            {
                _callID = sptCallID;
                runOnUiThread(new Runnable()
                {
                    @Override
                    public void run()
                    {
                      //  showIncomingCallDialog();
                    }
                });
            }
        }
    }

    private void processLaunchFromToken(SptSchMeetingSequenceID sequenceID)
    {
      Log.v("main: ","processLaunchFromToken");
        if(sequenceID != null && sequenceID.intValue() != SptSchMeetingSequenceID.SPT_INVALID_MEETING_SEQUENCE_ID)
        {
            ISptSchMeetingSequence seq = _sdk.getSchMeetingSequenceByID(sequenceID);
            if(seq != null)
            {
                ISptSchMeeting m = seq.getCurrentMeeting();
                if(m!= null)
                {
                  Log.v("main: ","SptSchJoinMeeting");
                    SptSchJoinMeeting joinMeeting = new SptSchJoinMeeting(sequenceID, m.getSchMeetingID(), true);
                    _sdk.joinSchMeeting(joinMeeting);
                }
            }
        }
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

      Log.v("main: ","onCreate");
      String package_name = getApplication().getPackageName();
       //String package_name = "com.stanleyidesis.cordova.plugin";
       Resources resources = getApplication().getResources();
       setContentView(resources.getIdentifier("activity_main", "layout", package_name));

       Log.v("package name: ", package_name);
      // Log.v("Resources name: ", resources.String);
       Log.v("view ID: ", String.valueOf(resources.getIdentifier("activity_main", "layout", package_name)));
    //   _sdk = ((SptIMSDKApp)getApplication()).getSptIMSDK();

      _sdk = SptIMSDKApp.getInstance().getSptIMSDK(getApplicationContext());
      //_app = SptIMSDKApp.getInstance();
      //_sdk = _app.getSptIMSDK(getApplicationContext());

      Intent intent1 = getIntent();

      String serverName = intent1.getStringExtra("serverName");
      String userMail = intent1.getStringExtra("userMail");
      String passWord = intent1.getStringExtra("passWord");
      String personalID = intent1.getStringExtra("personalID");

      Log.v("MainActivity - serverName: ", serverName);
      Log.v("MainActivity - userMail: ", userMail);
      Log.v("MainActivity - passWord: ", passWord);
      Log.v("MainActivity - personalID: ", personalID);


    //   _sdk = ((TestConnectMeetingApplication)getApplication()).getSptIMSDK();
      // _sdk = ((SptIMSDKApp)getApplication()).getSptIMSDK(getApplicationContext());
       _callObserver = new TestConnectSptCallObserver();
      _sdk.addCallObserver(_callObserver);

      _sptObserver = new TextConnectSptIMObserver();
        _sdk.addObserver(_sptObserver);





  //     _pageAdapter = new MainPagerAdapter(getSupportFragmentManager());
    //   _viewPager = findViewById(R.id.main_view_pager);
  //     _viewPager = setContentView(resources.getIdentifier("main_view_pager", "id", package_name));
  //     _viewPager.setAdapter(_pageAdapter);
  //     _tabLayout = (TabLayout)findViewById(R.id.tablayout);
  //     _tabLayout.setupWithViewPager(_viewPager);
       //undle args = getIntent().getExtras();

       //_sdk.getTokenData("43030687", "collaboratespace.net");

      // Log.v("main - oncreate ", String.valueOf(args.getInt(EXTRA_JOIN_TO_MEETING, SptSchMeetingSequenceID.SPT_INVALID_MEETING_SEQUENCE_ID)));

      _sdk.getTokenData(personalID, serverName);

    //    _sdk.getTokenData("88817741", "collaboratespace.net");

    //  Log.v("main - oncreate _tokenSequenceID", String.valueOf(_tokenSequenceID));

//       if(args != null)
//       {
//           Log.v("main: ","onCreate _tokenSequenceID");
//
//           _tokenSequenceID = new SptSchMeetingSequenceID(args.getInt(EXTRA_JOIN_TO_MEETING, SptSchMeetingSequenceID.SPT_INVALID_MEETING_SEQUENCE_ID));
//       }

Log.v("main: ","onCreate2");



Log.v("main: ","onCreat3");
//package_name = "com.stanleyidesis.cordova.plugin";

       //Intent intent = getIntent();

       //String serverName = intent.getStringExtra("serverName");
       //String sessionID = intent.getStringExtra("sessionID");
       //String userName = intent.getStringExtra("userName");

      // _sdk = ((TestConnectMeetingApplicatiogetApplication()).getSptIMSDK();
      // _sdk = ((SptIMSDKApp)getApplication()).getSptIMSDK(getApplicationContext());
      // _callObserver = new TestConnectSptCallObserver();
      //_sdk.addCallObserver(_callObserver);

    //   _app = SptIMSDKApp.getInstance();
//       _sdk = _app.getSptIMSDK(getApplicationContext());
//       _callObserver = new TestConnectSptCallObserver();
    // _sdk.addCallObserver(_callObserver);

    //   Bundle args = getIntent().getExtras();
    //   if(args != null)
    //   {
    //       _tokenSequenceID = new SptSchMeetingSequenceID(args.getInt(EXTRA_JOIN_TO_MEETING, SptSchMeetingSequenceID.SPT_INVALID_MEETING_SEQUENCE_ID));

//       }
  //     processLaunchFromToken(_tokenSequenceID);


      //  String activity_main_connect_buttonData = intent.getStringExtra("activity_main_connect_button");
      //  setContentView(R.layout.activity_main);
   //Log.v("activity_main_connect_buttonData: ", activity_main_connect_buttonData);
      //  _app = new TestConnectMeetingApplication();
      //  _app.attachBaseContext(this.getApplicationContext());
      //  _sdk = _app.getSptIMSDK(); // new
      //  _sdk = ((TestConnectMeetingApplication)getApplication()).getSptIMSDK();

      //  _serverView = (EditText)findViewById(R.id.activity_main_server);
      //  _sessionIdView = (EditText)findViewById(R.id.activity_main_id);
      //  _userView = (EditText)findViewById(R.id.activity_main_user);
      //  _connectButton = (Button)findViewById(R.id.activity_main_connect_button);

    //  String package_name1 = getApplication().getPackageName();
    //  Resources resources1 = getApplication().getResources();

      //  _serverView = (EditText)findViewById(resources1.getIdentifier("activity_main_server", "id", package_name1));
      //  _sessionIdView = (EditText)findViewById(resources1.getIdentifier("activity_main_id", "id", package_name1));
      //  _userView = (EditText)findViewById(resources1.getIdentifier("activity_main_user", "id", package_name1));
      //  _connectButton = (Button)findViewById(resources1.getIdentifier("activity_main_connect_button", "id", package_name1));

    //    _serverView.setText(serverName);
    //    _sessionIdView.setText(sessionID);
    //    _userView.setText(userName);
// Log.v("activity_main_server: ", String.valueOf(resources1.getIdentifier("activity_main_server", "layout", package_name1)));

      //  _connectButton.setOnClickListener(new View.OnClickListener() {
      //      @Override
      //      public void onClick(View v) {
      //          String server = _serverView.getText().toString();
      //          String sessionId = _sessionIdView.getText().toString();
      //          String user = _userView.getText().toString();

        //        Log.v("server: ", server);
        //        Log.v("sessionId: ", sessionId);
        //        Log.v("user: ", user);

        //        processLaunchFromToken(_tokenSequenceID);

          //      if(server.length() > 0 && sessionId.length() > 0 && user.length()>0)
            //    {

                  //  launchIntent();

              //      SptJoinCall joinCall = new SptJoinCall(user, "", sessionId, server);
              //      _callID = _sdk.joinCall(joinCall);
              //      if(_callID != null) {
              //        Log.v("one: ","call Id valid");
              //        Log.v("_callID: ",String.valueOf(_callID));
              //      }

                  //  launchIntent();
              //  }
            //}
        //});
        manageMainPermissions();
    }





    void launchIntent()
    {

    //Intent intentScan = new Intent(this, CallActivity.class);

    Intent i = new Intent(MainActivity.this, CallActivity.class);
    if(_callID != null)
        i.putExtra(CallActivity.EXTRA_CALL_ID, _callID.intValue());
    // Intent intentScan = new Intent("com.stanleyidesis.cordova.plugin.TestConnectMeetingApplication");

    //  Intent intentScan = getPackageManager().getLaunchIntentForPackage("com.clearone.testconnectmeeting");

      this.startActivity(i);

    }

  //  @Override
  //  protected void onDestroy() {
  //      super.onDestroy();
  //      _sdk.removeCallObserver(_callObserver);
  //  }

    @Override
    protected void onDestroy()
    {
        super.onDestroy();
        //_sptIMObserver = new MainActivitySptIMObserver();
        ISptIMSDK sdk = SptIMSDKApp.getInstance().getSptIMSDK(getApplicationContext());
        //sdk.removeObserver(_sptIMObserver);
        sdk.removeCallObserver(_callObserver);
    }

    private void showCallDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Call In Progress...").setPositiveButton("Hang", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
               _sdk.hangUpCall(_callID);
                _callDialog = null;
            }
        }).setCancelable(false);
        _callDialog = builder.show();
    }

    private void showIncomingCallDialog()
    {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Call In Progress...")
                .setPositiveButton("Video", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i)
                    {
                        _sdk.answerCall(_callID, true, true);
                        _callDialog = null;
                    }
                }).setNegativeButton("Audio", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
                _sdk.answerCall(_callID, true, false);
                _callDialog = null;
            }
        }).setNeutralButton("Hang", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialogInterface, int i)
            {
                _sdk.answerCall(_callID, false, true);
                _callDialog = null;
            }
        }).setCancelable(false);
        _callDialog = builder.show();
    }

    void manageMainPermissions()
    {


        ArrayList<String> permissionsArray = new ArrayList();
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.CAMERA) == PackageManager.PERMISSION_DENIED)
            permissionsArray.add(Manifest.permission.CAMERA);
        if(ContextCompat.checkSelfPermission(this, Manifest.permission.RECORD_AUDIO) == PackageManager.PERMISSION_DENIED)
            permissionsArray.add(Manifest.permission.RECORD_AUDIO);
        if(permissionsArray.size()>0)
            ActivityCompat.requestPermissions(this, permissionsArray.toArray(new String[permissionsArray.size()]),
                    REQUEST_CODE_ASK_PERMISSIONS);


    }

}

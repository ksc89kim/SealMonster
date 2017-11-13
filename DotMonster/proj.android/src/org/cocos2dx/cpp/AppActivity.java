/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;



import java.util.Hashtable;



import org.cocos2dx.lib.Cocos2dxActivity;

import android.app.ProgressDialog;
import android.content.Intent;
import android.content.IntentSender.SendIntentException;

import android.os.Bundle;
import android.util.Log;
import android.view.Gravity;
import android.view.View;
import android.view.WindowManager;
import android.widget.LinearLayout;

import com.google.android.gms.ads.*;
import com.google.android.gms.common.ConnectionResult;
import com.google.android.gms.common.GooglePlayServicesUtil;
import com.google.android.gms.common.api.GoogleApiClient;
import com.google.android.gms.common.api.GoogleApiClient.ConnectionCallbacks;
import com.google.android.gms.common.api.GoogleApiClient.OnConnectionFailedListener;
import com.google.android.gms.games.Games;
import com.google.android.gms.games.GamesActivityResultCodes;
import com.google.android.gms.plus.Plus;
import com.google.android.gms.plus.model.people.Person;
import com.tapjoy.TJActionRequest;
import com.tapjoy.TJError;
import com.tapjoy.TJPlacement;
import com.tapjoy.TJPlacementListener;
import com.tapjoy.Tapjoy;
import com.tapjoy.TapjoyConnectFlag;
import com.tapjoy.TJConnectListener;
import com.tapjoy.TJEarnedCurrencyListener;
import com.tapjoy.TJGetCurrencyBalanceListener;
import com.tapjoy.TapjoyLog;
import com.tapjoy.TJVideoListener;
import com.tronplay.dotgame.R;
import com.tronplay.etc.Helper.HelperLister;
import com.tronplay.etc.Helper;

interface GoogleType{
	public int googleLoginType = 1; 
	public int googleSubmitScore = 2;
	public int googleLeaderBoard = 3;
}

public class AppActivity extends Cocos2dxActivity implements TJGetCurrencyBalanceListener, TJPlacementListener, ConnectionCallbacks,
	OnConnectionFailedListener, HelperLister{
	
	private AdView admobView;
	private InterstitialAd interstitial = null;
	public static AppActivity  mActivity;
	LinearLayout layout;
	LinearLayout mainLayout;
	boolean isAdmobInited = false;
	private static final String AD_UNIT_ID = "ca-app-pub-4632355628993982/9398755953";
	private static final String AD_UNIT_INTER_ID = "ca-app-pub-4632355628993982/4711204353";
	
	static final String TAG = AppActivity.class.getSimpleName();
	private TJPlacement directPlayPlacement;

	private GoogleApiClient mGoogleApiClient;
    public static final int REQUEST_CODE_RESOLVE_ERR = 9000;
    public static final int REQUEST_CODE_LEADERBOARDS = 20201;
    public static final int REQUEST_CODE_ACHIEVEMENT = 20202;
    public int mGooglePlusType = 0;
    
    ProgressDialog mDialog;
    
	@Override
	protected void onCreate(final Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		mActivity = this;
		
		Helper.init(this, this);
		
		Helper.nativeCallAdmob();
		Helper.nativeCallInterstitial();
		//createAdMob("ca-app-pub-4632355628993989/9398755959");
		/** Tapjoy SDK */
		connectToTapjoy();
		Tapjoy.setUserID("TEST_SEAL_MONSTER");
		Tapjoy.setDebugEnabled(false);
		
		//google play
		checkPlayServices();
		// google plus with play setup
		mGoogleApiClient = new GoogleApiClient.Builder(this)
				.addConnectionCallbacks(this)
				.addOnConnectionFailedListener(this)
				.addApi(Plus.API, Plus.PlusOptions.builder().build())
				.addScope(Plus.SCOPE_PLUS_LOGIN).addApi(Games.API)
				.addScope(Games.SCOPE_GAMES).build();
	}
	
	
	@Override
	protected void onStart() {
		super.onStart();
		Tapjoy.onActivityStart(this);
	}
	protected void onStop() {
		super.onStart();
		Tapjoy.onActivityStop(this);
	}
	@Override
	public void onPause() {
		super.onPause();
		admobView.pause();
	}

	@Override
	public void onResume() {
		super.onResume();
		admobView.resume();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		admobView.destroy();
	}
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		/* google play */
		if ( resultCode == GamesActivityResultCodes.RESULT_RECONNECT_REQUIRED && requestCode == REQUEST_CODE_LEADERBOARDS)  { 
			mGoogleApiClient.disconnect();
		}
		else if(resultCode == GamesActivityResultCodes.RESULT_RECONNECT_REQUIRED && requestCode == REQUEST_CODE_ACHIEVEMENT)
		{
			mGoogleApiClient.disconnect();
		}
		if(requestCode == REQUEST_CODE_RESOLVE_ERR)
		 {
			 if(resultCode == RESULT_OK)
			 {
				 signInWithGplus();
			 }
			 else if(resultCode==RESULT_CANCELED)
			 {
			 }
			 else
			 {
			 }
		 }
		 /* google play */

	}
	
	public void startLoading()
	{
		if (mDialog != null) {
			return;
		}
		mDialog = ProgressDialog.show(AppActivity.this, "",
			   		"", true);
	}
	
	public void endLoading()
	{
		if (mDialog == null) {
			return;
		}
		mDialog.dismiss();
		mDialog = null;
	}
	
	/* Admob Start */
	public void createAdMob(String data) {
		
		admobView = new AdView(this);
		admobView.setAdSize(AdSize.BANNER);
		admobView.setAdUnitId(data);
		
		if (isAdmobInited || admobView == null) {
			return;
		}
		mainLayout = new LinearLayout(mActivity);
		mainLayout.post(new Runnable() {

			@Override
			public void run() {
				AdRequest adRequest = new AdRequest.Builder().build();

				WindowManager wm = (WindowManager) mActivity
						.getSystemService("window");

				WindowManager.LayoutParams mLayoutParams = new WindowManager.LayoutParams();
				mLayoutParams.type = WindowManager.LayoutParams.TYPE_APPLICATION_PANEL;
				mLayoutParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
				mLayoutParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
				mLayoutParams.flags |= WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
				mLayoutParams.gravity = Gravity.TOP;

				wm.addView(admobView, mLayoutParams);

				// Enable this if your are testing AdMob, otherwise you'll risk
				// to be banned!
				// adRequest.addTestDevice (AdRequest.TEST_EMULATOR);
				admobView.loadAd(adRequest);
				isAdmobInited = true;
			}
		});
	}
	public void createInterstitial(String data)
	{
		interstitial = new InterstitialAd(this);
		interstitial.setAdUnitId(data);
		interstitial.setAdListener(new AdListener() {
            @Override
            public void onAdClosed() {
                requestNewInterstitial();
            }
        });
		requestNewInterstitial();
	}
	
	public void requestNewInterstitial()
	{
		AdRequest adRequest = new AdRequest.Builder().build();
		interstitial.loadAd(adRequest);
	}
	
	public void setAdmob(final String data) {
		Log.d("tron", "setAdmob");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mActivity.createAdMob(data);
			}
		});
	}
	
	public void setInterstitial(final String data) {
		Log.d("tron", "setInterstitial");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mActivity.createInterstitial(data);
			}
		});
	}
	
	public void displayInterstitital() {
		Log.d("tron", "displayInterstitital");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (mActivity.interstitial != null) {
					if (mActivity.interstitial.isLoaded()) {
						mActivity.interstitial.show();
					}
				}
			}
		});
	}
	public void showAdMob() {
		Log.d("tron", "showAdMob");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (!mActivity.admobView.isEnabled())
					mActivity.admobView.setEnabled(true);
				if (mActivity.admobView.getVisibility() == 4)
					mActivity.admobView.setVisibility(View.VISIBLE);
			}
		});

	}
	public void hideAdMob() {
		Log.d("tron", "hideAdMob");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				if (mActivity.admobView.isEnabled())
					mActivity.admobView.setEnabled(false);
				if (mActivity.admobView.getVisibility() != 4)
					mActivity.admobView.setVisibility(View.INVISIBLE);
			}
		});

	}
	/* Admob End */
	
	/* TapJoy Start */
	public void showVideoStart() {
		// TODO Auto-generated method stub
		Log.d("tron", "hideAdMob");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mActivity.showVideo();
			}
		});
		//callShowOffers();
	}

	private void connectToTapjoy() {
		// OPTIONAL: For custom startup flags.
		Hashtable<String, Object> connectFlags = new Hashtable<String, Object>();
		connectFlags.put(TapjoyConnectFlag.ENABLE_LOGGING, "true");
		//Tapjoy.setGcmSender("14001875913");
		String tapjoySDKKey = "ZYivMAnrSOSW7hsrNfqy5wECsFJxGXZEPolOpfQdDcuOG5CzXgwlEjnamzub";
		//Tapjoy.setGcmSender("34027022155");
		//CT3Define.TAPJOY_APPID
		Tapjoy.connect(this.getApplicationContext(), tapjoySDKKey, connectFlags, new TJConnectListener() {
			@Override
			public void onConnectSuccess() {
				Log.d("tap joy", "onConnectSuccess");
				AppActivity.this.onConnectSuccess();
			}

			@Override
			public void onConnectFailure() {
				Log.d("-", "onConnectFailure");
			}
		});
	}

	
	public void showVideo() {
		directPlayPlacement = new TJPlacement(this, "video", new TJPlacementListener() {
	          @Override
	          public void onRequestSuccess(TJPlacement placement) {
		           TapjoyLog.i(TAG, "Success");

	             if (!placement.isContentAvailable()) {
	            	 	Helper.nativeVideoNotContent();
			 			Log.d("tap joy", "video isContentAvailable1");
	               }

		 			Log.d("tap joy", "video isContentAvailable2");

	          }
	          @Override
	          public void onRequestFailure(TJPlacement placement, TJError error) {
		 			Log.d("tap joy", "onRequestFailure"+ error);
		 			Helper.nativeVideoFail();
	          }

	          @Override
	          public void onContentReady(TJPlacement placement) {
	 			Log.d("tap joy", "onContentReady for pl"+ placement.getName());
				placement.showContent();
	          }

	          @Override
	          public void onContentShow(TJPlacement placement) {
	 			Log.d("tap joy", "video onContentShow");
	             TapjoyLog.i(TAG, "onContentShow for placement " + placement.getName());
	            
	          }
	          @Override
	          public void onContentDismiss(TJPlacement placement) {
	        	  Log.d("tap joy", "video onContentDismiss");
	             TapjoyLog.i(TAG, "onContentDismiss for placement " + placement.getName());
	             //  CT3Helper.nativeEndTapjoyVideo();
	          }

	          @Override
	          public void onPurchaseRequest(TJPlacement placement, TJActionRequest request, String productId) {
		 			Log.d("tap joy", "video onPurchaseRequest");
	          }

	          @Override
	          public void onRewardRequest(TJPlacement placement, TJActionRequest request, String itemId, int quantity) {
		 			Log.d("tap joy", "video onRewardRequest");
	          }
	      });
		directPlayPlacement.requestContent();
	}
	
	public  void tapJoyViedoConnect() {
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Helper.nativeTapJoyConnect(mActivity.interstitial.getAdUnitId());
			}
		});
	}
	
	public void onConnectSuccess() {

		Tapjoy.setEarnedCurrencyListener(new TJEarnedCurrencyListener() {
			@Override
			public void onEarnedCurrency(String currencyName, int amount) {
			}
		});
		// Setup listener for Tapjoy video callbacks
		Tapjoy.setVideoListener(new TJVideoListener() {
			@Override
			public void onVideoStart() {
				Log.i(TAG, "video has started");
				
			}

			@Override
			public void onVideoError(int statusCode) {
				Helper.nativeVideoFail();
	 			Log.d("tap joy", "there was an error with the video: " + statusCode);
				Log.i(TAG, "there was an error with the video: " + statusCode);
			}

			@Override
			public void onVideoComplete() {
	 			Log.d("tap joy", "video has completed");
	 			Helper.nativeVideoSuccess();
				// Best Practice: We recommend calling getCurrencyBalance as often as possible so the user�뜝�릯 balance is always up-to-date.
				Tapjoy.getCurrencyBalance(AppActivity.this);
			}
		});
	}

	
	@Override
	public void onContentDismiss(TJPlacement arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onContentReady(TJPlacement arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onContentShow(TJPlacement arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onPurchaseRequest(TJPlacement arg0, TJActionRequest arg1,
			String arg2) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onRequestFailure(TJPlacement arg0, TJError arg1) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onRequestSuccess(TJPlacement arg0) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onRewardRequest(TJPlacement arg0, TJActionRequest arg1,
			String arg2, int arg3) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onGetCurrencyBalanceResponse(String arg0, int arg1) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void onGetCurrencyBalanceResponseFailure(String arg0) {
		// TODO Auto-generated method stub
		
	}
	/* TapJoy End */
	
	/* Google Play Start */
	
	private boolean checkPlayServices() {
		int resultCode = GooglePlayServicesUtil
				.isGooglePlayServicesAvailable(this);
		if (resultCode != ConnectionResult.SUCCESS) {
			if (GooglePlayServicesUtil.isUserRecoverableError(resultCode)) {
				GooglePlayServicesUtil.getErrorDialog(resultCode, this,
						REQUEST_CODE_RESOLVE_ERR).show();
			} else {
				finish();
			}
			return false;
		}
		return true;
	}
	
	public void loginGoogle() {
		Log.d("tron", "loginGoogle");
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mActivity.mGooglePlusType = GoogleType.googleLoginType;
				mActivity.signInWithGplus();
			}
		});
	}
	
	public void submitGoogleScore(final int score) {
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mActivity.mGooglePlusType = GoogleType.googleSubmitScore;
				mActivity.submitScore(score);
			}
		});
	}
	public void showLeaderBoard() {
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				mActivity.mGooglePlusType = GoogleType.googleLeaderBoard;
				mActivity.leaderboardsActivity();
			}
		});
	}
	public void googleService() {
		mActivity.runOnUiThread(new Runnable() {
			@Override
			public void run() {
				Helper.nativeGoogleService(mActivity.admobView.getAdUnitId());
			}
		});
	}
	
	@Override
	public void onConnectionFailed(ConnectionResult result) {
		// TODO Auto-generated method stub
		if (!result.hasResolution()) {
			GooglePlayServicesUtil.getErrorDialog(result.getErrorCode(), this,
					0).show();
			return;
		} else {
			try {
				result.startResolutionForResult(this,0);
			} catch (SendIntentException e) {
				mGoogleApiClient.connect();
			}
		}
	}

	@Override
	public void onConnected(Bundle arg0) {
		// TODO Auto-generated method stub
		getProfileInformation();
	}

	@Override
	public void onConnectionSuspended(int arg0) {
		// TODO Auto-generated method stub
		mGoogleApiClient.connect();
	}

	public void getProfileInformation() {
		try {
			if (Plus.PeopleApi.getCurrentPerson(mGoogleApiClient) != null) {
				Person currentPerson = Plus.PeopleApi
						.getCurrentPerson(mGoogleApiClient);
				String personId = currentPerson.getId();
				switch(mGooglePlusType)
				{
				case GoogleType.googleLoginType:
					break;
				case GoogleType.googleSubmitScore:
					break;
				case GoogleType.googleLeaderBoard:
					leaderboardsActivity();
					break;
				}
			} else {
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void signInWithGplus() {
		if (!mGoogleApiClient.isConnected())
			mGoogleApiClient.connect();
		else {
			getProfileInformation();
		}
	}
	

	public void signOutFromGplus() {
		if (mGoogleApiClient.isConnected()) {
			Plus.AccountApi.clearDefaultAccount(mGoogleApiClient);
			Games.signOut(mGoogleApiClient);
			mGoogleApiClient.disconnect();
		}
	}

	public void submitScore(int score) {
		if (mGoogleApiClient.isConnected()) {
			Games.Leaderboards.submitScore(mGoogleApiClient,
					this.getString(R.string.leaderboard_sealmonster), score);
		}
	}


	public void leaderboardsActivity() {
		if (mGoogleApiClient.isConnected()) {
			startActivityForResult(Games.Leaderboards.getLeaderboardIntent(
					mGoogleApiClient, getString(R.string.leaderboard_sealmonster)),
					REQUEST_CODE_LEADERBOARDS);
		}
		else
		{
			signInWithGplus();
		}
	}

	
	/* Google Play End */
}

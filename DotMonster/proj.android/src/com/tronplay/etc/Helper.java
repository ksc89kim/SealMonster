package com.tronplay.etc;


import android.content.Context;

public class Helper {
	private static Context mContext = null;
	private static HelperLister mHelperLister;
	
	// ===========================================================
	// Constructors
	// ===========================================================
	public static void init(final Context pContext, final HelperLister pHelperListener) {
		mContext = pContext;
		mHelperLister = pHelperListener;
	}

	public static void setAdmob(final String data) {
		mHelperLister.setAdmob(data);
	}
	
	public static void setInterstitial(final String data) {
		mHelperLister.setInterstitial(data);
	}
	
	public static void displayInterstitital() {
		mHelperLister.displayInterstitital();
	}
	public static void showAdMob() {
		mHelperLister.showAdMob();
	}
	public static void hideAdMob() {
		mHelperLister.hideAdMob();
	}
	public static void showVideoStart() {
		mHelperLister.showVideoStart();
	}
	public static void tapJoyViedoConnect() {
		mHelperLister.tapJoyViedoConnect();
	}
	
	public static void loginGoogle() {
		mHelperLister.loginGoogle();
	}
	
	public static void submitGoogleScore(final int score) {
		mHelperLister.submitGoogleScore(score);
	}
	public static void showLeaderBoard() {
		mHelperLister.showLeaderBoard();
	}
	public static void googleService() {
		mHelperLister.googleService();
	}
	public static native void nativeGoogleService(String service);
	public static native void nativeVideoSuccess();
	public static native void nativeVideoFail();
	public static native void nativeVideoNotContent();
	public static native void nativeTapJoyConnect(String connectData);
	public static native void nativeCallAdmob();
	public static native void nativeCallInterstitial();
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
	
	public static interface HelperLister {
		public void setAdmob(final String data);
		public void setInterstitial(final String data);
		public void displayInterstitital();
		public void showAdMob();
		public void hideAdMob();
		public void showVideoStart();
		public void tapJoyViedoConnect();
		public void loginGoogle();
		public void submitGoogleScore(final int score);
		public void showLeaderBoard();
		public void googleService(); 
	}
}

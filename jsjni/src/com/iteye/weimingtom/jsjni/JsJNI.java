package com.iteye.weimingtom.jsjni;

import android.content.Context;

public class JsJNI {
	private static final boolean D = true;
	private static final String TAG = "JsJNI";
	
	public native int exec(String filename);
	
	static {
		System.loadLibrary("application");
	}
	
	private Context mContext;
	
	public JsJNI(Context context) {
		this.mContext = context;
	}
}

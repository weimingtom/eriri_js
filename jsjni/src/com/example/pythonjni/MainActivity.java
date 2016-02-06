package com.example.pythonjni;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import com.example.jsjni.R;
import com.iteye.weimingtom.jsjni.JsJNI;

public class MainActivity extends Activity {
	private static final String TAG = "MainActivity";
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.setContentView(R.layout.main);
		JsJNI python = new JsJNI(this);
		Log.e(TAG, "python.exec return : " + python.exec("test_fib.rb"));
	}
}

package com.master.trival;

import android.graphics.PixelFormat;
import android.os.Bundle;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;

import androidx.appcompat.app.AppCompatActivity;


/**
 * Created by Mao on 17/7/18.
 */
public class MainActivity extends AppCompatActivity implements SurfaceHolder.Callback {

    static {
        System.loadLibrary("ffmpeg");
        System.loadLibrary("triangle");
    }

    SurfaceView mSurfaceView;
    PlayRender mPlayRender;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method

        mSurfaceView = findViewById(R.id.surfaceview);
        mSurfaceView.getHolder().setFormat(PixelFormat.TRANSPARENT);
        mSurfaceView.setZOrderOnTop(true);
        mSurfaceView.getHolder().addCallback(this);
        mPlayRender = new PlayRender();

        TextView test = findViewById(R.id.tv_test);
        test.setText(avcodecinfo());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public static native String avcodecinfo();

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        mPlayRender.init();
        mPlayRender.setSurface(holder.getSurface());
    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        mPlayRender.resetSize(width, height);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
        mPlayRender.stop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mPlayRender.stop();
    }
}

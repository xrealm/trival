package com.master.trival;

import android.view.Surface;

/**
 * Created by Mao on 6/7/18.
 */
public class PlayRender {

    public native void init();

    public native void setSurface(Surface surface);

    public native void resetSize(int width, int height);

    public native void stop();
}

package com.example.player1;

import android.view.Surface;

/**
 *
 */
public class Player {

    static {
        System.loadLibrary("native-lib");
    }

    public native void playVideo(Surface surface);
}

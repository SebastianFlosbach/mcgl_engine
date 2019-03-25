public class MCGLEngineInterface {
    static{
        System.loadLibrary("mcgl-engine");
        System.loadLibrary("mcgl_engine_java");
    }

    public native void createEngine();
    public native void destroyEngine();

    public native void createWindow( int width, int height, String title );

    public native void run();
    public native void stop();

    private IKeyEventCallback keyEventCallback;
    public void registerKeyEventCallback( IKeyEventCallback callback ){
        keyEventCallback = callback;
    }
    private native void registerKeyEventCallback( String callbackName );


    public native void registerMouseEventCallback();
}

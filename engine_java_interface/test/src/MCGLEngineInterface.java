public class MCGLEngineInterface {
    static{
        System.loadLibrary("mcgl-engine");
        System.loadLibrary("mcgl-engine-java");
    }

    public native void createEngine();
    public native void destroyEngine();

    public native void createWindow( int width, int height, String title );

    public native void run();
    public native void stop();

    private IKeyEventCallback keyEventCallback;
    private void keyEventCallback( KeyEvent event ){
        if( keyEventCallback != null ){
            keyEventCallback( event );
        }
    }
    public void registerKeyEventCallback( IKeyEventCallback callback ){
        keyEventCallback = callback;
        registerKeyEventCallback( "keyEventCallback" );
    }
    private native void registerKeyEventCallback( String callbackName );


    public native void registerMouseEventCallback();
}

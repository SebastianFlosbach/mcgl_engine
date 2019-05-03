public class Main {

    public static void main( String[] args ){
        MCGLEngineInterface engine = new MCGLEngineInterface();
        engine.createEngine();
        engine.createWindow( 800, 600, "MCGL test java");
        engine.registerKeyEventCallback( new KeyEventHandler() );
        engine.run();
    }
}

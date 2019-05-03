public class KeyEventHandler implements IKeyEventCallback {
    public void keyEventCallback( KeyEvent event ){
        System.out.println( event.type );
    }
}

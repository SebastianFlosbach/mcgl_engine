public final class KeyEvent {
    public KeyEvent( KeyEventType type, int key, double timePressed ){
        this.type = type;
        this.key = key;
        this.timePressed = timePressed;
    }

    public final KeyEventType type;
    public final int key;
    public final double timePressed;
}

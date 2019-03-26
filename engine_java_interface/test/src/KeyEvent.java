public final class KeyEvent {
    public KeyEvent( KeyEventType type, int key, double timePressed ){
        this.type = type;
        this.key = key;
        this.timePressed = timePressed;
    }

    public KeyEventType type;
    public int key;
    public double timePressed;
}

public class KeyEvent {
    public enum KeyEventType{
        Pressed,
        Down,
        Released
    }

    public KeyEventType type;
    public int key;
    public double timePressed;
}

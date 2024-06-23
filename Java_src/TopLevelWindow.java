import java.awt.*;
import javax.swing.*;

public class TopLevelWindow
{
    private static void createWindow()
    {
        JFrame frame = new JFrame("Silly little window");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel textLabel = new JLabel("Hi! Am a silly label! :P", SwingConstants.CENTER);
        textLabel.setPreferredSize(new Dimension(300, 100));
        frame.getContentPane().add(textLabel, BorderLayout.CENTER);

        frame.setLocationRelativeTo(null);
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args)
    {
        createWindow();
        NativeMethods.Test();
        NativeMethods.TestFunction();
    }
}
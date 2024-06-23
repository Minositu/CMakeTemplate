import java.awt.*;
import javax.swing.*;

public class TopLevelWindow
{
    private static void createWindow()
    {
        JFrame frame = new JFrame("CMakeExample");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JLabel textLabel = new JLabel("Hello CMake!", SwingConstants.CENTER);
        textLabel.setPreferredSize(new Dimension(450, 450));
        frame.getContentPane().add(textLabel, BorderLayout.WEST);

        frame.setLocationRelativeTo(null);
        frame.pack();
        frame.setVisible(true);
    }

    public static void main(String[] args)
    {
        createWindow();
        String OS;
        int test = 0;
        OS = System.getProperty("os.name");
        if (OS.contains("Windows"))
        {
            System.out.println("Current OS is " + OS);
            System.out.println("Working Directory = " + System.getProperty("user.dir"));
            System.setProperty("java.library.path", System.getProperty("user.dir"));
            System.loadLibrary("libMySuperStaticLibrary");
        }
        else
        {
            System.out.println("Current OS is " + OS);
            System.loadLibrary("MySuperStaticLibrary");
        }
        
        NativeMethods.Test();
        System.out.println("JAVA Pre-result is: " + test);
        test = NativeMethods.TestFunction(test);
        System.out.println("JAVA Result is: " + test);
    }
}
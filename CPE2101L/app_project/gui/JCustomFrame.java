// Template class for all frames in the system

package gui;

import java.awt.*;
import javax.swing.*;

import group.*;
import indiv.Transaction;

public class JCustomFrame extends JFrame {
    protected JCustomFrame parentFrame;

    // Saving constructor arguments to class
    protected Contacts contacts;
    protected Stock stock;
    protected History history;
    protected Transaction cart;

    public JCustomFrame(String menuTitle) {
        // Defaults of all frames in the system
        super("Sari-sari Store Management System");
        setSize(Theme.WIDTH, Theme.HEIGHT);
        setResizable(false);
        setAlwaysOnTop(true);
        setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
        
        // Opens the frame at the center of the screen
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        int x = (screenSize.width - Theme.WIDTH) / 2;
        int y = (screenSize.height - Theme.HEIGHT) / 2;
        setLocation(x, y);
        
        // Set layout of frame as BorderLayout
        Container con = getContentPane();
        con.setLayout(new BorderLayout());

        // Create a label with the menu title at top-center of the frame
        JLabel label = new JLabel(menuTitle);
        label.setFont(Theme.HEADER1_FONT);
        label.setHorizontalAlignment(SwingConstants.CENTER);
        con.add(label, BorderLayout.NORTH);     // Add the label to the top of the frame
    }

    // To be overridden by subclasses
    public void updateText() {
        throw(new UnsupportedOperationException("Method not implemented"));
    }

    public void returnToMenu() {
        throw new UnsupportedOperationException("Unimplemented method 'returnToMenu'");
    }
}
import group.*;
import gui.*;
import indiv.*;

public class sariSariManager{
    // "boostrapping"
    // functionality is in JMainMenu.java
    public static void main(String[] args) {
        // declarations and initializations
        Contacts contacts = new Contacts();
        History history = new History();
        Stock stock = new Stock(); 
        
        // load from files
        contacts.fromFile();            // (Contacts.java)
        history.fromFile();             // (History.java)
        stock.fromFile();               // (Stock.java)        
        
        // If no logs were loaded, add a new log for the first day
        if (history.isEmpty()) {        
            history.add(new Log());
        }

        // GUI initialization
        JMainMenu mainMenu = new JMainMenu(history, stock, contacts);
        mainMenu.updateText();
        mainMenu.setVisible(true);

        // debugging code
        System.out.println(contacts);
        System.out.println(stock);
        System.out.println(history);
        System.out.println(stock.lowInventoryNotifier());
    }
}

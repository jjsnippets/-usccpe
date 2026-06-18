// Class which contains a financial report / summary for a single day
// History.java keeps track of all logs

package indiv;

public class Log {
    private double totalPayment;
    private double totalWorth;

    public Log(){
        this.setTotalPayment(0);
        this.setTotalWorth(0);
    }

    public Log(double totalPayment, double totalWorth){
        this.setTotalPayment(totalPayment);
        this.setTotalWorth(totalWorth);
    }

    public double getTotalPayment() { return this.totalPayment; }
    public void setTotalPayment(double totalPayment){ this.totalPayment = totalPayment;}
    public void incTotalPayment(double totalPayment){ this.totalPayment = this.totalPayment + totalPayment;}
    
    public double getTotalWorth() { return this.totalWorth; }
    public void setTotalWorth(double totalWorth){ this.totalWorth = Math.max(0, totalWorth);}
    public void incTotalWorth(double totalWorth){ this.totalWorth = Math.max(0, this.totalWorth + totalWorth);}

    public double getRevenue(){ return this.totalPayment - this.totalWorth; }

    public void addTransaction(Transaction transaction) {
        this.totalPayment += transaction.getPayment();
        this.totalWorth += transaction.getWorth();
    }
}

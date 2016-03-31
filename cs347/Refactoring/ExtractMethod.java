/*
 *   Version 1
 *
 *   Name is "printAmountOwed" but method (1) prints and
 *   (2) calculates for (3) both current and prior orders.
 *
 *
 */

/**
 * Prints a title for a customer owing something
 */
public void printAmountOwedTitle(){
    System.out.println("***********************");
    System.out.println("***  Customer owes  ***");
    System.out.println("***********************");
}

/**
 * Given an enumeration of orders, return the sum of the outstanding balances
 * @param e         An enumeration of orders
 * @return          The sum of outstanding balances
 */
public double getOurstanding(Enumeration e){
    double outstanding = 0.0;
    while(e.hasMoreElements()){
        Order order = (Order) e.nextElement();
        outstanding += order.getAmount();
    }
    return outstanding;
}

/**
 * Prints out the name and amount owed
 * @param name      The account name
 * @param amount    The total amount to display
 */
public void printInfo(String name, double amount){
    System.out.println("name: " + name);
    System.out.println("amount: " + amount);
}

/**
 * Given the balance on an account, print out what the customer owes, taking outstanding balance into account
 * @param balance       The current balance on the account
 */
 void printAmountOwed(double balance) {
     printAmountOwedTitle();

     Enumeration e = _orders.elements();
     double outstanding = getOutstanding(e);

     printInfo(_namname, (balance+outstanding));
 }



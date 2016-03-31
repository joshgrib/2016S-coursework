abstract class Customer {
    private double _price;

    private double costFactor;
    private double taxFactor;

    public Customer(double costFactor, double taxFactor){
        this.costFactor = costFactor;
        this.taxFactor = taxFactor;
    }

    //Use the values set by the subclasses to calculate the value
    public double totalDue(){
        double cost = _price * costFactor;
        double tax = cost * taxFactor;
        return cost + tax;
    }
}
​
//Individual and Business subclasses declare constants
//and call the superclass constructor to set field values
class Individual extends Customer {
    private static final double COST_FACTOR = 1.0;
    private static final double TAX_FACTOR = 0.035;
​
    public Individual(){
        super(COST_FACTOR, TAX_FACTOR);
    }
}
class Business extends Customer {
    private static final double COST_FACTOR = 0.90;
    private static final double TAX_FACTOR = 0.07;
​
    public Business(){
        super(COST_FACTOR, TAX_FACTOR);
    }

}

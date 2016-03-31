abstract class Employee {
    private int _type;               //  the "type code" field
    private int _monthlySalary;

    double payAmount() {
        return monthlySalary;
    }
}

public class Engineer extends Employee{

    Employee(monthlySalary){
        _type = 0;
        _monthlySalary = monthlySalary;
    }
}

public class Salesman extends Employee{

    private int _commission;

    Employee(monthlySalary, commission){
        _type = 1;
        _monthlySalary = monthlySalary;
        _commission = commission;
    }

    //returns monthly salary + commission
    @Override
    double payAmount(){
        return _monthlySalary + _commission;
    }
}

public class Manager extends Employee{

    private int _bonus;

    Employee(monthlySalary, bonus){
        _type = 2;
        _monthlySalary = monthlySalary;
        _bonus = bonus;
    }
    //returns monthly salary + bonus
    @Override
    double payAmount(){
        return _monthlySalary + _bonus;
    }
}

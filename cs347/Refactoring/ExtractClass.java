class phoneNumber {
    private String _officeAreaCode;
    private String _officeNumber;
​
    public phoneNumber(String area_code, String number)
    {
        _officeAreaCode = area_code;
        _officeNumber = number;
    }
​
    public String toString()
    {
        return "(" + _officeAreaCode + ") " + _officeNumber;
    }
}
​
class Person {
    private String _name;
    phoneNumber phone;
​
    public Person(String name, String area_code, String number)
    {
        _name = name;
        phone = phoneNumber(area_code, number);
    }
    public String getName() {
        return _name;
    }
​
    public String getPhoneNumber() {
       return phone.toString();
    }
}

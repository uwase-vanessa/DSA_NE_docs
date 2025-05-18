#include <iostream>
using namespace std;


// Class and Object

class Car {
public:
    string brand;
    int year;

    void display() {
        cout << "Brand: " << brand << ", Year: " << year << endl;
    }
};



// Encapsulation (Hiding internal details and exposing necessary details)
class Student {
private:
    int age; // hidden

public:
    void setAge(int a) {
        if (a > 0)
            age = a;
    }

    int getAge() {
        return age;
    }
};



// Inheritance
class Animal {
public:
    void speak() {
        cout << "Animal speaks" << endl;
    }
};

class Dog : public Animal {
public:
    void bark() {
        cout << "Dog barks" << endl;
    }
};


// Compile time Polymorphism 

class Print {
public:
    void show(int a) {
        cout << "Integer: " << a << endl;
    }

    void show(string s) {
        cout << "String: " << s << endl;
    }
};

// Runtime polymorphism

class Mammal {
public:
    virtual void sound() {
        cout << "Animal sound" << endl;
    }
};

class Cat : public Mammal {
public:
    void sound() override {
        cout << "Meow" << endl;
    }
};

//Abstraction

class Shape {
public:
    virtual void draw() = 0; 
};

class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing Circle" << endl;
    }
};



int main() {
    Car myCar; // object
    myCar.brand = "Toyota";
    myCar.year = 2020;

    myCar.display(); // calling method ;
    
    //Encapsulation
    Student s;
    s.setAge(20);
    cout << "Student Age: " << s.getAge() << endl;
    
    // inheritance
    Dog d;
    d.speak(); // inherited from Animal
    d.bark();  // own method
  
    
    //compile polymorphism (method overloading)
    Print p;
    p.show(5);
    p.show("Hello");
 
    
    // runtime polymorphism
    
    Mammal* a;
    Cat c;
    a = &c;
    a->sound();

    
    // Abtraction
    
    Shape* shape = new Circle();
    shape->draw(); // abstraction in action
    delete shape;
    return 0;
    

}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Coordinates {
private:
    int x;
    int y;

public:
    Coordinates(int x, int y) : x(x), y(y) {}

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }
    double distance(const Coordinates& p) const {
        int dx = p.x - x;
        int dy = p.y - y;
        return sqrt(dx * dx + dy * dy);
    }
    void translate(int dx, int dy) {
        x = x + dx;
        y = y + dy;
    }
    void scale(int factor, bool sign) {
        if (sign) {
            x = x * factor;
            y = y * factor;
        } else {
            x = x/factor;
            y = y/factor;
        }
    }
    string display() const {
        return "X = " + to_string(x) + ", Y = " + to_string(y);
    }
};
class Shape {
public:
    Coordinates position;
    int sides;

    Shape(int noOfSides, const Coordinates& coord) : position(coord), sides(noOfSides) {}

    Coordinates getCoordinates() const {
        return position;
    }
    int getSides() const {
        return sides;
    }
    void setCoordinates(const Coordinates& newCoord) {
        position = newCoord;
    }
    void translate(int dx, int dy) {
        position.translate(dx, dy);
    }
    virtual void scale(int factor, bool sign) {
        position.scale(factor, sign);
    }
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual string display() const = 0;
};
class Rectangle : public Shape {
private:
    int width;
    int length;

public:
    Rectangle(const Coordinates& coord, int width, int length)
        : Shape(4, coord), width(width), length(length) {}

    double getArea() const override {
        return width * length;
    }
    double getPerimeter() const override {
        return 2 * (width + length);
    }

  string display() const override {
        return "Rectangle\nCoordinates: " + position.display() +
               "\nWidth: " + to_string(width) +
               "\nLength: " + to_string(length) +
               "\nArea: " + to_string(getArea()) +
               "\nPerimeter: " + to_string(getPerimeter());
    }
};

class Square : public Shape {
private:
    int side;

public:
    Square(const Coordinates& coord, int side)
        : Shape(4, coord), side(side) {}

    double getArea() const override {
        return side * side;
    }

    double getPerimeter() const override {
        return 4 * side;
    }

   string display() const override {
        return "Square\nCoordinates: " + position.display() +
               "\nSide: " + to_string(side) +
               "\nArea: " + to_string(getArea()) +
               "\nPerimeter: " + to_string(getPerimeter());
    }
};

class Circle : public Shape {
private:
    int radius;

public:
    Circle(const Coordinates& coord, int radius)
        : Shape(0, coord), radius(radius) {}

    double getArea() const override {
        return 3.142 * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * 3.142 * radius;
    }

    string display() const override {
        return "Circle\nCoordinates: " + position.display() +
               "\nRadius: " + to_string(radius) +
               "\nArea: " + to_string(getArea()) +
               "\nPerimeter: " + to_string(getPerimeter());
    }
};

class Triangle : public Shape {
private:
    Coordinates vertex1;
    Coordinates vertex2;
    Coordinates vertex3;

public:
    Triangle(const Coordinates& v1, const Coordinates& v2, const Coordinates& v3)
        : Shape(3, v1), vertex1(v1), vertex2(v2), vertex3(v3) {}

    double getArea() const override {
        double a = vertex1.distance(vertex2);
        double b = vertex2.distance(vertex3);
        double c = vertex3.distance(vertex1);
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double getPerimeter() const override {
        return vertex1.distance(vertex2) + vertex2.distance(vertex3) + vertex3.distance(vertex1);
    }

    string display() const override {
        return "Triangle\nCoordinates:\nVertex 1: " + vertex1.display() +
               "\nVertex 2: " + vertex2.display() +
               "\nVertex 3: " + vertex3.display() +
               "\nArea: " + to_string(getArea()) +
               "\nPerimeter: " + to_string(getPerimeter());
    }
};

class ShapeList {
private:
    vector<Shape*> listOfShapes;

public:
    void addShape(Shape* shape) {
        listOfShapes.push_back(shape);
    }
    void translateShapes(int dx, int dy) {
        for (Shape* shape : listOfShapes) {
            shape->translate(dx, dy);
        }
    }

    Shape * getShape(int pos) const {
        if (pos >= 0 && pos < listOfShapes.size()) {
            return listOfShapes[pos];
        }
        return nullptr;
    }

    Shape* removeShape(int pos) {
        if (pos >= 0 && pos < listOfShapes.size()) {
            Shape * shape = listOfShapes[pos];
            listOfShapes.erase(listOfShapes.begin() + pos);
            return shape;
        }
        return nullptr;
    }

    double area(int pos) const {
        Shape * shape = getShape(pos);
        if (shape) {
            return shape->getArea();
        }
        return 0;
    }

    void scale(int factor, bool sign) {
        for (Shape* shape : listOfShapes) {
            shape->scale(factor, sign);
        }
    }
    double perimeter(int pos) const {
        Shape* shape = getShape(pos);
        if (shape) {
            return shape->getPerimeter();
        }
        return 0;
    }
    string display() const {
        string result;
        for (Shape* shape : listOfShapes) {
            result += shape->display() + "\n\n";
        }
        return result;
    }
    int getNumberOfShapes() const {
        return listOfShapes.size();
    }
};
class ShapeManagement {
private:
    ShapeList shapeList;
public:
    void run() {
        int choice;
        do {
            cout << "1: Add a shape" << endl;
            cout << "2: Remove a shape by position" << endl;
            cout << "3: Get information about a shape by position" << endl;
            cout << "4: Area and perimeter of a shape by position" << endl;
            cout << "5: Display information of all the shapes" << endl;
            cout << "6: Translate all the shapes" << endl;
            cout << "7: Scale all the shapes" << endl;
            cout << "0: Quit program" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addShape();
                    break;
                case 2:
                    removeShape();
                    break;
                case 3:
                    getShapeInfo();
                    break;
                case 4:
                    getAreaAndPerimeter();
                    break;
                case 5:
                    displayShapes();
                    break;
                case 6:
                    translateShapes();
                    break;
                case 7:
                    scaleShapes();
                    break;
                case 0:
                    cout << "Program Exited!" << endl;
                    break;
                default:
                    cout << "Invalid Input." << endl;
            }
        } while (choice != 0);
    }
    void addShape() {
        int choice;
        cout << "Select a shape to add:" << endl;
        cout << "1: Rectangle" << endl;
        cout << "2: Square" << endl;
        cout << "3: Circle" << endl;
        cout << "4: Triangle" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        int x=0, y= 0;
        cout << "Enter the coordinates x:";
        cin >> x;
        cout << "Enter the coordinates y:";
        cin >> y;
        Coordinates coord(x, y);

        Shape* shape = nullptr;
        switch (choice) {
            case 1: {
                int width, length;
                cout << "Enter the width and length: ";
                cin >> width >> length;
                shape = new Rectangle(coord, width, length);
                break;
            }
            case 2: {
                int side;
                cout << "Enter the side length: ";
                cin >> side;
                shape = new Square(coord, side);
                break;
            }
            case 3: {
                int radius;
                cout << "Enter the radius: ";
                cin >> radius;
                shape = new Circle(coord, radius);
                break;
            }
            default:
                cout << "Invalid choice. Shape not added." << endl;
                return;
        }
        shapeList.addShape(shape);
        cout << "Shape added successfully!" << endl;
    }
    void removeShape() {
        int pos;
        cout << "Enter the position of the shape to remove: ";
        cin >> pos;

        Shape * shape = shapeList.removeShape(pos);
        if (shape) {
            delete shape;
            cout << "Shape removed successfully!" << endl;
        } else {
            cout << "Invalid position. Shape not removed." << endl;
        }
    }
    void getShapeInfo() {
        int pos;
        cout << "Enter the position of the shape to get information: ";
        cin >> pos;

        Shape* shape = shapeList.getShape(pos);
        if (shape) {
            cout << shape->display() << endl;
        } else {
            cout << "Invalid position. Shape not found." << endl;
        }
    }
    void getAreaAndPerimeter() {
        int pos;
        cout << "Enter the position of the shape to calculate area and perimeter: ";
        cin >> pos;

        double area = shapeList.area(pos);
        double perimeter = shapeList.perimeter(pos);

        if (area > 0 && perimeter > 0) {
            cout << "Area: " << area << endl;
            cout << "Perimeter: " << perimeter << endl;
        } else {
            cout << "There's no shape on the given coordinates!" << endl;
        }
    }
    void displayShapes() {
        cout << shapeList.display() << endl;
    }
    void translateShapes() {
        int dx, dy;
        cout << "Enter the translation values (dx): ";
        cin >> dx;
        cout << "Enter the translation values (dy): ";
        cin >> dy;

        shapeList.translateShapes(dx, dy);
        cout << "Shapes translated!" << endl;
    }
    void scaleShapes() {
        int factor;
        bool sign;
        cout << "Enter the scaling factor: ";
        cin >> factor;
        cout << "Enter the scaling sign (0 to Decrease, 1 to Increase): ";
        cin >> sign;

        shapeList.scale(factor, sign);
        cout << "Shapes scaled successfully!" << endl;
    }
};
int main() {
    ShapeManagement sm;
    sm.run();
    return 0;
}

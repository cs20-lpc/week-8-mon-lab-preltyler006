// lab09-main.cpp
#include "ArrayStack.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

template <typename T>
void printStack(const ArrayStack<T>& s, const string& name) {
    ArrayStack<T> copy = s;  // copy so we can pop without mutating original
    cout << name << " [top->bottom] (len=" << copy.getLength()
         << "/" << copy.getMaxSize() << "): ";
    if (copy.isEmpty()) {
        cout << "<empty>" << endl;
        return;
    }
    while (!copy.isEmpty()) {
        cout << copy.peek();
        copy.pop();
        if (!copy.isEmpty()) cout << ' ';
    }
    cout << endl;
}

void expect(bool cond, const string& msg) {
    cout << (cond ? "[OK]   " : "[FAIL] ") << msg << endl;
}

int main() {
    // --- 1) Construct with capacity and basic pushes ---
    ArrayStack<int> a(5);
    expect(a.isEmpty(), "New stack starts empty");
    expect(!a.isFull(), "New stack is not full");
    for (int i = 1; i <= 5; ++i) a.push(i);  // top=5
    printStack(a, "A");
    expect(a.getLength() == 5, "Length after 5 pushes is 5");
    expect(a.isFull(), "Stack becomes full at capacity");

    // --- 2) Overflow should throw ---
    try {
        a.push(99);
        cout << "[FAIL] Expected overflow on push to full stack\n";
    } catch (const overflow_error& e) {
        cout << "[OK]   Caught overflow: " << e.what() << endl;
    } catch (const exception& e) {
        cout << "[OK]   Caught exception: " << e.what() << endl;
    }

    // --- 3) Peek and Pop ---
    expect(a.peek() == 5, "Peek returns top element (5)");
    a.pop(); // remove 5, new top=4
    expect(a.peek() == 4, "After one pop, top is 4");
    printStack(a, "A");

    // --- 4) Copy constructor (deep copy) ---
    ArrayStack<int> b = a;  // copy of A
    printStack(b, "B (copy of A)");
    expect(b.getLength() == a.getLength(), "Copy has same length");
    // Mutate B and ensure A unchanged
    b.pop(); // pop 4, new top=3
    expect(b.peek() == 3, "B top becomes 3 after pop");
    expect(a.peek() == 4, "A remains unaffected (top still 4)");

    // --- 5) Assignment operator (deep copy) ---
    ArrayStack<int> c;      // default capacity
    c = a;                  // assign from A
    printStack(c, "C (assigned from A)");
    expect(c.getLength() == a.getLength(), "Assigned stack has same length");
    // Self-assignment safety check
    c = c;
    expect(c.getLength() == a.getLength(), "Self-assignment leaves stack intact");

    // --- 6) Clear and underflow exceptions ---
    b.clear();
    printStack(b, "B after clear()");
    expect(b.isEmpty(), "Cleared stack is empty");
    // Underflow on pop
    try {
        b.pop();
        cout << "[FAIL] Expected underflow on pop from empty stack\n";
    } catch (const underflow_error& e) {
        cout << "[OK]   Caught underflow (pop): " << e.what() << endl;
    } catch (const exception& e) {
        cout << "[OK]   Caught exception (pop): " << e.what() << endl;
    }
    // Underflow on peek
    try {
        (void)b.peek();
        cout << "[FAIL] Expected underflow on peek from empty stack\n";
    } catch (const underflow_error& e) {
        cout << "[OK]   Caught underflow (peek): " << e.what() << endl;
    } catch (const exception& e) {
        cout << "[OK]   Caught exception (peek): " << e.what() << endl;
    }

    // --- 7) Mixed operations sanity check ---
    ArrayStack<int> d(3);
    d.push(10);
    d.push(20);
    expect(d.peek() == 20, "Top is 20");
    d.pop();                // remove 20
    d.push(30);
    d.push(40);             // now full (10,30,40 with top=40)
    printStack(d, "D");
    expect(d.isFull(), "D is full at capacity 3");
    expect(d.peek() == 40, "Top of D is 40");

    cout << "\nAll tests done.\n";
    return 0;
}

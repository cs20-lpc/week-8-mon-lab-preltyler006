template <typename T>
ArrayStack<T>::ArrayStack(int i) {
    this->maxSize = i;
    this->length = 0;
    this->buffer = new T[maxSize];
}

template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& copyObj) {
    copy(copyObj);
}

template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
ArrayStack<T>::~ArrayStack() {
    clear();
}

template <typename T>
void ArrayStack<T>::clear() {
    if (this->buffer != nullptr) {
        delete[] this->buffer;
        this->buffer = nullptr;
    }

    this->length = 0;
    this->maxSize = 0;
}

template <typename T>
void ArrayStack<T>::copy(const ArrayStack<T>& copyObj) {
    this->length = copyObj.length;
    this->maxSize = copyObj.maxSize;

    this->buffer = new T[this->maxSize];

    for (int i = 0; i < this->length; i++) {
        this->buffer[i] = copyObj.buffer[i];
    }

}

template <typename T>
int ArrayStack<T>::getLength() const {
    return this->length;
}

template <typename T>
int ArrayStack<T>::getMaxSize() const {
    return maxSize;
}

template <typename T>
bool ArrayStack<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
bool ArrayStack<T>::isFull() const {
    return this->length == maxSize;
}

template <typename T>
T ArrayStack<T>::peek() const {
    if (this->isEmpty()) {
        throw underflow_error("peek(): Stack is empty");
    }

    return this->buffer[this->length - 1];
}

template <typename T>
void ArrayStack<T>::pop() {
    if (this->isEmpty()) {
        throw underflow_error("pop(): Stack is empty");
    }

    this->length--;
}

template <typename T>
void ArrayStack<T>::push(const T& elem) {
    try {
        if (this->isFull()) {
            throw overflow_error("push(): Stack is full");
        }

        this->buffer[this->length] = elem;
        this->length++;
    }
    catch (const overflow_error& e) {
        cerr << "Overflow error in push(): " << e.what() << endl;
        return;
    }
    catch (const exception& e) {
        cerr << "General exception in push(): " << e.what() << endl;
        return;
    }
    catch (...) {
        cerr << "Unknown exception occurred in push()." << endl;
        return;
    }
}

template <typename T>
void ArrayStack<T>::rotate(typename Stack<T>::Direction dir) {
    if (this->length <= 1) return;

    switch (dir) {
        case Stack<T>::RIGHT: {
            // bottom -> top
            T bottom = this->buffer[0];
            for (int i = 0; i < this->length - 1; i++) {
                this->buffer[i] = this->buffer[i + 1];
            }
            this->buffer[this->length - 1] = bottom;
            break;
        }
        case Stack<T>::LEFT: {
            // top -> bottom
            T top = this->buffer[this->length - 1];
            for (int i = this->length - 1; i > 0; --i) {
                this->buffer[i] = this->buffer[i - 1];
            }
            this->buffer[0] = top;
            break;
        }
        default:
            break;
    }
}

template <typename T>
ostream& operator<<(ostream& outStream, const ArrayStack<T>& myObj) {
    if (myObj.isEmpty()) {
        outStream << "Stack is empty, no elements to display.\n";
    }
    else {
        for (int i = myObj.length - 1; i >= 0; i--) {
            outStream << (i == myObj.length - 1 ? "top\t" : "\t")
                      << myObj.buffer[i] << endl;
        }
    }

    return outStream;
}


[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/wu16z5h-)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=20933399&assignment_repo_type=AssignmentRepo)
# Week 8 Mon Lab

## Directions

You will be implementing the Stack ADT as an array-based class. The `Stack` abstract class is already given to you, along with the header file for the `ArrayStack` class, and a skeleton of its implementation file.

You are also in charge of writing your own driver program to test your `ArrayStack` class. Be thorough with your testing by checking all the operations in different scenarios and with various data types. 
#### Do not edit/rename lab09-main.cpp. Write your own driver file to test and upload results to canvas. Make sure your driver includes tests for rotation.

## Notes

- If you need to access the `length` attribute in your `ArrayStack` class, you need to write it as `this->length`
- The `buffer` attribute is meant to be a fixed-size, dynamic array
- The `<<` stream insertion operator has been overloaded for the `ArrayStack` class, meaning you can use `cout` on your `ArrayStack` object to print out the elements inside in top-to-bottom order
- There are a number of operations that need to consider if it's invalid for it to be called: in those scenarios, make sure to `throw` a `string` exception explaining the error, like this
    ```C++
    throw string("message goes here");
    ```
- To access the enumerator values of the `Direction` enumeration from within the `ArrayStack` class, you need to scope, like this:
    ```C++
    Stack<T>::RIGHT
    ```
- Similarly, if you are trying to access `Direction` values outside of the class completely, you can only do so within a function template so that the above syntax works. This means you can't test the `rotate` method directly in the `main` function, you have to create a separate function template for that. For example:
    ```C++
    template <typename T>
    void testRotate(ArrayStack<T>&);
    ```





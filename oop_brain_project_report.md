# OOP-Brain Project: Object-Oriented Programming Analysis Report
## 1. Project Overview
**OOP-Brain** is a modular, extensible, and object-oriented Artificial Neural Network library developed from scratch using C++. Instead of utilizing pre-existing libraries (such as Eigen or TensorFlow), the project constructs fundamental matrix operations, forward propagation network structures, activation functions, and model save/load mechanisms internally, adhering to Object-Oriented Programming (OOP) principles.
This report conducts an in-depth analysis of how the classes and architecture within the project are structured around OOP concepts (Encapsulation, Inheritance, Polymorphism, Abstraction).
---
## 2. Application of Object-Oriented Programming (OOP) Principles
The project perfectly integrates the four core pillars of OOP:
### 2.1. Encapsulation
The internal states (data) of the classes are hidden from the outside world, and only the necessary parts are exposed through public methods.
*   **`Matrix` Class:** The variables `rows`, `cols`, and `data` (dynamic 2D array) are defined as `private`. Direct access to matrix data is prevented; instead, safe access is provided via `operator()` overloading. For dimension information, `getRows()` and `getCols()` (getter) functions are used.
*   **`DenseLayer` Class:** The fundamental parameters of the layer, namely `weights`, `biases`, and `activation` (activation function pointer), are hidden as `private`.
*   **`NeuralNetwork` Class:** The `layers` vector holding the network's layers is hidden, and the process of adding layers is performed in a controlled manner solely through the `addLayer` method.
### 2.2. Inheritance
Inheritance is actively used to prevent code duplication and establish an "IS-A" relationship.
*   **Hierarchical Structure:** The `DenseLayer` class is derived from the abstract `BaseLayer` class (`class DenseLayer : public BaseLayer`). This establishes a standard infrastructure for different layer types that might be added in the future, such as `ConvolutionalLayer` or `DropoutLayer`.
*   **Activation Functions:** The `Sigmoid` and `ReLU` classes inherit from the `IActivation` interface.
*   **Custom Exceptions:** The `DimensionMismatchException` class, written for dimension mismatch errors, inherits from the `std::exception` class in the C++ standard library, integrating it into the system's exception throwing mechanism.
### 2.3. Polymorphism
Different objects are enabled to exhibit different behaviors using the same interface. **Runtime Polymorphism** is heavily utilized in the project:
*   **Virtual Functions:** The `forward`, `save`, and `load` functions within `BaseLayer` are defined as virtual. The `NeuralNetwork` class holds layers in a list of type `BaseLayer*` (base class pointer). During the forward propagation loop (`layer->forward(current)`), which layer type (e.g., DenseLayer) the called function belongs to is determined at runtime (Late Binding / Dynamic Dispatch).
*   **Strategy Pattern:** Activation functions are abstracted with the `IActivation` interface, and `DenseLayer` accesses these functions via a pointer. This allows behavior (Sigmoid or ReLU?) to be changed at runtime without needing if-else blocks.
![Activation Functions Comparison (Sigmoid vs ReLU)](activations.png)
### 2.4. Abstraction
Complex subsystems are hidden to create easy-to-use, high-level structures.
*   **Pure Virtual Classes:** The `BaseLayer` and `IActivation` classes are abstract classes because they possess at least one pure virtual function (`= 0`), meaning they cannot be instantiated directly. They merely serve as interfaces (contracts) defining what needs to be done.
*   Complex algorithmic details like matrix multiplication (`operator*`) or file reading operations are hidden within the classes, allowing the user (inside `main.cpp`) to make simple calls like `nn.predict(X)`.
---
## 3. Class Analysis and System Architecture
![OOP-Brain UML Class Diagram](https://github.com/Danial-Pourrashidi/OOP-Neural-Network/blob/f54ff55e772c0435a2338830f6498e19eec33a78/png/Diagram.png)
### A. Core Math Engine: `Matrix`
*   **Memory Management (Rule of Three):** A rule that classes using dynamic memory in C++ must follow. The `Matrix` class has specifically written its own **Copy Constructor**, **Assignment Operator**, and **Destructor** to safely manage the memory it allocates with `new`. This ensures deep copy is performed, preventing crashes and memory leaks caused by shallow copying.
*   **Operator Overloading:** One of the powerful features of C++. By overloading the `*` operator for matrix multiplication, `+` for matrix addition and broadcasting, and `()` for accessing elements, readable code close to mathematical notation (`input * weights + biases`) is achieved.
### B. Neural Network Layers: `BaseLayer` and `DenseLayer`
*   `DenseLayer` (Fully Connected Layer) manages its own weight and bias matrices. In its constructor, it automatically initializes these matrices with randomized values.
*   In the `forward` method, it applies the linear algebra equation `Z = X * W + B` and, if an activation function is assigned to the layer, passes the result through this function and returns it. Its destructor is responsible for deleting its activation object from memory (`delete activation`).
### C. Manager and Orchestration: `NeuralNetwork`
![OOP-Brain Forward Feed Neural Network Architecture (Iris Example)](nn.png)
*   **Composition:** The network consists of layers (`std::vector<BaseLayer*>`). The network manages the lifecycle of the layers given to it. When the network object is destroyed, its destructor (`~NeuralNetwork`) frees all dynamic layers in its list, preventing memory leaks.
*   **Persistence (Serialization):** With the `saveModel` and `loadModel` functions, the ability to save weights and architecture to disk (in .txt format) after model training is completed, and read them back later, is provided.
### D. Auxiliary Components
*   **`CSVReader`:** A utility class designed solely for reading datasets, defining its functions as `static` so there is no need for instantiation. In accordance with the Separation of Concerns principle, it separates file I/O operations from the main network logic.
*   **Exception Handling:** Potential logical or dimension errors (e.g., trying to multiply a 3x4 matrix with a 5x2 matrix) are thrown using the custom `DimensionMismatchException` class. As seen in `main.cpp`, these errors are caught with `try-catch` blocks, preventing the program from crashing.
---
## 4. Evaluation for the Project Assignment and Conclusion
This project is an **excellent and highly advanced example** for a C++ Object-Oriented Programming course.
It hasn't just performed basic object instantiation;
1.  It has professionally handled **Dynamic Memory Management (Pointers, Memory Allocation, Rule of Three)**,
2.  Provided elegant syntax via **Operator Overloading**,
3.  Established a modular "Plug-and-Play" architecture (ability to add desired activation or layer wherever wanted) thanks to **Polymorphism & Abstraction**,
4.  Applied robust software principles through **Exception Handling**.
**In conclusion;** with its code structure, proper distribution of responsibilities (Single Responsibility Principle) to classes, and the use of advanced OOP architectures (Strategy Pattern), it successfully fulfills all requirements of an academic project according to professional software engineering standards.

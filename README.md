# Rover resources arbiter (model checking)

## Materials for paper:
M. V. Neyzov.
Symmetry based development and verification of reactive system programs // Modeling and Analysis of Information Systems, vol. ?, no. 1, pp. ?, 2026. DOI: ?.

## Resume

* Arbiter is to ensure mutually exclusive access of processes to resources.
* Arbiter is a program consisting of a `core` and its `wrapper`.
* The core uses process number `symmetry`.
* The core coordinates the actions in the wrapper.
* Implemented `model checking` of the core.
* The model of core is automatically `extracted` from the program.
* The core guarantees the satisfiability of `temporal properties`.

[//]:----------------------------------------------------

## Technology Stack

Programming Languages: **`C/C++`**

IDE: **`Visual Studio Code`**

Model Checker Tool: **`Spin`**

Modeling Language: **`Promela`**

Properties Specification Language: **`LTL (Linear Temporal Logic)`**

[//]:----------------------------------------------------

## Content

* Arbiter – [C++ code](./cpp_code)
* Core – [C code](./c_code)
* Model of core – [Promela code](./promela_code)
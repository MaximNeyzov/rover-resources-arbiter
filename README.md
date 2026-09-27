# Rover resources arbiter (model checking)

## Materials for paper:
M. V. Neyzov.
Using Symmetry in Programming and Verification of a Resource Arbiter // Modeling and Analysis of Information Systems, vol. 33, no. 1, pp. 90–116, 2026. https://doi.org/10.18255/1818-1015-2026-1-90-116

## Resume

* Arbiter is to ensure mutually exclusive access of processes to resources.
* Arbiter is a program consisting of a `kernel` and its `wrapper`.
* The kernel uses process number `symmetry`.
* The kernel coordinates the actions in the wrapper.
* Implemented `model checking` of the kernel.
* The model of kernel is automatically `extracted` from the program.
* The kernel guarantees the satisfiability of `temporal properties`.

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
* Kernel – [C code](./c_code)
* Model of kernel – [Promela code](./promela_code)
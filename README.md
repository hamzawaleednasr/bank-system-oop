# Bank Management System (C++) 🏦

A **console-based bank management system** implemented in **modern C++**, designed around a **screen-driven object-oriented architecture**.  
The project simulates core banking operations while emphasizing clean design, separation of concerns, and reusable components.

---

## 🧩 Architectural Overview

The system is structured around a **Screen-Based Architecture**, where each user interaction is represented as a dedicated screen class derived from a common base interface.

Core architectural layers include:
- **Screen Layer** – Handles user interaction and navigation
- **Domain Layer** – Represents core entities such as users and clients
- **Business Logic Layer** – Implements banking operations and rules
- **Utility Layer** – Provides shared helpers for validation, formatting, and dates
- **Persistence Layer** – File-based storage for data durability

---

## 🏗️ Core Design Components

### Screen System
- All screens inherit from a base `screen` class
- Each screen encapsulates a single responsibility (list, add, update, delete, transact)
- Navigation is centralized and controlled through explicit screen transitions
- Polymorphism is used to treat all screens uniformly

### Domain Model
- `person` acts as a base abstraction
- `client` and `user` extend shared behavior with specialized responsibilities
- Clear separation between banking clients and system users (employees/admins)

### User Roles & Permissions
- Users are authenticated before accessing the system
- Administrative actions (user management) are isolated from client operations
- Role separation is enforced at the screen and logic level

---

## 💼 Banking Features

- Client management (add, update, delete, search, list)
- User management with role-based access
- Deposit and withdrawal operations
- Money transfers between clients
- Transfer logging and balance tracking
- Total balances reporting

All operations are validated before execution to ensure data consistency.

---

## 💾 Data Persistence Strategy

- Data is stored using **file-based persistence**
- Read/write operations are encapsulated away from screen logic
- The design allows replacing file storage with another backend without rewriting screens

---

## 🧰 Utilities & Helpers

The project includes reusable utility modules for:
- Input validation and safe numeric/string handling
- Date formatting and comparison
- String manipulation
- Shared global context for current session state

These helpers reduce duplication and keep business logic clean.

---

# 👤 Author
**Hamza Waleed**

# Design Patterns in C++

Implementation of three design patterns in C++, based on the [Refactoring Guru](https://refactoring.guru/design-patterns) catalog.

> **Note:** This project was implemented with the assistance of **Claude (Anthropic)**.

---

## Patterns

| Type | Pattern | File |
|------|---------|------|
| Creational | [Factory Method](#1-factory-method--creational) | `creational/factory-method/factory_method.cpp` |
| Behavioral | [Command](#2-command--behavioral) | `behavioral/command/command.cpp` |
| Structural | [Decorator](#3-decorator--structural) | `structural/decorator/decorator.cpp` |

---

## 1. Factory Method — Creational

> Reference: https://refactoring.guru/design-patterns/factory-method

### Context

A document editor application needs to create different types of documents: PDF, Word, and Spreadsheet. Each document type has its own way of opening and saving files.

### Problem

If the application directly instantiates concrete document classes (e.g., `new PDFDocument()`), the code becomes tightly coupled to those specific classes. Adding a new document type would require modifying existing code, violating the Open/Closed Principle.

### Solution

The Factory Method pattern defines an interface (`createDocument()`) in a base `DocumentEditor` class and lets each subclass (`PDFEditor`, `WordEditor`, `SpreadsheetEditor`) decide which concrete `Document` to instantiate. The client code works only with the abstract interface — it never needs to know which document type is being created.

### Code Explanation

```
DocumentEditor          (abstract creator)
├── PDFEditor           → creates PDFDocument
├── WordEditor          → creates WordDocument
└── SpreadsheetEditor   → creates SpreadsheetDocument

Document                (abstract product)
├── PDFDocument
├── WordDocument
└── SpreadsheetDocument
```

- **`Document`** — abstract product interface with `open()`, `save()`, and `getType()` methods.
- **`PDFDocument`, `WordDocument`, `SpreadsheetDocument`** — concrete products implementing the `Document` interface.
- **`DocumentEditor`** — abstract creator declaring the factory method `createDocument()` and containing the business logic method `newDocument()`, which uses the factory method internally.
- **`PDFEditor`, `WordEditor`, `SpreadsheetEditor`** — concrete creators that override `createDocument()` to return the appropriate product.
- **`clientCode()`** — works with any editor through the abstract `DocumentEditor` interface, completely unaware of which document type will be created.

### How to run

```bash
g++ -o factory_method creational/factory-method/factory_method.cpp
./factory_method
```

### Expected output

```
=== Factory Method Pattern Demo ===

Launching PDF Editor:
Editor: Creating a new PDF document.
[PDF] Opening PDF document...
[PDF] Saving as .pdf file...

Launching Word Editor:
Editor: Creating a new Word document.
[Word] Opening Word document...
[Word] Saving as .docx file...

Launching Spreadsheet Editor:
Editor: Creating a new Spreadsheet document.
[Spreadsheet] Opening spreadsheet...
[Spreadsheet] Saving as .xlsx file...
```

---

## 2. Command — Behavioral

*Coming soon.*

---

## 3. Decorator — Structural

*Coming soon.*

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

> Reference: https://refactoring.guru/design-patterns/command

### Context

A text editor application needs to support inserting and deleting text, with the ability to undo any previously executed action.

### Problem

Without a structured approach, undo/redo logic ends up scattered across the UI or business logic, tightly coupling operations to their execution context. Adding new operations or extending undo behavior becomes increasingly difficult and error-prone.

### Solution

The Command pattern encapsulates each action (insert, delete) as an object implementing a common `Command` interface with `execute()` and `undo()` methods. An `Invoker` (`CommandHistory`) stores executed commands in a stack and delegates undo calls to them. The client code only interacts with the invoker — it never calls editor methods directly.

### Code Explanation

```
Command                 (interface)
├── InsertCommand       → inserts text, undoes by deleting it
└── DeleteCommand       → deletes text, undoes by restoring it

TextEditor              (receiver — does the actual work)
CommandHistory          (invoker — executes and stores commands)
```

- **`Command`** — interface declaring `execute()` and `undo()`.
- **`InsertCommand`** — stores the content to insert; `undo()` removes it from the editor.
- **`DeleteCommand`** — stores the deleted content before removing it; `undo()` restores it.
- **`TextEditor`** — the receiver that directly manipulates the text string.
- **`CommandHistory`** — the invoker that calls `execute()` on commands and maintains a stack for undo operations.

### How to run

```bash
g++ -o command behavioral/command/command.cpp
./command
```

### Expected output

```
=== Command Pattern Demo ===

-- Executing commands --
[Editor] Inserted: "Hello, "
[Editor] Inserted: "World!"
Current text: "Hello, World!"

[Editor] Deleted: "World!"
Current text: "Hello, "

-- Undoing commands --
[Editor] Restored: "World!"
[Undo] Restored: "World!"
Current text: "Hello, World!"

[Undo] Reverted insert of: "World!"
[Editor] Deleted: "World!"
Current text: "Hello, "

[Undo] Reverted insert of: "Hello, "
[Editor] Deleted: "Hello, "
Current text: ""

[Undo] Nothing to undo.
Current text: ""
```

---

## 3. Decorator — Structural

> Reference: https://refactoring.guru/design-patterns/decorator

### Context

A notification system needs to send alerts through multiple channels: Email, SMS, Slack, and a logging layer. Users may want any combination of these channels active at the same time.

### Problem

Using inheritance to cover every combination (EmailSMS, EmailSlack, EmailSMSSlack, etc.) leads to a class explosion. Every new channel requires updating all existing combinations, making the code impossible to maintain.

### Solution

The Decorator pattern wraps a base `Notifier` object with additional behavior at runtime. Each decorator (`SMSDecorator`, `SlackDecorator`, `LoggerDecorator`) holds a reference to a `Notifier` and calls it before or after adding its own behavior. Decorators can be stacked in any order and combination without changing the original class.

### Code Explanation

```
Notifier                    (component interface)
└── EmailNotifier           (concrete component — base behavior)

NotifierDecorator           (base decorator — wraps a Notifier)
├── SMSDecorator            → adds SMS notification
├── SlackDecorator          → adds Slack notification
└── LoggerDecorator         → adds logging before and after sending
```

- **`Notifier`** — component interface declaring `send()`.
- **`EmailNotifier`** — the concrete base component; sends email notifications.
- **`NotifierDecorator`** — abstract base decorator that holds a reference to a `Notifier` and delegates `send()` to it.
- **`SMSDecorator`, `SlackDecorator`, `LoggerDecorator`** — concrete decorators that call the wrapped notifier's `send()` and add their own behavior.
- **Client code** — stacks decorators freely at runtime, with no knowledge of which concrete combination is being used.

### How to run

```bash
g++ -o decorator structural/decorator/decorator.cpp
./decorator
```

### Expected output

```
=== Decorator Pattern Demo ===

-- Email only --
[Email] To: alice@example.com | Message: Your order has been placed.

-- Email + SMS --
[Email] To: alice@example.com | Message: Your order has been shipped.
[SMS] To: +55 44 99999-0000 | Message: Your order has been shipped.

-- Email + SMS + Slack --
[Email] To: alice@example.com | Message: Payment confirmed.
[SMS] To: +55 44 99999-0000 | Message: Payment confirmed.
[Slack] Channel: #alerts | Message: Payment confirmed.

-- Email + SMS + Slack + Logger --
[Log] Sending notification: "Account login detected."
[Email] To: alice@example.com | Message: Account login detected.
[SMS] To: +55 44 99999-0000 | Message: Account login detected.
[Slack] Channel: #alerts | Message: Account login detected.
[Log] Notification sent.
```

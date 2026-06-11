#include <iostream>
#include <string>

// Product interface
class Document {
public:
    virtual void open() const = 0;
    virtual void save() const = 0;
    virtual std::string getType() const = 0;
    virtual ~Document() {}
};

// Concrete Products
class PDFDocument : public Document {
public:
    void open() const override {
        std::cout << "[PDF] Opening PDF document...\n";
    }
    void save() const override {
        std::cout << "[PDF] Saving as .pdf file...\n";
    }
    std::string getType() const override {
        return "PDF";
    }
};

class WordDocument : public Document {
public:
    void open() const override {
        std::cout << "[Word] Opening Word document...\n";
    }
    void save() const override {
        std::cout << "[Word] Saving as .docx file...\n";
    }
    std::string getType() const override {
        return "Word";
    }
};

class SpreadsheetDocument : public Document {
public:
    void open() const override {
        std::cout << "[Spreadsheet] Opening spreadsheet...\n";
    }
    void save() const override {
        std::cout << "[Spreadsheet] Saving as .xlsx file...\n";
    }
    std::string getType() const override {
        return "Spreadsheet";
    }
};

// Creator (abstract)
class DocumentEditor {
public:
    // Factory Method — subclasses decide which Document to create
    virtual Document* createDocument() const = 0;

    // Business logic that uses the factory method
    void newDocument() const {
        Document* doc = createDocument();
        std::cout << "Editor: Creating a new " << doc->getType() << " document.\n";
        doc->open();
        doc->save();
        std::cout << "\n";
        delete doc;
    }

    virtual ~DocumentEditor() {}
};

// Concrete Creators
class PDFEditor : public DocumentEditor {
public:
    Document* createDocument() const override {
        return new PDFDocument();
    }
};

class WordEditor : public DocumentEditor {
public:
    Document* createDocument() const override {
        return new WordDocument();
    }
};

class SpreadsheetEditor : public DocumentEditor {
public:
    Document* createDocument() const override {
        return new SpreadsheetDocument();
    }
};

// Client code
void clientCode(const DocumentEditor& editor) {
    editor.newDocument();
}

int main() {
    std::cout << "=== Factory Method Pattern Demo ===\n\n";

    PDFEditor pdfEditor;
    WordEditor wordEditor;
    SpreadsheetEditor spreadsheetEditor;

    std::cout << "Launching PDF Editor:\n";
    clientCode(pdfEditor);

    std::cout << "Launching Word Editor:\n";
    clientCode(wordEditor);

    std::cout << "Launching Spreadsheet Editor:\n";
    clientCode(spreadsheetEditor);

    return 0;
}

#include <iostream>
#include <string>
#include <stack>
#include <vector>

// Receiver — the object that performs the actual work
class TextEditor {
private:
    std::string text;

public:
    void insertText(const std::string& content) {
        text += content;
        std::cout << "[Editor] Inserted: \"" << content << "\"\n";
    }

    void deleteText(int chars) {
        if (chars > (int)text.size()) chars = text.size();
        std::string removed = text.substr(text.size() - chars);
        text = text.substr(0, text.size() - chars);
        std::cout << "[Editor] Deleted: \"" << removed << "\"\n";
    }

    void restoreText(const std::string& content) {
        text += content;
    }

    std::string getText() const {
        return text;
    }
};

// Command interface
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Concrete Command: Insert
class InsertCommand : public Command {
private:
    TextEditor& editor;
    std::string content;

public:
    InsertCommand(TextEditor& editor, const std::string& content)
        : editor(editor), content(content) {}

    void execute() override {
        editor.insertText(content);
    }

    void undo() override {
        editor.deleteText(content.size());
        std::cout << "[Undo] Reverted insert of: \"" << content << "\"\n";
    }
};

// Concrete Command: Delete
class DeleteCommand : public Command {
private:
    TextEditor& editor;
    int chars;
    std::string deletedContent;

public:
    DeleteCommand(TextEditor& editor, int chars)
        : editor(editor), chars(chars), deletedContent("") {}

    void execute() override {
        std::string text = editor.getText();
        int toDelete = std::min(chars, (int)text.size());
        deletedContent = text.substr(text.size() - toDelete);
        editor.deleteText(toDelete);
    }

    void undo() override {
        editor.restoreText(deletedContent);
        std::cout << "[Undo] Restored: \"" << deletedContent << "\"\n";
    }
};

// Invoker — stores and executes commands, manages undo history
class CommandHistory {
private:
    std::stack<Command*> history;

public:
    void executeCommand(Command* command) {
        command->execute();
        history.push(command);
    }

    void undo() {
        if (history.empty()) {
            std::cout << "[Undo] Nothing to undo.\n";
            return;
        }
        Command* command = history.top();
        history.pop();
        command->undo();
        delete command;
    }

    ~CommandHistory() {
        while (!history.empty()) {
            delete history.top();
            history.pop();
        }
    }
};

int main() {
    std::cout << "=== Command Pattern Demo ===\n\n";

    TextEditor editor;
    CommandHistory history;

    std::cout << "-- Executing commands --\n";
    history.executeCommand(new InsertCommand(editor, "Hello, "));
    history.executeCommand(new InsertCommand(editor, "World!"));
    std::cout << "Current text: \"" << editor.getText() << "\"\n\n";

    history.executeCommand(new DeleteCommand(editor, 6));
    std::cout << "Current text: \"" << editor.getText() << "\"\n\n";

    std::cout << "-- Undoing commands --\n";
    history.undo();
    std::cout << "Current text: \"" << editor.getText() << "\"\n\n";

    history.undo();
    std::cout << "Current text: \"" << editor.getText() << "\"\n\n";

    history.undo();
    std::cout << "Current text: \"" << editor.getText() << "\"\n\n";

    history.undo(); // nothing left
    std::cout << "Current text: \"" << editor.getText() << "\"\n";

    return 0;
}

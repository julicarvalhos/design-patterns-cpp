#include <iostream>
#include <string>

// Component interface
class Notifier {
public:
    virtual void send(const std::string& message) const = 0;
    virtual ~Notifier() {}
};

// Concrete Component — base notification (email)
class EmailNotifier : public Notifier {
private:
    std::string recipient;

public:
    EmailNotifier(const std::string& recipient) : recipient(recipient) {}

    void send(const std::string& message) const override {
        std::cout << "[Email] To: " << recipient << " | Message: " << message << "\n";
    }
};

// Base Decorator — wraps a Notifier
class NotifierDecorator : public Notifier {
protected:
    Notifier* wrappee;

public:
    NotifierDecorator(Notifier* notifier) : wrappee(notifier) {}

    void send(const std::string& message) const override {
        wrappee->send(message);
    }

    virtual ~NotifierDecorator() {}
};

// Concrete Decorator: SMS
class SMSDecorator : public NotifierDecorator {
private:
    std::string phoneNumber;

public:
    SMSDecorator(Notifier* notifier, const std::string& phoneNumber)
        : NotifierDecorator(notifier), phoneNumber(phoneNumber) {}

    void send(const std::string& message) const override {
        NotifierDecorator::send(message);
        std::cout << "[SMS] To: " << phoneNumber << " | Message: " << message << "\n";
    }
};

// Concrete Decorator: Slack
class SlackDecorator : public NotifierDecorator {
private:
    std::string channel;

public:
    SlackDecorator(Notifier* notifier, const std::string& channel)
        : NotifierDecorator(notifier), channel(channel) {}

    void send(const std::string& message) const override {
        NotifierDecorator::send(message);
        std::cout << "[Slack] Channel: " << channel << " | Message: " << message << "\n";
    }
};

// Concrete Decorator: Logger
class LoggerDecorator : public NotifierDecorator {
public:
    LoggerDecorator(Notifier* notifier) : NotifierDecorator(notifier) {}

    void send(const std::string& message) const override {
        std::cout << "[Log] Sending notification: \"" << message << "\"\n";
        NotifierDecorator::send(message);
        std::cout << "[Log] Notification sent.\n";
    }
};

// Client code
void clientCode(Notifier* notifier, const std::string& message) {
    notifier->send(message);
}

int main() {
    std::cout << "=== Decorator Pattern Demo ===\n\n";

    // Base: email only
    std::cout << "-- Email only --\n";
    Notifier* notifier = new EmailNotifier("alice@example.com");
    clientCode(notifier, "Your order has been placed.");
    std::cout << "\n";

    // Email + SMS
    std::cout << "-- Email + SMS --\n";
    Notifier* smsNotifier = new SMSDecorator(
        new EmailNotifier("alice@example.com"),
        "+55 44 99999-0000"
    );
    clientCode(smsNotifier, "Your order has been shipped.");
    std::cout << "\n";

    // Email + SMS + Slack
    std::cout << "-- Email + SMS + Slack --\n";
    Notifier* fullNotifier = new SlackDecorator(
        new SMSDecorator(
            new EmailNotifier("alice@example.com"),
            "+55 44 99999-0000"
        ),
        "#alerts"
    );
    clientCode(fullNotifier, "Payment confirmed.");
    std::cout << "\n";

    // Email + SMS + Slack + Logger
    std::cout << "-- Email + SMS + Slack + Logger --\n";
    Notifier* loggedNotifier = new LoggerDecorator(
        new SlackDecorator(
            new SMSDecorator(
                new EmailNotifier("alice@example.com"),
                "+55 44 99999-0000"
            ),
            "#alerts"
        )
    );
    clientCode(loggedNotifier, "Account login detected.");
    std::cout << "\n";

    delete notifier;
    delete smsNotifier;
    delete fullNotifier;
    delete loggedNotifier;

    return 0;
}

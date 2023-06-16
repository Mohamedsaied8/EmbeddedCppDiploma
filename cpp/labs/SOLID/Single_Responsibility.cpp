#include <iostream>
#include <fstream>

class Logger {
public:
    void logError(const std::string& message) {
        std::ofstream file("log.txt", std::ios::app);
        file << "ERROR: " << message << std::endl;
        file.close();
    }

    void sendEmail(const std::string& recipient, const std::string& message) {
        std::cout << "Sending email to: " << recipient << std::endl;
        std::cout << "Message: " << message << std::endl;
    }
};

int main() {
    Logger logger;
    logger.logError("An error occurred!");
    logger.sendEmail("admin@example.com", "Error occurred, please check log!");

    return 0;
}

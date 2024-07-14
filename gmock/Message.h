#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <utility>

class Message {

    public:

        explicit Message(std::string message) : message(std::move(message)) {

        }

        std::string getMessage() const {
            return message;
        }

        bool isHtml() const {
            auto startHtmlTagPos = message.find("<html>");
            if (startHtmlTagPos != std::string::npos) {
                auto endHtmlTagPos = message.find("</html>");
                return endHtmlTagPos != std::string::npos && endHtmlTagPos > startHtmlTagPos;
            }
            return false;
        }

    private:

        std::string message;

};

#endif //MESSAGE_H
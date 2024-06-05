#ifndef SENDMESSAGE_H
#define SENDMESSAGE_H

#include <memory>
#include <vector>
#include "Message.h"
#include "AbstractTransport.h"

class SendMessage {

    public:

        explicit SendMessage(std::shared_ptr<AbstractTransport> transport)  { }

        void addTo(std::string to) {
            toList.push_back(to);
        }

        void send(Message message) {
            if (toList.empty()) {
                return;
            }

            for (auto &to: toList) {
                transport->send(message.getMessage(), to);
            }
        }

    private:

        std::shared_ptr<AbstractTransport> transport;
        std::vector<std::string> toList;

};

#endif
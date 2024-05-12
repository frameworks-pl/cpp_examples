#include "pch.h"
#include <string>
#include <vector>
#include <queue>

class Message {
    std::string messageId;
    
    public:
        Message(const std::string& messageId) {
            this->messageId = messageId;
        }
        virtual ~Message() {
        }
        
        const std::string& getMessageId() {
            return messageId;
        }
};

class ServerRequest : public Message {
    std::string serverId;
    
    public:
        ServerRequest(const std::string& messageId, const std::string& serverId) : Message(messageId) {
            this->serverId = serverId;
        }
        
        const std::string& getServerId() {
            return serverId;
        }
};

class ClientRequest : public Message {
    std::string clientId;
    
    public:
        ClientRequest(const std::string& messageId, const std::string& clientId) : Message(messageId) {
            this->clientId = clientId;
        }
        
        const std::string& getClientId() {
            return clientId;
        }

};

class MessageQueue {

    std::queue<Message*> messages;

    public:
        ~MessageQueue() {
            while (!messages.empty()) {
                delete messages.front();
                messages.pop();
            }
        }

        void enqueue(ServerRequest sr) {

            ServerRequest* pRequest = new ServerRequest(sr.getMessageId(), sr.getServerId());
            messages.push(pRequest);
        }

        void enqueue(ClientRequest cr) {
                
                ClientRequest* pRequest = new ClientRequest(cr.getMessageId(), cr.getClientId());
                messages.push(pRequest);

        }

        void pop() {
            delete messages.front();
            messages.pop();
        }

        std::string getMessageAsString() {
            Message* m = this->messages.front();

            if (dynamic_cast<ServerRequest*>(m) != NULL) {
                ServerRequest* sr = dynamic_cast<ServerRequest*>(m);
                return sr->getMessageId() + " " + sr->getServerId();
            } else {
                ClientRequest* cr = dynamic_cast<ClientRequest*>(m);
                return cr->getMessageId() + " " + cr->getClientId();
            }

            return "MessageQueue";
        }

};

TEST(ClientServerQueue, simpleCase) {

    MessageQueue mq;
    mq.enqueue(ServerRequest("1", "server1"));
    mq.enqueue(ClientRequest("2", "client1"));
    ASSERT_EQ("1 server1", mq.getMessageAsString());    
    mq.pop();
    ASSERT_EQ("2 client1", mq.getMessageAsString());
    

}
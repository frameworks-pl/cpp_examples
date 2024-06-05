#include "pch.h"
#include "SendMessage.h"
#include "Message.h"
#include "MockTransport.h"

TEST(SendMessage, test_sender_doesnt_send_message) {
    auto mockTransport = std::make_shared<MockTransport>();

    SendMessage sendMessage(mockTransport);
    Message message("message content");

    EXPECT_CALL(*mockTransport, send("asd", "asd"))
            .Times(0);

    sendMessage.send(message);
}
#ifndef MOCKTRANSPORT_H
#define MOCKTRANSPORT_H

#include <string>
#include "gmock/gmock.h"
#include "AbstractTransport.h"

class MockTransport : public AbstractTransport {

    public:

        MOCK_METHOD2(send, bool(std::string to, std::string content));

};

#endif //MOCKTRANSPORT_H
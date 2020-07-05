#include <string>


namespace Http {
    struct  Response {
        bool m_Status;
        std::string m_RawText;
        std::string m_HeaderText;
        std::string m_BodyText;
    };

    Response* Get(const char* url);
}

namespace Socket {
    int GetSock(const char* hostname);
}

#include <iostream>

#include "Http/Fetch.hpp"


int main() {
    auto s = Http::Get("im-neko.net");
    std::cout << "Status--------------" << std::endl;
    std::cout << s->m_Status << std::endl;
    std::cout << "Raw--------------" << std::endl;
    std::cout << s->m_RawText.c_str() << std::endl;
    std::cout << "Header--------------" << std::endl;
    std::cout << s->m_HeaderText.c_str() << std::endl;
    std::cout << "Body--------------" << std::endl;
    std::cout << s->m_BodyText.c_str() << std::endl;
    std::cout << "--------------" << std::endl;
    return 0;
}

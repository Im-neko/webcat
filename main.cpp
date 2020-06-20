#include <iostream>

#include "Http/Fetch.hpp"


int main() {
    auto s = Http::Get("im-neko.net");
    std::cout << s->m_Status << std::endl;
    std::cout << s->m_BodyText << std::endl;
    return 0;
}

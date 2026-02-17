#ifndef SESSIONMANAGER_HPP
#define SESSIONMANAGER_HPP

#include <string>
#include <map>

class SessionManager {
public:
    static std::string createSession();
    static bool hasSession(const std::string &id);
    static size_t incrementSession(const std::string &id);
private:
    static std::map<std::string, size_t> _sessions;
    static std::string _generateId();
};

#endif


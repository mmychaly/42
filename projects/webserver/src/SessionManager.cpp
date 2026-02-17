#include "SessionManager.hpp"
#include <cstdlib>
#include <ctime>
#include <sstream>

std::map<std::string, size_t> SessionManager::_sessions;

static bool _session_seeded = false;

std::string SessionManager::_generateId()
{
    if (!_session_seeded)
    {
        std::srand(std::time(NULL));
        _session_seeded = true;
    }
    std::stringstream ss;
    for (int i = 0; i < 16; ++i)
        ss << std::hex << (std::rand() % 16);
    return ss.str();
}

std::string SessionManager::createSession()
{
    std::string id = _generateId();
    _sessions[id] = 1;
    return id;
}

bool SessionManager::hasSession(const std::string &id)
{
    return _sessions.find(id) != _sessions.end();
}

size_t SessionManager::incrementSession(const std::string &id)
{
    std::map<std::string, size_t>::iterator it = _sessions.find(id);
    if (it == _sessions.end())
        return 0;
    return ++it->second;
}


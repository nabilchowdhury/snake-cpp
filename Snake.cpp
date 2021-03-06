#include "Snake.h"

using namespace std;


unordered_map<char, vector<int>> Snake::DIRECTIONS {
    {'h', {0, -1}},
    {'j', {1, 0}},
    {'k', {-1, 0}},
    {'l', {0, 1}}
};

Snake::Snake(unsigned x, unsigned y, char direction):
    m_score(0),
    m_direction(direction),
    m_size(1)
{
    m_coordinates.push_back({x, y});
    m_lookup[x].insert(y);
}

SnakeStatus Snake::moveSnake(unsigned x, unsigned y, bool grow) {
    // First check if moving snake to x, y kills it
    if (isSnakeAt(x, y)) {
        return SnakeStatus::DEAD;
    }

    // Add new coords to list
    m_coordinates.push_front({x, y});
    m_lookup[x].insert(y);

    // If there was food at (x, y), grow. Else, remove last coordinate
    if (grow) {
        ++m_score;
        ++m_size;
    } else {
        auto r = m_coordinates.back();
        m_coordinates.pop_back();
        m_lookup[r.first].erase(r.second);
        if (m_lookup[r.first].empty()) {
            m_lookup.erase(r.first);
        }
    }
    return SnakeStatus::ISOK;
}

void Snake::resetSnake(unsigned length) {
    // If snake gets too big, force it to reset
    for (auto it = next(m_coordinates.begin(), length); it != m_coordinates.end(); ++it) {
        m_lookup[it->first].erase(it->second);
        if (m_lookup[it->first].empty()) {
            m_lookup.erase(it->first);
        }
    }
    m_coordinates.resize(length);
    m_size = length;
}

unsigned Snake::getScore() const {
    return m_score;
}

pair<unsigned, unsigned> Snake::getCurrentPosition() const {
    return m_coordinates.front();
}

bool Snake::isSnakeAt(unsigned x, unsigned y) {
    return m_lookup.find(x) != m_lookup.end() && m_lookup[x].find(y) != m_lookup[x].end();
}

void Snake::setDirection(char direction) {
    m_direction = direction;
}

char Snake::getDirection() const {
    return m_direction;
}

unsigned Snake::getSize() const {
    return m_size;
}
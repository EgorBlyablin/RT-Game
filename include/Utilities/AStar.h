#ifndef A_STAR_H
#define A_STAR_H

#include <deque>
#include <functional>
#include <memory>
#include <thread>
#include <vector>

#include <SFML/System/Vector2.hpp>

/// @brief Точка маршрута имеющая предка и расстояния до начала и конца
class Node
{
  public:
    unsigned int x, y, distanceToOrigin = 0, distanceToEnd = 0, distance = 0;
    std::shared_ptr<Node> parent = nullptr;

    Node(unsigned int x, unsigned int y);
    Node(const Node &node);
    Node &operator=(const Node &node);
    ~Node() = default;

    friend bool operator<(const Node &first, const Node &second);
    friend bool operator==(const Node &first, const Node &second);
};

std::vector<sf::Vector2u> getNeighbors(const sf::Vector2u &tile, std::function<bool(sf::Vector2u)> isFree);
std::deque<sf::Vector2u> calculatePath(const sf::Vector2u &fromTile, const sf::Vector2u &toTile,
                                       std::function<bool(sf::Vector2u)> isFree, std::stop_token *stopToken);

#endif
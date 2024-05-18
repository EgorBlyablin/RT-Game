#include <iostream>
#include <set>

#include "Utilities/AStar.h"

Node::Node(unsigned int x, unsigned int y) : x(x), y(y)
{
}

Node::Node(const Node &node)
    : x(node.x), y(node.y), distanceToOrigin(node.distanceToOrigin), distanceToEnd(node.distanceToEnd),
      distance(node.distance), parent(node.parent)
{
}

Node &Node::operator=(const Node &node)
{
    this->x = node.x;
    this->y = node.y;
    this->distanceToOrigin = node.distanceToOrigin;
    this->distanceToEnd = node.distanceToEnd;
    this->distance = node.distance;
    this->parent = node.parent;

    return *this;
}

bool operator<(const Node &first, const Node &second)
{
    return first.distance < second.distance;
}

bool operator==(const Node &first, const Node &second)
{
    return first.x == second.x and first.y == second.y;
}

std::vector<sf::Vector2u> getNeighbors(const sf::Vector2u &tile, std::function<bool(sf::Vector2u)> isFree)
// получение вектора соседних клеток
{
    std::vector<sf::Vector2u> neighbors;

    for (int dx = -1; dx < 2; dx++)
        for (int dy = -1; dy < 2; dy++)
        {
            // если перемещение произошло по диагонали или клетка уходит в отрицательные значения - пропускаем
            if (not(abs(dx + dy) == 1) or ((int)tile.x + dx < 0) or ((int)tile.y + dy < 0))
                continue;

            unsigned int x = tile.x + dx;
            unsigned int y = tile.y + dy;

            if (isFree(sf::Vector2u(x, y)))
                neighbors.push_back(sf::Vector2u(x, y));
        }

    return neighbors;
}

std::deque<sf::Vector2u> calculatePath(const sf::Vector2u &fromTile, const sf::Vector2u &toTile,
                                       std::function<bool(sf::Vector2u)> isFree, std::stop_token *stopToken)
// расчет кратчайшего пути (используется алгоритм А*)
{
    Node startNode(fromTile.x, fromTile.y), endNode(toTile.x, toTile.y);

    if (startNode == endNode or not isFree(toTile))
        return std::deque<sf::Vector2u>();

    std::deque<Node> borderNodes; // пограничные клетки (кандидаты на проверку)
    borderNodes.push_back(startNode);

    auto nodesSort = [](const Node &a, const Node &b) { return a.distance < b.distance; };

    auto tilesComparator = [&fromTile](const sf::Vector2u &a, const sf::Vector2u &b) {
        unsigned int distanceA = abs(a.x - fromTile.x) + abs(a.y - fromTile.y);
        unsigned int distanceB = abs(b.x - fromTile.x) + abs(b.y - fromTile.y);

        return distanceA < distanceB;
    };
    std::set<sf::Vector2u, decltype(tilesComparator)> visitedTiles(tilesComparator); // просмотренные клетки

    while (not borderNodes.empty()) // пока есть кандидаты на проверку
    {
        if (stopToken->stop_requested())
            break;

        std::sort(borderNodes.begin(), borderNodes.end(), nodesSort);

        auto currentNode = borderNodes.front(); // проверяемая нода
        borderNodes.pop_front(); // удаляем проверяемую ноду из пограничных

        if (currentNode == endNode) // цель достигнута
        {
            // восстанавливаем маршрут
            std::deque<sf::Vector2u> path;
            auto nodeCursor = currentNode;

            while (nodeCursor.parent != nullptr)
            {
                path.push_front(sf::Vector2u(nodeCursor.x, nodeCursor.y));
                nodeCursor = *(nodeCursor.parent);
            }
            return path;
        }

        visitedTiles.insert(sf::Vector2u(currentNode.x, currentNode.y)); // заносим клетку в посещенные

        for (auto &neighbor : getNeighbors(sf::Vector2u(currentNode.x, currentNode.y), isFree))
        // проверяем соседей клетки
        {
            if (stopToken->stop_requested())
                break;

            if (visitedTiles.contains(neighbor)) // если клетку проверяли ранее - пропускаем
                continue;

            unsigned int distanceToOrigin = currentNode.distanceToOrigin + 1; // длина пути от начала

            Node neighborNode(neighbor.x, neighbor.y);
            auto iterator = std::find(borderNodes.begin(), borderNodes.end(), neighborNode);

            if (iterator != borderNodes.end()) // новая нода уже есть в пограничных
            {
                // выбираем лучшую и обновляем значения
                if (distanceToOrigin < iterator->distanceToOrigin)
                {
                    iterator->distanceToOrigin = distanceToOrigin;
                    iterator->distanceToEnd = abs(toTile.x - iterator->x) + abs(toTile.y - iterator->y);
                    iterator->distance = iterator->distanceToOrigin + iterator->distanceToEnd;
                    iterator->parent = std::make_shared<Node>(currentNode);
                }
            }
            else
            {
                // заносим в кандидаты на проверку
                neighborNode.distanceToOrigin = distanceToOrigin;
                neighborNode.distanceToEnd = abs(toTile.x - neighborNode.x) + abs(toTile.y - neighborNode.y);
                neighborNode.distance = neighborNode.distanceToOrigin + neighborNode.distanceToEnd;
                neighborNode.parent = std::make_shared<Node>(currentNode);

                borderNodes.push_back(neighborNode);
            }
        }
    }

    // если маршрут не существует - возвращаем пустую деку
    return std::deque<sf::Vector2u>();
}
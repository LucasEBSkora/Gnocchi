#pragma once

#include <string>
#include <map>
#include <vector>
#include <memory>

#include "ENVertex.h"

namespace EN
{

    class Scope
    {
    public:
        virtual ~Scope();
        void addVertex(std::shared_ptr<Vertex> v);
        void addEdge(std::shared_ptr<Edge> e);
        const std::vector<std::shared_ptr<Vertex>> getVertices() const;
        bool hasVertex(std::string name) const;
        const std::shared_ptr<Vertex> getVertex(std::string id) const;
        const std::vector<std::shared_ptr<Edge>> getEdges() const;

    private:
        std::vector<std::shared_ptr<Vertex>> vertices;
        std::map<std::string, std::shared_ptr<Vertex>> namedVertices;
        std::vector<std::shared_ptr<Edge>> edges;
    };
}
#include "ENScope.h"
#include "SemanticException.h"

namespace EN
{
    Scope::~Scope() {}
    void Scope::addVertex(std::shared_ptr<Vertex> v)
    {
        if (!v)
            throw SemanticException("can't add null vertex to scope!");

        if (namedVertices.count(v->id) != 0)
            throw SemanticException("Redeclaration of vertex with name " + v->id);

        vertices.push_back(v);

        if (v->id != "")
            namedVertices.emplace(v->id, v);
    }

    void Scope::addEdge(std::shared_ptr<Edge> e)
    {
        edges.push_back(e);
    }
    const std::vector<std::shared_ptr<Vertex>> Scope::getVertices() const
    {
        return vertices;
    }
    bool Scope::hasVertex(std::string name) const
    {
        return namedVertices.count(name);
    }
    const std::shared_ptr<Vertex> Scope::getVertex(std::string id) const
    {
        if (!hasVertex(id))
            throw SemanticException("Current scope has no vertex with ID " + id);

        return namedVertices.at(id);
    }

    const std::vector<std::shared_ptr<Edge>> Scope::getEdges() const
    {
        return edges;
    }

}
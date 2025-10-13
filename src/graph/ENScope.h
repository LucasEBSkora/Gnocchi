#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "ENTypeManager.h"
#include "ENVertex.h"

namespace EN {
using namespace std;
class Scope {
public:
  virtual ~Scope();
  void addVertex(shared_ptr<Vertex> v);
  void addEdge(shared_ptr<Edge> e);
  const vector<shared_ptr<Vertex>> getVertices() const;
  bool hasVertex(string name) const;
  const shared_ptr<Vertex> getVertex(string id) const;
  const vector<shared_ptr<Edge>> getEdges() const;

  TypeManager typeManager;

private:
  vector<shared_ptr<Vertex>> vertices;
  map<string, shared_ptr<Vertex>> namedVertices;
  vector<shared_ptr<Edge>> edges;
};
} // namespace EN
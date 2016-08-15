#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list < listS, vecS, directedS, no_property, property < edge_weight_t, int > > BoostGraph;
typedef graph_traits < BoostGraph >::vertex_descriptor VertexDescriptor;
typedef std::pair<int, int> Edge;
 

int main(int argc, char *argv[]){
   
    const int num_nodes = 5;
    enum nodes { A, B, C, D, E };
    char name[] = "ABCDE";
    Edge edge_array[] = { Edge(A, C), Edge(B, B), Edge(B, D), Edge(B, E),
            Edge(C, B), Edge(C, D), Edge(D, E), Edge(E, A), Edge(E, B)
    };
    int weights[] = { 10, 20, 1, 2, 7, 3, 1, 1, 1 };
    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    BoostGraph graph(edge_array, edge_array + num_arcs, weights, num_nodes);
    property_map<BoostGraph, edge_weight_t>::type weightmap = get(edge_weight, graph);
    vector<VertexDescriptor> p(num_vertices(graph));
    vector<int> d(num_vertices(graph));
    VertexDescriptor vd = vertex(A, graph);
    
    dijkstra_shortest_paths(graph, vd,
                            predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, graph))).
                            distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, graph))));
    
    cout << "distances and parents:" << endl;
    graph_traits < BoostGraph >::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(graph); vi != vend; ++vi) {
      cout << "distance(" << name[*vi] << ") = " << d[*vi] << ", ";
      cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << 
        endl;
    }
    cout << endl;
    
    ofstream dot_file("figs/dijkstra-eg.dot");
    
    dot_file << "digraph D {\n"
      << "  rankdir=LR\n"
      << "  size=\"4,3\"\n"
      << "  ratio=\"fill\"\n"
      << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";
    
    graph_traits < BoostGraph >::edge_iterator ei, ei_end;
    for (boost::tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
      graph_traits < BoostGraph >::edge_descriptor e = *ei;
      graph_traits < BoostGraph >::vertex_descriptor
        u = source(e, graph), v = target(e, graph);
      dot_file << name[u] << " -> " << name[v]
        << "[label=\"" << get(weightmap, e) << "\"";
      if (p[v] == u)
        dot_file << ", color=\"black\"";
      else
        dot_file << ", color=\"grey\"";
      dot_file << "]";
    }
    dot_file << "}";
    dot_file.close();
}


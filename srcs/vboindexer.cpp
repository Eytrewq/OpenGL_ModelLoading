#include "common.hpp"

bool getSimilarVertexIndex_fast(PackedVertex &packed, std::map<PackedVertex,unsigned int> &VertexToOutIndex, unsigned int & result)
{
	std::map<PackedVertex,unsigned int>::iterator it = VertexToOutIndex.find(packed);
	if (it == VertexToOutIndex.end()) {
		return false;
	} else {
		result = it->second;
		return true;
	}
}

void indexVBO(std::vector<t_vec3> & in_vertices,std::vector<unsigned int> & out_indices,std::vector<t_vec3> & out_vertices)
{
	std::map<PackedVertex,unsigned int> VertexToOutIndex;

	for (unsigned int i=0; i<in_vertices.size(); i++) {

		PackedVertex packed = {in_vertices[i]};

		unsigned int index;
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if (found) {
			out_indices.push_back(index);
		} else {
			out_vertices.push_back(in_vertices[i]);
			unsigned int newindex = (unsigned int)out_vertices.size() - 1;
			out_indices.push_back(newindex);
			VertexToOutIndex[packed] = newindex;
		}
	}
}

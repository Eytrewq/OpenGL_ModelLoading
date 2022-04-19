#include "common.hpp"

bool loadOBJ(const char * path, t_env *env) {
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<t_vec3> temp_vertices;
	std::vector<t_vec2> temp_uvs;
	std::vector<t_vec3> temp_normals;

	std::string path_obj = path;
	if (path_obj.find(".obj") == std::string::npos)
		return (false);

	FILE * file = fopen(path, "r");
	if( file == NULL ) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while(1) {
		char lineHeader[128];

		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			t_vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			t_vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			t_vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
			if (env->opt == 2) {
				int matches = fscanf(file, "%d/%d %d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0],
				&vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2],
				&vertexIndex[3], &uvIndex[3]);
				if (matches != 6 && matches != 8) {
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					fclose(file);
        			return (false);
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				if (matches == 8) {
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[2]);
					uvIndices.push_back(uvIndex[3]);
				}
			}
			if (env->opt == 1) {
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2],
				&vertexIndex[3], &uvIndex[3], &normalIndex[3]);
				if (matches != 9 && matches != 12) {
					printf("File can't be read by my simple parser : Try exporting with other options\n");
					fclose(file);
        			return (false);
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
				if (matches == 12) {
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
					uvIndices.push_back(uvIndex[0]);
					uvIndices.push_back(uvIndex[2]);
					uvIndices.push_back(uvIndex[3]);
					normalIndices.push_back(normalIndex[0]);
					normalIndices.push_back(normalIndex[2]);
					normalIndices.push_back(normalIndex[3]);
				}
			}
			if (env->opt == 0) {
				int nbr = fscanf(file, "%d %d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);
				if (nbr != 3 && nbr != 4) {
					printf("File can't be read by my simple parser : Try exporting with other options\n");
					fclose(file);
        			return (false);
				}
				
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				if (nbr == 4) {
					vertexIndices.push_back(vertexIndex[0]);
					vertexIndices.push_back(vertexIndex[2]);
					vertexIndices.push_back(vertexIndex[3]);
				}
			}
		} else {
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	for (unsigned int i = 0; i < temp_vertices.size(); i++) {
        if (temp_vertices[i].x > env->max.x)
            env->max.x = temp_vertices[i].x;
        if (temp_vertices[i].y > env->max.y)
            env->max.y = temp_vertices[i].y;
        if (temp_vertices[i].z > env->max.z)
            env->max.z = temp_vertices[i].z;
        
        if (temp_vertices[i].x < env->min.x)
            env->min.x = temp_vertices[i].x;
        if (temp_vertices[i].y < env->min.y)
            env->min.y = temp_vertices[i].y;
        if (temp_vertices[i].z < env->min.z)
            env->min.z = temp_vertices[i].z;
    }

	t_vec3 center = create_vec3((env->max.x + env->min.x)/2.0f,(env->max.y + env->min.y)/2.0f,(env->max.z + env->min.z)/2.0f);
	for( unsigned int i = 0; i < vertexIndices.size(); i++ ) {
		unsigned int vertexIndex = vertexIndices[i];
		t_vec3 vertex = temp_vertices[vertexIndex-1];
		vertex = vec3_sub(vertex, center);
		env->vertices.push_back(vertex);

		if (env->opt == 2) {
			unsigned int uvsIndex = uvIndices[i];
			t_vec2 uv = temp_uvs[uvsIndex-1];
			env->uvs.push_back(uv);
		}

		if (env->opt == 1) {
			unsigned int uvsIndex = uvIndices[i];
			t_vec2 uv = temp_uvs[uvsIndex-1];
			env->uvs.push_back(uv);

			unsigned int normalsIndex = normalIndices[i];
			t_vec3 normal = temp_normals[normalsIndex-1];
			env->normals.push_back(normal);
		}
	}

	fclose(file);
	return true;
}

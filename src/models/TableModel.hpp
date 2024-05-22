#ifndef MINI_BILLIARD_TABLEMODEL_HPP
#define MINI_BILLIARD_TABLEMODEL_HPP

#include "../classes/ObjectRenderable.h"
#include "../utils/ObjectUtil.hpp"

class TableModel: public ObjectRenderable {
public:
	TableModel(float width, float height, float length): ObjectRenderable(ObjectType::TABLE, MeshType::CUBE) {
		this->files = {
			{ FileType::VERTEX_SHADER, "shaders/table.vert" },
			{ FileType::FRAGMENT_SHADER, "shaders/table.frag" }
		};

        this->position.y = -2.5f;
        this->min = { width, height, length };
        this->max = { width, height, length };

		this->vertices = {
			// Front side
            { -width, -height, length },
            { width, -height, length },
            { width, height, length },
            { -width, height, length },

			// Back side
            { -width, -height, -length },
            { -width, height, -length },
            { width, height, -length },
            { width, -height, -length },

			// Left side
            { -width, -height, length },
            { -width, height, length },
            { -width, height, -length },
            { -width, -height, -length },

			// Right side
            { width, -height, length },
            { width, -height, -length },
            { width, height, -length },
            { width, height, length },

			// Top side
            { -width, height, length },
            { width, height, length },
            { width, height, -length },
            { -width, height, -length },

			// Bottom side
            { -width, -height, length },
            { -width, -height, -length },
            { width, -height, -length },
            { width, -height, length }
		};

		this->normals = {
			// Front side
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },

			// Back side
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },

			// Left side
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },

			// Right side
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },

			// Top side
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },

			// Bottom side
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f }
		};

        this->indices = {
			// Front face
			0, 1, 2,
			2, 3, 0,

			// Back face
			4, 5, 6,
			6, 7, 4,

            // Left face
            8, 9, 10,
            10, 11, 8,

            // Right face
			12, 13, 14,
			14, 15, 12,

			// Top face
			16, 17, 18,
			18, 19, 16,

			// Bottom face
			20, 21, 22,
			22, 23, 20
		};

        for (int vertex = 0; vertex < this->vertices.size(); vertex++)
            GenerateElements(this->elements, &this->vertices[vertex], nullptr, &this->normals[vertex]);
	}
};

#endif //MINI_BILLIARD_TABLEMODEL_HPP

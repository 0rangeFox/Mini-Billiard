//
// Created by Tiago Mendes on 21/05/2024.
//

#ifndef MINI_BILLIARD_TABLEMODEL_HPP
#define MINI_BILLIARD_TABLEMODEL_HPP

#include "../classes/ObjectRenderable.h"
#include "../utils/ObjectUtil.hpp"

class TableModel: public ObjectRenderable {
public:
	TableModel(float width = 12.5f, float height = 1.5f, float length = 22.5f): ObjectRenderable(ObjectType::TABLE) {
		this->files = {
			{ FileType::VERTEX_SHADER, "shaders/table.vert" },
			{ FileType::FRAGMENT_SHADER, "shaders/table.frag" }
		};

        this->position.y = -3.f;
		this->vertices = {
			// Frente
            { -width, -height, length },
            { width, -height, length },
            { width, height, length },
            { -width, height, length },

			// Trás
            { -width, -height, -length },
            { -width, height, -length },
            { width, height, -length },
            { width, -height, -length },

			// Lado Esquerdo
            { -width, -height, length },
            { -width, height, length },
            { -width, height, -length },
            { -width, -height, -length },

			// Lado Direito
            { width, -height, length },
            { width, -height, -length },
            { width, height, -length },
            { width, height, length },

			// Lado de cima
            { -width, height, length },
            { width, height, length },
            { width, height, -length },
            { -width, height, -length },

			// Lado de baixo
            { -width, -height, length },
            { -width, -height, -length },
            { width, -height, -length },
            { width, -height, length }
		};

		this->normals = {
			// Frente
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },
            { 0.f, 0.f, 1.f },

			// Trás
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },
            { 0.f, 0.f, -1.f },

			// Lado Esquerdo
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },
            { 1.f, 0.f, 0.f },

			// Lado Direito
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },
            { -1.f, 0.f, 0.f },

			// Lado de cima
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },
            { 0.f, 1.f, 0.f },

			// Lado de baixo
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f },
            { 0.f, -1.f, 0.f }
		};

        this->indices = {
			// Face frontal
			0, 1, 2,
			2, 3, 0,

			// Face traseira
			4, 5, 6,
			6, 7, 4,

			// Face direita
			8, 9, 10,
			10, 11, 8,

			// Face esquerda
			12, 13, 14,
			14, 15, 12,

			// Face superior
			16, 17, 18,
			18, 19, 16,

			// Face inferior
			20, 21, 22,
			22, 23, 20
		};

        for (int index = 0; index < this->vertices.size(); index++)
            GenerateElements(this->elements, &this->vertices[index], nullptr, &this->normals[index]);
	}
};

#endif //MINI_BILLIARD_TABLEMODEL_HPP

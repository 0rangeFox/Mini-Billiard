﻿//
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

		this->vertices = {
			// Frente
			glm::vec3(-width, -height, length),
			glm::vec3(width, -height, length),
			glm::vec3(width, height, length),
			glm::vec3(-width, height, length),

			// Trás
			glm::vec3(-width, -height, -length),
			glm::vec3(-width, height, -length),
			glm::vec3(width, height, -length),
			glm::vec3(width, -height, -length),

			// Lado Esquerdo
			glm::vec3(-width, -height, length),
			glm::vec3(-width, height, length),
			glm::vec3(-width, height, -length),
			glm::vec3(-width, -height, -length),

			// Lado Direito
			glm::vec3(width, -height, length),
			glm::vec3(width, -height, -length),
			glm::vec3(width, height, -length),
			glm::vec3(width, height, length),

			// Lado de cima
			glm::vec3(-width, height, length),
			glm::vec3(width, height, length),
			glm::vec3(width, height, -length),
			glm::vec3(-width, height, -length),

			// Lado de baixo
			glm::vec3(-width, -height, length),
			glm::vec3(-width, -height, -length),
			glm::vec3(width, -height, -length),
			glm::vec3(width, -height, length)
		};

		this->normals = {
			// Frente
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.0f, 0.0f, 1.0f),

			// Trás
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),

			// Lado Esquerdo
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),

			// Lado Direito
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-1.0f, 0.0f, 0.0f),

			// Lado de cima
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),

			// Lado de baixo
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.0f, -1.0f, 0.0f)
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

        #define VERTICES 3
        for (int face = 0; face < this->indices.size(); face += VERTICES)
            for (int vertex = face; vertex < VERTICES; vertex++)
                GenerateElements(this->elements, &this->vertices[vertex], nullptr, &this->normals[vertex]);
	}
};

#endif //MINI_BILLIARD_TABLEMODEL_HPP

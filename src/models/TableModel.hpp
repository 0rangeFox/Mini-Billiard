//
// Created by João Fernandes on 14/05/2024.
//

#ifndef MINI_BILLIARD_TABLE_HPP
#define MINI_BILLIARD_TABLE_HPP

#include "../classes/ObjectRenderable.h"
#include "../utils/ObjectUtil.hpp"

class TableModel : public ObjectRenderable {
public:
	TableModel(): ObjectRenderable(ObjectType::TABLE) {

		this->files = std::unordered_map<FileType, File>{
			{ FileType::VERTEX_SHADER, "shaders/table.vert" },
			{ FileType::FRAGMENT_SHADER, "shaders/table.frag" }
		};

		float tH = 3.0f;    // Valores posteriormente divididos por 2,
		float tW = 25.0f;        // sendo que os v�rtice mais longe um do outro s�o esse valor 
		float tL = 35.0f;
		float poolW = tW / 2;
		float poolH = tH / 2;
		float poolL = tL / 2;


		this->vertices = {
			// Frente
			glm::vec3(-poolW, -poolH, poolL),
			glm::vec3(poolW, -poolH, poolL),
			glm::vec3(poolW, poolH, poolL),
			glm::vec3(-poolW, poolH, poolL),

			// Trás
			glm::vec3(-poolW, -poolH, -poolL),
			glm::vec3(-poolW, poolH, -poolL),
			glm::vec3(poolW, poolH, -poolL),
			glm::vec3(poolW, -poolH, -poolL),

			// Lado Esquerdo
			glm::vec3(-poolW, -poolH, poolL),
			glm::vec3(-poolW, poolH, poolL),
			glm::vec3(-poolW, poolH, -poolL),
			glm::vec3(-poolW, -poolH, -poolL),

			// Lado Direito
			glm::vec3(poolW, -poolH, poolL),
			glm::vec3(poolW, -poolH, -poolL),
			glm::vec3(poolW, poolH, -poolL),
			glm::vec3(poolW, poolH, poolL),

			// Lado de cima
			glm::vec3(-poolW, poolH, poolL),
			glm::vec3(poolW, poolH, poolL),
			glm::vec3(poolW, poolH, -poolL),
			glm::vec3(-poolW, poolH, -poolL),

			// Lado de baixo 
			glm::vec3(-poolW, -poolH, poolL),
			glm::vec3(-poolW, -poolH, -poolL),
			glm::vec3(poolW, -poolH, -poolL),
			glm::vec3(poolW, -poolH, poolL)
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
			
		/*for (auto face : this->indices) 
			for (int i = face; i < 3; ++i) 
				GenerateElements(this->elements, this->vertices[i], this->uvs[i], this->normals[i]);*/
	}
};


#endif //MINI_BILLIARD_TABLE_HPP

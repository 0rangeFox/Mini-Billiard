//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_H
#define MINI_BILLIARD_OBJECTRENDERABLE_H

#include "../app/Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../classes/File.h"
#include "../classes/Material.h"
#include "../classes/Shader.h"
#include "../classes/ObjectType.h"

class ObjectRenderable {
public:
    ObjectRenderable(const ObjectType&, const std::string&);
    ObjectRenderable(const ObjectType&, const std::string&, const std::unordered_map<FileType, File>&);
    ~ObjectRenderable();

    template<FileType T>
    const File& getResource() { return this->files[T]; }
    const File& getResource(FileType type) { return this->files[type]; }
    bool addResource(FileType type, const File& file) { return this->files.insert(std::make_pair(type, file)).second; }
    bool removeResource(FileType type) { return this->files.erase(type) == 1; }

    GLuint getTotalElements() const { return this->vertices.size() * 3 + this->normals.size() * 3 + this->uvs.size() * 2; }

    bool assemble(ApplicationPtr);
    void render(ApplicationPtr) const;

private:
    bool isInitialized;
    std::unordered_map<FileType, File> files{};
    ObjectType type;
    MaterialPtr material = nullptr;
    GLuint* indices = nullptr;
    GLfloat* elements = nullptr;
    GLuint shader, texture;
    std::vector<glm::vec3> vertices{}, normals{};
    std::vector<glm::vec2> uvs{};

    bool generateIndices();
    bool generateElements();
    bool generateShaders();
    bool generateTextures(ApplicationPtr);
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_H

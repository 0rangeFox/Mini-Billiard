//
// Created by João Fernandes on 16/05/2024.
//

#ifndef MINI_BILLIARD_OBJECTRENDERABLE_H
#define MINI_BILLIARD_OBJECTRENDERABLE_H

#include "../app/Application.h"
#include "Object.h"
#include "File.h"
#include "Material.h"
#include "Shader.h"
#include "ObjectType.h"

class ObjectRenderable: Object {
public:
    ObjectRenderable(const ObjectType&);
    ObjectRenderable(const ObjectType&, const std::string&);
    ObjectRenderable(const ObjectType&, const std::string&, const std::unordered_map<FileType, File>&);
    ~ObjectRenderable();

    template<FileType T>
    const File& getResource() { return this->files[T]; }
    const File& getResource(FileType type) { return this->files[type]; }
    bool addResource(FileType type, const File& file) { return this->files.insert(std::make_pair(type, file)).second; }
    bool removeResource(FileType type) { return this->files.erase(type) == 1; }

    bool assemble(ApplicationPtr);
    void render(ApplicationPtr) const;

protected:
    std::unordered_map<FileType, File> files{};

    ObjectType type;

    std::vector<glm::vec3> vertices{}, normals{};
    std::vector<glm::vec2> uvs{};
    std::vector<GLuint> indices{};
    std::vector<GLfloat> elements{};

private:
    bool isInitialized;

    MaterialPtr material = nullptr;
    GLuint shader, texture;

    bool generateShaders();
    bool generateTextures(ApplicationPtr);
};

#endif //MINI_BILLIARD_OBJECTRENDERABLE_H

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>

using namespace glm;
using namespace std;
bool loadObj(const char* file, vector<unsigned short>& indices,
    vector<glm::vec3>& vertices,
    vector<glm::vec2>& uv,
    vector<glm::vec3>& normals)
{
    Assimp::Importer* importer = new Assimp::Importer();

    importer->ReadFile(file, aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace | aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices);

    if (!importer->GetScene())
    {
        cout << "Error loading mesh: " << file << ". " << importer->GetErrorString();
        return false;
    }

    const aiScene *scene = importer->GetScene();
    for (unsigned int meshI = 0; meshI < scene->mNumMeshes; ++meshI)
    {
        aiMesh *mesh = scene->mMeshes[meshI];

        aiFace *faces = mesh->mFaces;

        for (unsigned int faceI = 0; faceI < mesh->mNumFaces; ++faceI)
        {
            indices.push_back(faces[faceI].mIndices[0]);
            indices.push_back(faces[faceI].mIndices[1]);
            indices.push_back(faces[faceI].mIndices[2]);
        }

        aiVector3D *v = mesh->mVertices;
        aiVector3D *t = mesh->mTextureCoords[0];
        aiVector3D *n = mesh->mNormals;

        for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
        {

            vertices.push_back(glm::vec3(v[i][0], v[i][1], v[i][2]));
            uv.push_back(glm::vec2(t[i][0], t[i][1]));
            normals.push_back(glm::vec3(n[i][0], n[i][1], n[i][2]));
        }
    }

    delete importer;
    importer = NULL;

    return true;
}
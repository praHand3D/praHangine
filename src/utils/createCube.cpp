#include "prahangine/utils.h"
#include "pr4/AssetSystem.h"
#include "pr4/types.h"
#include "pr4/config.h"
#include "math/Matrix.h"


void createCube() {
    AssetSystem writer;

    Mesh mesh;
    mesh.id = 1;

    mesh.vertexes.emplace_back(0,1,0);
    mesh.vertexes.emplace_back(1,1,0);
    mesh.vertexes.emplace_back(0,0,0);
    mesh.vertexes.emplace_back(1,0,0);

    mesh.vertexes.emplace_back(0,1,1);
    mesh.vertexes.emplace_back(1,1,1);
    mesh.vertexes.emplace_back(0,0,1);
    mesh.vertexes.emplace_back(1,0,1);

    mesh.indices.emplace_back(0,1,2);
    mesh.indices.emplace_back(1,2,3);
    mesh.indices.emplace_back(4,5,6);
    mesh.indices.emplace_back(5,6,7);
    mesh.indices.emplace_back(0,1,4);
    mesh.indices.emplace_back(1,4,5);
    mesh.indices.emplace_back(2,3,6);
    mesh.indices.emplace_back(3,6,7);
    mesh.indices.emplace_back(0,2,4);
    mesh.indices.emplace_back(2,4,6);
    mesh.indices.emplace_back(1,3,5);
    mesh.indices.emplace_back(3,5,7);

    writer.header.mesh_count = 1;
    writer.meshes.push_back(mesh);

    Transform transform = Transform(
        Vec3(-0.5, -0.5, -0.5),
        Vec4(0,0,0,1),
        Vec3(1,1,1));

    Object object = Object(1, 1, transform); // nie wiem czy mesh_ref powinien byc od 0 czy 1
    writer.header.object_count = 1;
    writer.objects.push_back(object);

    std::string path = DATA_PATH + "cube.PR4";

    writer.write(path.c_str());
}
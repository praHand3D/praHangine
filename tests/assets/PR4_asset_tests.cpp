#include <fstream>

#include "gtest/gtest.h"
#include "pr4/config.h"
#include "pr4/AssetSystem.h"

const std::string ASSET_TEST_DIR = DATA_PATH + "test/";

TEST(PR4_WRITE, WRITE_DATA_PROBLEM) {
    AssetSystem assetSystem;

    Mesh mesh;
    mesh.id = 1;

    mesh.vertexes.emplace_back(1.0f, 2.0f, 3.0f);
    mesh.vertexes.emplace_back(4.0f, 5.0f, 6.0f);
    mesh.indices.emplace_back(0, 1, 0);

    assetSystem.meshes.push_back(mesh);
    assetSystem.header.mesh_count = 1;

    std::string path = ASSET_TEST_DIR + "test_data.PR4";
    EXPECT_EQ(assetSystem.write(path.c_str()), PR4_WRITER_ERROR::OK);
}

TEST(PR4_WRITE, EMPTY_DATA) {
    std::string path = ASSET_TEST_DIR + "test.PR4";
    EXPECT_EQ(AssetSystem().write(path.c_str()), PR4_WRITER_ERROR::OK);

    AssetSystem assetSystem;
    EXPECT_EQ(assetSystem.load(path.c_str()), PR4_LOAD_ERROR::OK);

    EXPECT_EQ(assetSystem.header.mesh_count, 0);
    EXPECT_EQ(assetSystem.header.object_count, 0);
    EXPECT_EQ(assetSystem.header.animation_count, 0);

    EXPECT_EQ(assetSystem.meshes.size(), 0);
    EXPECT_EQ(assetSystem.objects.size(), 0);
    EXPECT_EQ(assetSystem.animations.size(), 0);
}

TEST(PR4_WRITE, BAD_EXTENSION) {
    std::string path = ASSET_TEST_DIR + "test.noPR4";
    EXPECT_EQ(AssetSystem().write(path.c_str()), PR4_WRITER_ERROR::INVALID_EXTENSION);
}

TEST(PR4_LOAD, PASS) {
    AssetSystem writer;

    Mesh mesh;
    mesh.id = 1;
    mesh.vertexes.emplace_back(1.0f, 2.0f, 3.0f);
    mesh.vertexes.emplace_back(4.0f, 5.0f, 6.0f);
    mesh.indices.emplace_back(0, 1, 0);

    writer.meshes.push_back(mesh);
    writer.header.mesh_count = 1;

    std::string path = ASSET_TEST_DIR + "test_load.PR4";
    ASSERT_EQ(writer.write(path.c_str()), PR4_WRITER_ERROR::OK);

    AssetSystem reader;
    ASSERT_EQ(reader.load(path.c_str()), PR4_LOAD_ERROR::OK);

    EXPECT_EQ(reader.header.mesh_count, 1);
    EXPECT_EQ(reader.meshes.size(), 1);
    EXPECT_EQ(reader.meshes[0].id, 1);
    EXPECT_EQ(reader.meshes[0].vertexes.size(), 2);
    EXPECT_FLOAT_EQ(reader.meshes[0].vertexes[0].position.x, 1.0f);
    EXPECT_FLOAT_EQ(reader.meshes[0].vertexes[0].position.y, 2.0f);
    EXPECT_FLOAT_EQ(reader.meshes[0].vertexes[0].position.z, 3.0f);
    EXPECT_FLOAT_EQ(reader.meshes[0].vertexes[1].position.x, 4.0f);
    EXPECT_EQ(reader.meshes[0].indices.size(), 1);
    EXPECT_EQ(reader.meshes[0].indices[0].vertexes_index[0], 0);
}

TEST(PR4_LOAD, EMPTY_BAD_EXTENSION) {
    std::string path = ASSET_TEST_DIR + "test.noPR4";
    EXPECT_EQ(AssetSystem().write(path.c_str()), PR4_WRITER_ERROR::INVALID_EXTENSION);
}

TEST(PR4_LOAD, BAD_MAGIC) {
    std::string path = ASSET_TEST_DIR + "bad_magic.PR4";
    std::ofstream file(path, std::ios::binary);
    uint8_t bad_magic[4] = {0x00, 0x00, 0x00, 0x00};
    file.write(reinterpret_cast<char*>(bad_magic), 4);
    file.close();

    AssetSystem assetSystem;
    EXPECT_EQ(assetSystem.load(path.c_str()), PR4_LOAD_ERROR::INVALID_MAGIC);
}

TEST(PR4_LOAD, BAD_VERSION) {
    std::string path = ASSET_TEST_DIR + "bad_version.PR4";
    std::ofstream file(path, std::ios::binary);
    file.write(reinterpret_cast<const char*>(PR4_MAGIC), 4);
    uint8_t bad_version = 99;
    file.write(reinterpret_cast<const char*>(&bad_version), 1);
    file.close();

    AssetSystem assetSystem;
    EXPECT_EQ(assetSystem.load(path.c_str()), PR4_LOAD_ERROR::INVALID_VERSION);
}
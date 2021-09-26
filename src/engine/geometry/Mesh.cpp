#include "Mesh.h"

#include "engine/base/Macros.h"
#include "BoundingBox.h"

namespace urus {
    // ------------------------------------------------------------------------
    // Mesh
    // ------------------------------------------------------------------------

    const std::string Mesh::MeshData::kVerticesKey = "vertices";
    const std::string Mesh::MeshData::kVertexColorsKey = "vertexColors";
    const std::string Mesh::MeshData::kVertexNormalsKeys = "vertexNormals";

    // Mesh is an abstract class, but we must provide the dtor definition.
    Mesh::~Mesh() = default;

    bool Mesh::isEmpty() const {
        return hasVertices() || hasNormals() || hasVertexColors();
    }

    mq::vec3 Mesh::getMinBound() const {
        // TODO: impl
        return mq::vec3();
    }

    mq::vec3 Mesh::getMaxBound() const {
        // TODO: impl
        return mq::vec3();
    }

    mq::vec3 Mesh::getCenter() const {
        // TODO: impl
        return mq::vec3();
    }

    AxisAlignedBoundingBox Mesh::getAxisAlignedBoundingBox() const {
        // TODO: impl
        return AxisAlignedBoundingBox();
    }

    OrientedBoundingBox Mesh::getOrientedBoundingBox() const {
        // TODO: impl
        return OrientedBoundingBox();
    }

    void Mesh::transform(const mq::mat4 transformation) {
        // TODO: impl
    }

    void Mesh::translate(const mq::vec3 translation, bool relative) {
        // TODO: impl
    }

    void Mesh::scale(float scale, mq::vec3 center) {
        // TODO: impl
    }

    void Mesh::rotate(const mq::mat3& R, const mq::vec3& center) {
        // TODO: impl
    }

    void Mesh::paintUniformColor(const mq::vec3& color) {
        // TODO: impl
    }

    void Mesh::normalizeNormals() {
        // TODO: impl
    }

    void Mesh::clear() {
        mMeshData.mVertices.clear();
        UNUSED(mMeshData.mVertexColors);
        UNUSED(mMeshData.mVertexNormals);
    }

    // ------------------------------------------------------------------------
    // TriangleMesh
    // ------------------------------------------------------------------------

    TriangleMesh::TriangleMesh(const std::vector<mq::vec3>& vertices,
        const std::vector<mq::ivec3> triangles)
        : Mesh(vertices), mTriangles(triangles) {}

    TriangleMesh& TriangleMesh::operator+= (const TriangleMesh& rhs) {
        // TODO: provide imple - merge the two meshes.
        return (*this);
    }

    TriangleMesh TriangleMesh::operator+ (const TriangleMesh& rhs) const {
        auto temp(*this);
        temp += rhs;
        return temp;
    }

    void TriangleMesh::clear() {
        Mesh::clear();
        mTriangles.clear();
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::computeConvexCull() const {
        // TODO: impl
        // Implement Qhull
        // http://www.qhull.org/
        return nullptr;
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::createBox(
        float width, float height, float depth) {
        // TODO: impl
        return nullptr;
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::createArrow(
        float cylinderRadius, float cylinderHeight, float coneRadius,
        float coneHeight, int resolution, int cylinderSplit, int coneSplit) {
        // TODO: impl
        return nullptr;
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::createCoordinateFrame(
        float size, const mq::vec3& origin) {
        // TODO: impl
        return nullptr;
    }

}; // namespace urus

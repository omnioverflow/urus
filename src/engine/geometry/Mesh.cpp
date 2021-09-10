#include "Mesh.h"

#include "BoundingBox.h"

namespace urus {
    // ------------------------------------------------------------------------
    // Mesh
    // ------------------------------------------------------------------------

    bool Mesh::isEmpty() const {
        return hasVertices() || hasNormals() || hasVertexColors();
    }

    mq::vec3 Mesh::getMinBound() const {
        // TODO: impl
    }

    mq::vec3 Mesh::getMaxBound() const {
        // TODO: impl
    }

    mq::vec3 Mesh::getCenter() const {
        // TODO: impl
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

    void Mesh::translate(const mq::vec3 translation, bool relative = true) {
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
        mVertices.clear();
        mVertexColors.clear();
        mVertexNormals.clear();
    }

    // ------------------------------------------------------------------------
    // TriangleMesh
    // ------------------------------------------------------------------------

    TriangleMesh::TriangleMesh(const std::vector<mq::vec3>& vertices,
        const std::vector<mq::ivec3> triangles)
        : Mesh(vertices), mTriangles(triangles) {}

    void TriangleMesh::clear() {
        mTriangles.clear();
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::computeConvexCull() const {
        // TODO: impl
        // Implement Qhull
        // http://www.qhull.org/
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::createBox(float width,
        float height, float depth) {
        // TODO: impl
        return nullptr;
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::createArrow(float cylinderRadius,
        float cylinderHeight, float coneRadius, float coneHeight,
        int resolution, int cylinderSplit, int coneSplit) {
        // TODO: impl
    }

    std::shared_ptr<TriangleMesh> TriangleMesh::createCoordinateFrame(float size,
        const mq::vec3& origin) {
        // TODO: impl
    }

}; // namespace urus
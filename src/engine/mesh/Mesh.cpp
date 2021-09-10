#include "Mesh.h"

namespace urus {
    bool Mesh::isEmpty() const {
        return hasVertices() || hasNormals() || hasVertexColors();
    }

    void Mesh::paintUniformColor(const mq::vec3& color) {

    }
}; // namespace urus
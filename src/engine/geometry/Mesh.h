#pragma once

#include <memory>
#include <string>
#include <vector>

#include "mqMath/Mat.h"
#include "mqMath/Vec3.h"

// Inspired by mesh interfaces from Open3d.
// Example, check out the following:
// http://www.open3d.org/docs/0.12.0/cpp_api/classopen3d_1_1geometry_1_1_mesh_base.html
// http://www.open3d.org/docs/0.12.0/cpp_api/classopen3d_1_1geometry_1_1_triangle_mesh.html

namespace urus {
    class AxisAlignedBoundingBox;
    class OrientedBoundingBox;

// -----------------------------------------------------------------------------
// Mesh
// -----------------------------------------------------------------------------

    class Mesh {
    private:
        struct MeshData {
            static const std::string kVerticesKey;
            static const std::string kVertexColorsKey;
            static const std::string kVertexNormalsKeys;

            MeshData(const std::vector<mq::vec3>& vertices) : mVertices(vertices) {}
            MeshData(const std::vector<mq::vec3>& vertices,
                const std::vector<mq::vec3>& vertexColors)
                : mVertices(vertices)
                , mVertexColors(vertexColors) {}
            std::vector<mq::vec3> mVertices;
            std::vector<mq::vec3> mVertexColors;
            std::vector<mq::vec3> mVertexNormals;
        };
        struct MeshCache {

        };
    public: 
        Mesh(const std::vector<mq::vec3> vertices) : mMeshData(vertices) {}
        virtual ~Mesh() = 0;
        // Follow rule of 5 in C++11, since destructor is explicitly declared.
        Mesh(const Mesh&) = default;
        Mesh& operator=(const Mesh&) = default;
        Mesh(Mesh&&) = default;
        Mesh& operator=(Mesh&&) = default;
     
        bool isEmpty() const;
        bool hasVertices() const { return !mMeshData.mVertices.empty(); }
        bool hasNormals() const { return !mMeshData.mVertexNormals.empty(); }
        bool hasVertexColors() const { return !mMeshData.mVertexColors.empty(); }

        mq::vec3 getMinBound() const;
        mq::vec3 getMaxBound() const;
        mq::vec3 getCenter() const;

        AxisAlignedBoundingBox getAxisAlignedBoundingBox() const;
        OrientedBoundingBox getOrientedBoundingBox() const;

        void transform(const mq::mat4 transformation);
        void translate(const mq::vec3 translation, bool relative=true);
        void scale(float scale, mq::vec3 center);
        void rotate(const mq::mat3& R, const mq::vec3& center);

        void paintUniformColor(const mq::vec3& color);
        void normalizeNormals();

        // virtual methods:

        virtual void clear();

    protected:
        MeshData mMeshData;
        MeshCache mMeshCache;
    }; // class Mesh
    

// -----------------------------------------------------------------------------
// TriangleMesh
// -----------------------------------------------------------------------------

    class TriangleMesh : public Mesh {
    public:
        TriangleMesh(
            const std::vector<mq::vec3>& vertices,
            const std::vector<mq::ivec3> triangles
        );

        virtual ~TriangleMesh() = default;

        TriangleMesh& operator+= (const TriangleMesh& rhs);
        TriangleMesh operator+ (const TriangleMesh& rhs) const;

        virtual void clear() override;

        std::shared_ptr<TriangleMesh> computeConvexCull() const;
      
    public: // public static
        static std::shared_ptr<TriangleMesh> createBox(
            float width = 1.0f,
            float height = 1.0f,
            float depth = 1.0f
        );

        static std::shared_ptr<TriangleMesh> createArrow(
            float cylinderRadius = 1.0f,
            float cylinderHeight = 5.0f,
            float coneRadius = 1.0f,
            float coneHeight = 4.0f,
            int resolution = 20,
            int cylinderSplit = 4,
            int coneSplit = 1            
        );

        static std::shared_ptr<TriangleMesh> createCoordinateFrame(
            float size = 1.0f,
            const mq::vec3& origin = mq::vec3::getZero()
        );

    private:
        std::vector<mq::ivec3> mTriangles; // triangles
    }; // class TriangleMesh

} // namespace urus
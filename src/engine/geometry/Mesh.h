#pragma once

#include <memory>
#include <vector>

#include "mqMath/Mat.h"
#include "mqMath/Mat4.h"
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
    public: 
        Mesh() = default;
        Mesh(const std::vector<mq::vec3> vertices) : mVertices(vertices) {}
        virtual ~Mesh() = 0;
        // Follow rule of 5 in C++11, since destructor is explicitly declared.
        Mesh(const Mesh&) = default;
        Mesh& operator=(const Mesh&) = default;
        Mesh(Mesh&&) = default;
        Mesh& operator=(Mesh&&) = default;

        // TODO:
        // check this out https://en.cppreference.com/w/cpp/language/operators
        // regarding using friends when overloading arithmetic operators.
        Mesh& operator+=(const Mesh& rhs);
        const Mesh& operator+(const Mesh& rhs);        

        bool isEmpty() const;
        bool hasVertices() const { return !mVertices.empty(); }
        bool hasNormals() const { return !mVertexNormals.empty(); }
        bool hasVertexColors() const { return !mVertexColors.empty(); }

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
        std::vector<mq::vec3> mVertices;
        std::vector<mq::vec3> mVertexColors;
        std::vector<mq::vec3> mVertexNormals;
    }; // class Mesh
    

// -----------------------------------------------------------------------------
// TriangleMesh
// -----------------------------------------------------------------------------

    class TriangleMesh : public Mesh {
    public:
        TriangleMesh() = default;
        TriangleMesh(
            const std::vector<mq::vec3>& vertices,
            const std::vector<mq::ivec3> triangles
        );

        virtual void clear() override;

        std::shared_ptr<TriangleMesh> computeConvexCull() const;
      
    public: // public static
        static std::shared_ptr<TriangleMesh> createBox(
            float width = 1.0f,
            float height = 1.0f,
            float depth = 1.0f);

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
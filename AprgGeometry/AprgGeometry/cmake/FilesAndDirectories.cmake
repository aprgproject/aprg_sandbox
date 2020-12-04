set(APRG_GEOMETRY_INCLUDE_DIRECTORIES
    ${APRG_GEOMETRY_DIR}/src
)

set(APRG_GEOMETRY_TEST_INCLUDE_DIRECTORIES
    ${APRG_GEOMETRY_DIR}/tst
)

set(APRG_GEOMETRY_SOURCES
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Circle.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Circle.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Line.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Line.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Parabola.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Parabola.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Point.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Point.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Polygon.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Polynomial.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Quadrilateral.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Quadrilateral.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Rectangle.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Rectangle.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Triangle.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/Triangle.hpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/TwoDimensionsHelper.cpp
    ${APRG_GEOMETRY_DIR}/src/TwoDimensions/TwoDimensionsHelper.hpp
)

set(APRG_GEOMETRY_TESTS
    ${APRG_GEOMETRY_DIR}/tst/TwoDimensions/Circle_unit.cpp
    ${APRG_GEOMETRY_DIR}/tst/TwoDimensions/Line_unit.cpp
    ${APRG_GEOMETRY_DIR}/tst/TwoDimensions/Point_unit.cpp
    ${APRG_GEOMETRY_DIR}/tst/TwoDimensions/Polygon_unit.cpp
    ${APRG_GEOMETRY_DIR}/tst/TwoDimensions/Polynomial_unit.cpp
    ${APRG_GEOMETRY_DIR}/tst/TwoDimensions/TwoDimensionsHelper_unit.cpp
)

set(APRG_GEOMETRY_SOURCES_AND_TESTS
    ${APRG_GEOMETRY_SOURCES}
    ${APRG_GEOMETRY_TESTS}
)

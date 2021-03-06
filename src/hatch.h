/*!
 * \file hatch.h
 *
 * \author Copyright (C) 2008 ... 2015 by Bert Timmerman <bert.timmerman@xs4all.nl>.
 *
 * \brief Definition of a DXF hatch entity (\c HATCH).
 *
 * \warning The hatch entity requires AutoCAD version R14 or higher.\n
 *
 * \htmlinclude "hatch.html"
 *
 * <hr>
 * <h1><b>Copyright Notices.</b></h1>\n
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.\n\n
 * This program is distributed in the hope that it will be useful, but
 * <b>WITHOUT ANY WARRANTY</b>; without even the implied warranty of
 * <b>MERCHANTABILITY</b> or <b>FITNESS FOR A PARTICULAR PURPOSE</b>.\n
 * See the GNU General Public License for more details.\n\n
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to:\n
 * Free Software Foundation, Inc.,\n
 * 59 Temple Place,\n
 * Suite 330,\n
 * Boston,\n
 * MA 02111 USA.\n
 * \n
 * Drawing eXchange Format (DXF) is a defacto industry standard for the
 * exchange of drawing files between various Computer Aided Drafting
 * programs.\n
 * DXF is an industry standard designed by Autodesk(TM).\n
 * For more details see http://www.autodesk.com.
 * <hr>
 */


#ifndef LIBDXF_SRC_HATCH_H
#define LIBDXF_SRC_HATCH_H


#include <math.h>

#include "global.h"
#include "point.h"


#define DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS 16
#define DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS 64


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge arc.
 */
typedef struct
dxf_hatch_boundary_path_edge_arc
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * X-value of center point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of center point coordinate. */
        double radius;
                /*!< group code = 40. */
        double start_angle;
                /*!< group code = 50. */
        double end_angle;
                /*!< group code = 51. */
        int is_ccw;
                /*!< group code = 73\n
                 * arc is counterclockwise flag. */
        struct DxfHatchBoundaryPathEdgeArc *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeArc.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeArc. */
} DxfHatchBoundaryPathEdgeArc;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge ellipse.
 */
typedef struct
dxf_hatch_boundary_path_edge_ellipse
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * X-value of center point coordinate. */
        double y0;
                /*!< group code = 20\n
                 * Y-value of center point coordinate. */
        double x1;
                /*!< group code = 11\n
                 * X-value of end point coordinate of major axis (relative to
                 * center point. */
        double y1;
                /*!< group code = 21\n
                 * Y-value of end point coordinate of major axis (relative to
                 * center point. */
        double minor_axis;
                /*!< group code = 40\n
                 * length of minor axis (percentage of major axis length). */
        double start_angle;
                /*!< group code = 50. */
        double end_angle;
                /*!< group code = 51. */
        int is_ccw;
                /*!< group code = 73\n
                 * ellipse is counterclockwise flag. */
        struct DxfHatchBoundaryPathEdgeEllipse *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeEllipse.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeEllipse. */
} DxfHatchBoundaryPathEdgeEllipse;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge line.
 */
typedef struct
dxf_hatch_boundary_path_edge_line
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = = 10\n
                 * start point X-value. */
        double y0;
                /*!< group code = 20\n
                 * start point Y-value. */
        double x1;
                /*!< group code = 11\n
                 * end point X-value. */
        double y1;
                /*!< group code = 21\n
                 * end point Y-value. */
        struct DxfHatchBoundaryPathEdgeLine *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeLine.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeLine. */
} DxfHatchBoundaryPathEdgeLine;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge spline
 * control point.
 */
typedef struct
dxf_hatch_boundary_path_edge_spline_cp
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        double weight;
                /*!< group code = 42\n
                 * optional, defaults to 1.0. */
        struct DxfHatchBoundaryPathEdgeSplineCp *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSplineCp. */
} DxfHatchBoundaryPathEdgeSplineCp;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge spline.
 */
typedef struct
dxf_hatch_boundary_path_edge_spline
{
        int id_code;
                /*!< group code = 5. */
        int degree;
                /*!< group code = 94. */
        int rational;
                /*!< group code = 73. */
        int periodic;
                /*!< group code = 74. */
        int number_of_knots;
                /*!< group code = 95\n
                 * number of knots. */
        double knots[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS];
                /*!< group code = 40\n
                 * knot values control the shape of the curve as it
                 * passes through the control points. */
        int number_of_control_points;
                /*!< group code = 96\n
                 * number of control points. */
        struct DxfHatchBoundaryPathEdgeSplineCp *control_points;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeSplineCp.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeSplineCp
                 * in the DxfHatchBoundaryPathEdgeSpline. */
        struct DxfHatchBoundaryPathEdgeSpline *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdgeSpline. */
} DxfHatchBoundaryPathEdgeSpline;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path edge
 * (composite of arcs, ellipses, lines or splines).
 */
typedef struct
dxf_hatch_boundary_path_edge
{
        int id_code;
                /*!< group code = 5.\n
                 * Treat the boundary path edge as if it were a single
                 * (composite) entity. */
        struct DxfHatchBoundaryPathEdgeArc *arcs;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeArc.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeArc in
                 * the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeEllipse *ellipses;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeEllipse.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeEllipse
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeLine * lines;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeLine.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeLine
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdgeSpline *splines;
                /*!< pointer to the first DxfHatchBoundaryPathEdgeSpline.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdgeSpline
                 * in the DxfHatchBoundaryPathEdge. */
        struct DxfHatchBoundaryPathEdge *next;
                /*!< pointer to the next DxfHatchBoundaryPathEdge.\n
                 * \c NULL if the last DxfHatchBoundaryPathEdge. */
} DxfHatchBoundaryPathEdge;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path polyline
 * vertex.
 */
typedef struct
dxf_hatch_boundary_path_polyline_vertex
{
        int id_code;
                /*!< group code = 5.*/
        double x0;
                /*!< group code = 10. */
        double y0;
                /*!< group code = 20. */
        struct DxfHatchBoundaryPathPolylineVertex *next;
                /*!< pointer to the next DxfHatchBoundaryPathPolylineVertex.\n
                 * \c NULL if the last DxfHatchBoundaryPathPolylineVertex. */
} DxfHatchBoundaryPathPolylineVertex;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path polyline.
 */
typedef struct
dxf_hatch_boundary_path_polyline
{
        int id_code;
                /*!< group code = 5. */
        double bulge;
                /*!< group code = 42.\n
                 * optional, default = 0. */
        int has_bulge;
                /*!< group code = 72. */
        int is_closed;
                /*!< group code = 73. */
        int number_of_vertices;
                /*!< group code = 93\n
                 * number of polyline vertices in
                 * DxfHatchBoundaryPathPolyline. */
        struct DxfHatchBoundaryPathPolylineVertex *vertices;
                /*!< pointer to the first
                 * DxfHatchBoundaryPathPolylineVertex.\n
                 * \c NULL if there is no
                 * DxfHatchBoundaryPathPolylineVertex in the
                 * DxfHatchBoundaryPathPolyline. */
        struct DxfHatchBoundaryPathPolyline *next;
                /*!< pointer to the next DxfHatchBoundaryPathPolyline.\n
                 * \c NULL if the last DxfHatchBoundaryPathPolyline. */
} DxfHatchBoundaryPathPolyline;


/*!
 * \brief DXF definition of an AutoCAD hatch boundary path (or loop)
 * (composite of a closed series of edges, and/or a polyline).
 */
typedef struct
dxf_hatch_boundary_path
{
        int id_code;
                /*!< group code = 5.\n
                 * Treat the boundary path as if it were a single
                 * (composite) entity. */
        struct DxfHatchBoundaryPathEdge *edges;
                /*!< pointer to the first DxfHatchBoundaryPathEdge.\n
                 * \c NULL if there is no DxfHatchBoundaryPathEdge in
                 * the DxfHatchBoundaryPath. */
        struct DxfHatchBoundaryPathPolyline *polylines;
                /*!< pointer to the first DxfHatchBoundaryPathPolyline.\n
                 * \c NULL if there is no DxfHatchBoundaryPathPolyline
                 * in the DxfHatchBoundaryPath. */
        struct DxfHatchBoundaryPath *next;
                /*!< pointer to the next DxfHatchBoundaryPath.\n
                 * \c NULL if the last DxfHatchBoundaryPath. */
} DxfHatchBoundaryPath;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern definition line.
 */
typedef struct
dxf_hatch_pattern_def_line
{
        int id_code;
                /*!< group code = 5. */
        double angle;
                /*!< group code = 53\n
                 * hatch pattern line angle. */
        double x0;
                /*!< group code = 43\n
                 * hatch pattern line base point X-value. */
        double y0;
                /*!< group code = 44\n
                 * hatch pattern line base point Y-value. */
        double x1;
                /*!< group code = 45\n
                 * hatch pattern line offset point X-value. */
        double y1;
                /*!< group code = 46\n
                 * hatch pattern line offset point Y-value. */
        int dash_items;
                /*!< group code = 79\n
                 * number of hatch pattern definition line dash items. */
        double dash_length[DXF_MAX_HATCH_PATTERN_DEF_LINE_DASH_ITEMS];
                /*!< group code = 49\n
                 * array of dash lengths for an array of hatch pattern
                 * definition lines. */
        struct DxfHatchPatternDefLine *next;
                /*!< pointer to the next DxfHatchPatternDefLine.\n
                 * \c NULL if the last DxfHatchPatternDefLine. */
} DxfHatchPatternDefLine;


/*!
 * \brief DXF definition of an AutoCAD hatch seed point.
 */
typedef struct
dxf_hatch_pattern_seedpoint
{
        int id_code;
                /*!< group code = 5. */
        double x0;
                /*!< group code = 10\n
                 * seed point X-value. */
        double y0;
                /*!< group code = 20\n
                 * seed point Y-value. */
        struct DxfHatchPatternSeedPoint *next;
                /*!< pointer to the next DxfHatchSeedPoint.\n
                 * \c NULL if the last DxfHatchSeedPoint. */
} DxfHatchPatternSeedPoint;


/*!
 * \brief DXF definition of an AutoCAD hatch pattern.
 */
typedef struct
dxf_hatch_pattern
{
        int id_code;
                /*!< group code = 5. */
        int def_lines;
                /*!< group code = 78\n
                 * number of hatch pattern definition lines. */
        struct DxfHatchPatternDefLine *lines;
                /*!< pointer to the first \c DxfHatchPatterDefLine. */
        double **length;
                /*!< group code = 49\n
                 * array of dash lengths for an array of hatch pattern
                 * definition lines. */
        int number_of_seed_points;
                /*!< group code = 98\n
                 * number of seed points. */
        struct DxfHatchPatternSeedPoint *seed_points;
                /*!< pointer to the first \c DxfHatchSeedPoint. */
        struct DxfHatchPattern *next;
                /*!< pointer to the next DxfHatchPattern.\n
                 * \c NULL if the last DxfHatchPattern. */
} DxfHatchPattern;


/*!
 * \brief DXF definition of an AutoCAD hatch entity.
 */
typedef struct
dxf_hatch
{
        /* Members common for all DXF drawable entities. */
        int id_code;
                /*!< group code = 5\n
                 * Identification number for the entity.\n
                 * This is to be an unique (sequential) number in the DXF
                 * file. */
        char *linetype;
                /*!< group code = 6\n
                 * The linetype of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file. */
        char *layer;
                /*!< group code = 8\n
                 * Layer on which the entity is drawn.\n
                 * Defaults to layer "0" if no valid layername is given. */
        double elevation;
                /*!< group code = 38\n
                 * Elevation of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if omitted in the DXF file, or prior
                 * to DXF version R12, or DXF_FLATLAND equals 0 (default). */
        double thickness;
                /*!< group code = 39\n
                 * Thickness of the arc in the local Z-direction.\n
                 * Defaults to 0.0 if ommitted in the DXF file. */
        double linetype_scale;
                /*!< group code = 48\n
                 * Linetype scale (optional). */
        int16_t visibility;
                /*!< group code = 60\n
                 * Object visibility (optional): 0 = Visible; 1 = Invisible. */
        int color;
                /*!< group code = 62\n
                 * Color of the entity.\n
                 * Defaults to \c BYLAYER if ommitted in the DXF file.\n
                 * Note that entities encapsulated in a block with the
                 * color \c BYBLOCK are represented in the "native" color of
                 * the \c BLOCK entity. */
        int paperspace;
                /*!< group code = 67\n
                 * Entities are to be drawn on either \c PAPERSPACE or
                 * \c MODELSPACE.\n
                 * Optional, defaults to \c DXF_MODELSPACE (0). */
        int number_of_image_bytes;
                /*!< group code = 92\n
                 * The number of bytes in the image (and subsequent
                 * binary chunk records) (optional). */
        char *binary_graphics_data[DXF_MAX_PARAM];
                /*!< group code = 310\n
                 * Proxy entity graphics data.\n
                 * Multiple lines of 256 characters maximum per line
                 * (optional). */
        char *dictionary_owner_soft;
                /*!< group code = 330\n
                 * Soft-pointer ID/handle to owner dictionary (optional). */
        char *dictionary_owner_hard;
                /*!< group code = 360\n
                 * Hard owner ID/handle to owner dictionary (optional). */
        /* Specific members for a DXF hatch. */
        char *pattern_name;
                /*!< group code = 2. */
        double x0;
                /*!< group code = 10\n
                 * base point. */
        double y0;
                /*!< group code = 20\n
                 * base point. */
        double z0;
                /*!< group code = 30\n
                 * base point. */
        double pattern_scale;
                /*!< group code 41\n
                 * pattern fill only. */
        double pixel_size;
                /*!< group code 47 */
        double pattern_angle;
                /*!< group code 52\n
                 * pattern fill only. */
        int solid_fill;
                /*!< group code = 70\n
                 * 0 = pattern fill\n
                 * 1 = solid fill. */
        int associative;
                /*!< group code = 71\n
                 * 0 = non-associative\n
                 * 1 = associative. */
        int hatch_style;
                /*!< group code = 75\n
                 * 0 = hatch "odd parity" area (Normal style)\n
                 * 1 = hatch outermost area only (Outer style)\n
                 * 2 = hatch through entire area (Ignore style). */
        int hatch_pattern_type;
                /*!< group code = 76\n
                 * 0 = user defined\n
                 * 1 = predefined\n
                 * 2 = custom. */
        int pattern_double;
                /*!< group code = 77\n
                 * pattern fill only\n
                 * 0 = not double\n
                 * 1 = double. */
        int number_of_pattern_def_lines;
                /*!< group code = 78\n
                 * number of pattern definition lines. */
        int number_of_boundary_paths;
                /*!< group code = 91\n
                 * number of boundary paths (loops). */
        int number_of_seed_points;
                /*!< group code = 98\n
                 * number of seed points. */
        double extr_x0;
                /*!< group code = 210\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_y0;
                /*!< group code = 220\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 0.0. */
        double extr_z0;
                /*!< group code = 230\n
                 * extrusion direction\n
                 * optional, if ommited defaults to 1.0. */
        struct DxfHatchBoundaryPath *paths;
                /*!< pointer to the first DxfHatchBoundaryPath.\n
                 * \c NULL if there is no DxfHatchBoundaryPath in the
                 * DxfHatch. */
        struct DxfHatchPatternDefLine *def_lines;
                /*!< pointer to the first DxfHatchPatternDefLine.\n
                 * \c NULL if there is no DxfHatchPatternDefLine in the
                 * DxfHatch. */
        struct DxfHatchPatternSeedPoint *seed_points;
                /*!< pointer to the first DxfHatchSeedPoint. */
        struct DxfHatch *next;
                /*!< pointer to the next DxfHatch.\n
                 * \c NULL if the last DxfHatch. */
} DxfHatch;


DxfHatch *
dxf_hatch_new ();
DxfHatchPattern *
dxf_hatch_pattern_new ();
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_new ();
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_new ();
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_new ();
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_new ();
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_new ();
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_new ();
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_new ();
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_new ();
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_new ();
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_new ();
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_new ();
DxfHatch *
dxf_hatch_init
(
        DxfHatch *dxf_hatch
);
DxfHatchPattern *
dxf_hatch_pattern_init
(
        DxfHatchPattern *dxf_hatch_pattern
);
DxfHatchPatternDefLine *
dxf_hatch_pattern_def_line_init
(
        DxfHatchPatternDefLine *dxf_hatch_pattern_def_line
);
DxfHatchPatternSeedPoint *
dxf_hatch_pattern_seedpoint_init
(
        DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint
);
DxfHatchBoundaryPath *
dxf_hatch_boundary_path_init
(
        DxfHatchBoundaryPath *dxf_hatch_boundary_path
);
DxfHatchBoundaryPathPolyline *
dxf_hatch_boundary_path_polyline_init
(
        DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline
);
DxfHatchBoundaryPathPolylineVertex *
dxf_hatch_boundary_path_polyline_vertex_init
(
        DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex
);
DxfHatchBoundaryPathEdge *
dxf_hatch_boundary_path_edge_init
(
        DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge
);
DxfHatchBoundaryPathEdgeArc *
dxf_hatch_boundary_path_edge_arc_init
(
        DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc
);
DxfHatchBoundaryPathEdgeEllipse *
dxf_hatch_boundary_path_edge_ellipse_init
(
        DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse
);
DxfHatchBoundaryPathEdgeLine *
dxf_hatch_boundary_path_edge_line_init
(
        DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line
);
DxfHatchBoundaryPathEdgeSpline *
dxf_hatch_boundary_path_edge_spline_init
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline
);
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_control_point_init
(
        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp
);
int
dxf_hatch_boundary_path_edge_spline_append_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp
);
int
dxf_hatch_boundary_path_edge_spline_append_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        double knot_value
);
int
dxf_hatch_boundary_path_edge_spline_prepend_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp
);
int
dxf_hatch_boundary_path_edge_spline_prepend_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        double knot_value
);
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_get_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position
);
double
dxf_hatch_boundary_path_edge_spline_get_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position
);
int
dxf_hatch_boundary_path_edge_spline_set_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position,
        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp
);
int
dxf_hatch_boundary_path_edge_spline_set_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position,
        double knot_value
);
int
dxf_hatch_boundary_path_edge_spline_insert_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position,
        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp
);
int
dxf_hatch_boundary_path_edge_spline_insert_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position,
        double knot_value
);
int
dxf_hatch_boundary_path_edge_spline_remove_control_point
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position
);
int
dxf_hatch_boundary_path_edge_spline_remove_knot_value
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        int position
);
DxfHatchBoundaryPathEdgeSplineCp *
dxf_hatch_boundary_path_edge_spline_copy_control_points
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        DxfHatchBoundaryPathEdgeSplineCp * dxf_hatch_boundary_path_edge_spline_cp
);
int
dxf_hatch_boundary_path_edge_spline_copy_knot_values
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,
        double *knot_values[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]
);
int
dxf_hatch_write
(
        DxfFile *fp,
        DxfHatch *dxf_hatch
);
int
dxf_hatch_pattern_def_line_write
(
        DxfFile *fp,
                /*!< DXF file pointer to an output file (or device). */
        DxfHatchPatternDefLine *dxf_hatch_pattern_def_line
                /*!< DXF hatch pattern definition line. */
);
int
dxf_hatch_pattern_seedpoint_write
(
        DxfFile *fp,
        DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint
);
int
dxf_hatch_boundary_path_write
(
        DxfFile *fp,
        DxfHatchBoundaryPath *dxf_hatch_boundary_path
);
int
dxf_hatch_boundary_path_polyline_close_polyline
(
        DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline
);
int
dxf_hatch_boundary_path_polyline_point_inside_polyline
(
        DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline,
        DxfPoint *dxf_point
);
int
dxf_hatch_boundary_path_polyline_write
(
        DxfFile *fp,
        DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline
);
int
dxf_hatch_boundary_path_polyline_vertex_write
(
        DxfFile *fp,
        DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex
);
int
dxf_hatch_free
(
        DxfHatch *dxf_hatch
);
int
dxf_hatch_pattern_free
(
        DxfHatchPattern *dxf_hatch_pattern
);
int
dxf_hatch_pattern_def_line_free
(
        DxfHatchPatternDefLine *dxf_hatch_pattern_def_line
);
int
dxf_hatch_pattern_seedpoint_free
(
        DxfHatchPatternSeedPoint *dxf_hatch_pattern_seedpoint
);
int
dxf_hatch_boundary_path_free
(
        DxfHatchBoundaryPath *dxf_hatch_boundary_path
);
int
dxf_hatch_boundary_path_polyline_free
(
        DxfHatchBoundaryPathPolyline *dxf_hatch_boundary_path_polyline
);
double
dxf_hatch_boundary_path_polyline_vertex_angle
(
        DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_0,
        DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex_1
);
int
dxf_hatch_boundary_path_polyline_vertex_free
(
        DxfHatchBoundaryPathPolylineVertex *dxf_hatch_boundary_path_polyline_vertex
);
int
dxf_hatch_boundary_path_edge_free
(
        DxfHatchBoundaryPathEdge *dxf_hatch_boundary_path_edge
);
int
dxf_hatch_boundary_path_edge_arc_free
(
        DxfHatchBoundaryPathEdgeArc *dxf_hatch_boundary_path_edge_arc
);
int
dxf_hatch_boundary_path_edge_ellipse_free
(
        DxfHatchBoundaryPathEdgeEllipse *dxf_hatch_boundary_path_edge_ellipse
);
int
dxf_hatch_boundary_path_edge_line_free
(
        DxfHatchBoundaryPathEdgeLine *dxf_hatch_boundary_path_edge_line
);
int
dxf_hatch_boundary_path_edge_spline_free
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline
);
int
dxf_hatch_boundary_path_edge_spline_control_point_free
(
        DxfHatchBoundaryPathEdgeSplineCp *dxf_hatch_boundary_path_edge_spline_cp
);


#endif /* LIBDXF_SRC_HATCH_H */


/* EOF */

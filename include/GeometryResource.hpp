/******************************************************************************
 * guacamole - delicious VR                                                   *
 *                                                                            *
 * Copyright: (c) 2011-2013 Bauhaus-Universität Weimar                        *
 * Contact:   felix.lauer@uni-weimar.de / simon.schneegans@uni-weimar.de      *
 *                                                                            *
 * This program is free software: you can redistribute it and/or modify it    *
 * under the terms of the GNU General Public License as published by the Free *
 * Software Foundation, either version 3 of the License, or (at your option)  *
 * any later version.                                                         *
 *                                                                            *
 * This program is distributed in the hope that it will be useful, but        *
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License   *
 * for more details.                                                          *
 *                                                                            *
 * You should have received a copy of the GNU General Public License along    *
 * with this program. If not, see <http://www.gnu.org/licenses/>.             *
 *                                                                            *
 ******************************************************************************/

#ifndef GUA_GEOMETRY_RESOURCE_HPP
#define GUA_GEOMETRY_RESOURCE_HPP

#include <MaterialPass.hpp>

namespace gua {

class GeometryResource {
 public:

  MaterialPass get_vertex_material_pass() const {
    return gua::MaterialPass("geometry_resource_pass")
      .set_source(R"(
        layout(location=0) vec3 in_position;
        layout(location=1) vec3 in_normal;
        layout(location=2) vec2 in_texcoords;

        void geometry_resource_pass() {
          gua_position = in_position;
          gua_normal = in_normal;
          gua_texcoords = in_texcoords;
        }
      )");
  }

  MaterialPass get_fragment_material_pass() const {
    return gua::MaterialPass("geometry_resource_pass")
      .set_source(R"(
        void geometry_resource_pass() {}
      )");
  }


};

}

#endif  // GUA_GEOMETRY_RESOURCE_HPP

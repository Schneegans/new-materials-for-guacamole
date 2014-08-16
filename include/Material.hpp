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

#ifndef GUA_MATERIAL_HPP
#define GUA_MATERIAL_HPP

#include <MaterialDescription.hpp>
#include <string_utils.hpp>

#include <sstream>
#include <iostream>

namespace gua {

class Material {
 public:
  Material(MaterialDescription const& desc) {

    std::unordered_map<std::string, std::shared_ptr<UniformValueBase>> global_uniforms;

    global_uniforms["gua_view_matrix"] = std::make_shared<UniformValue<float>>(1.f);
    global_uniforms["gua_view_id"] = std::make_shared<UniformValue<int>>(43);

    auto compile_description = [global_uniforms](std::vector<MaterialPass> const& passes) {
      std::stringstream source;

      // header ----------------------------------------------------------------
      source << "#version 420" << std::endl;

      // input and g-buffer output ---------------------------------------------
      source << R"(
        vec3  gua_position;
        vec3  gua_normal;
        vec3  gua_tangent;
        vec3  gua_bitangent;
        vec2  gua_texcoords;
        vec2  gua_color;
        float gua_shinyness;
      )";

      // uniforms --------------------------------------------------------------
      source << std::endl;

      auto uniforms = global_uniforms;

      // merge uniforms
      for (auto& pass: passes) {
        uniforms.insert(pass.get_uniforms().begin(), pass.get_uniforms().end());
      }

      // print uniforms
      for (auto& uniform: uniforms) {
        source << "uniform "
               << uniform.second->get_glsl_type() << " "
               << uniform.first << ";"
               << std::endl;
      }


      // pass sources ----------------------------------------------------------
      source << std::endl;
      for (auto& pass: passes) {
        source << pass.get_source() << std::endl;
      }

      // main ------------------------------------------------------------------
      source << std::endl;
      source << "int main() {" << std::endl;

      for (auto& pass: passes) {
        source << pass.get_name() << "();" << std::endl;
      }

      source << R"(
        gl_Position = vec4();
      )";

      source << "}" << std::endl;

      return string_utils::format_code(source.str());
    };

    vertex_source_   = compile_description(desc.get_vertex_passes());
    fragment_source_ = compile_description(desc.get_fragment_passes());
  }

  void print_shaders() {
    std::cout << vertex_source_ << std::endl;
    std::cout << std::endl;
    std::cout << fragment_source_ << std::endl;
  }

 private:
  std::string vertex_source_;
  std::string fragment_source_;
};

}

#endif  // GUA_MATERIAL_HPP

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

#include <Material.hpp>

namespace gua {

Material::Material(MaterialDescription const& desc)
  : desc_(desc) {}

MaterialDescription const& Material::get_description() const {
  return desc_;
}

void Material::use(GeometryResource const& for_type) {
  auto shader(shaders_.find(typeid(for_type)));

  if (shader != shaders_.end()) {
    shader->second->use();
  } else {

    std::unordered_map<std::string, std::shared_ptr<UniformValueBase>> global_uniforms;

    global_uniforms["gua_view_matrix"] = std::make_shared<UniformValue<float>>(1.f);
    global_uniforms["gua_view_id"] = std::make_shared<UniformValue<int>>(43);

    auto compile_description = [global_uniforms](std::list<MaterialPass> const& passes, bool vertex_shader) {
      std::stringstream source;

      // header ----------------------------------------------------------------
      source << "#version 420" << std::endl;

      // input and g-buffer output ---------------------------------------------
      if (vertex_shader) {
        source << R"(
          out vec3  gua_position;
          out vec3  gua_normal;
          out vec3  gua_tangent;
          out vec3  gua_bitangent;
          out vec2  gua_texcoords;
          out vec2  gua_color;
          out float gua_shinyness;
        )";

      } else {


        source << R"(
          in vec3  gua_position;
          in vec3  gua_normal;
          in vec3  gua_tangent;
          in vec3  gua_bitangent;
          in vec2  gua_texcoords;
          in vec2  gua_color;
          in float gua_shinyness;

          out vec3  gua_gbuffer_normal;
          out vec2  gua_gbuffer_color;
          out float gua_gbuffer_shinyness;
        )";
      }

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

      // indent and return code ------------------------------------------------
      return string_utils::format_code(source.str());
    };

    auto v_passes = desc_.get_vertex_passes();
    auto f_passes = desc_.get_fragment_passes();

    v_passes.push_front(for_type.get_vertex_material_pass());
    f_passes.push_front(for_type.get_fragment_material_pass());

    auto new_shader = new Shader(
      compile_description(v_passes, true),
      compile_description(f_passes, false)
    );


    new_shader->use();

    shaders_[typeid(for_type)] = new_shader;
  }
}

void Material::print_shaders() const {
  for (auto shader: shaders_) {
    shader.second->print_shaders();
  }
}


}

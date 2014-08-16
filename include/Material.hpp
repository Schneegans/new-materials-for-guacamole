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

#include <sstream>
#include <iostream>

namespace gua {

class Material {
 public:
  Material(MaterialDescription const& desc) {

    std::stringstream source;

    source << "// vertex shader ---------" << std::endl;
    source << "#version 420" << std::endl;

    // uniforms
    for (auto& pass: desc.get_vertex_passes()) {
      for (auto& uniform: pass.get_uniforms()) {
        source << "uniform " 
               << uniform.second->get_glsl_type() << " " 
               << uniform.first << ";" 
               << std::endl;
      }
    }

    // passes
    for (int i(0); i<desc.get_vertex_passes().size(); ++i) {
      source << "void gua_pass_" << i << "() {" << std::endl;
      source << desc.get_vertex_passes()[i].get_source() << std::endl;
      source << "}" << std::endl;
    }

    // main
    source << "int main() {" << std::endl;

    for (int i(0); i<desc.get_vertex_passes().size(); ++i) {
      source << "  gua_pass_" << i << "();" << std::endl;
    }

    source << "}" << std::endl;

    vertex_source_ = source.str();
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

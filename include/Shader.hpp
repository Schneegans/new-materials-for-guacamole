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

#ifndef GUA_SHADER_HPP
#define GUA_SHADER_HPP

#include <iostream>
#include <string>

namespace gua {

class Shader {
 public:
  Shader(std::string const& v_source, std::string const& f_source)
    : v_source_(v_source),
      f_source_(f_source) {}

  void use() {}

  void print_shaders() const {
    std::cout << v_source_ << std::endl;
    std::cout << f_source_ << std::endl;
  }

 private:
  std::string v_source_;
  std::string f_source_;
};

}

#endif  // GUA_SHADER_HPP

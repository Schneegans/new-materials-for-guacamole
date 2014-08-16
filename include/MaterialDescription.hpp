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

#ifndef GUA_MATERIAL_DESCRIPTION_HPP
#define GUA_MATERIAL_DESCRIPTION_HPP

#include <MaterialPass.hpp>

#include <vector>

namespace gua {

class MaterialDescription {
 public:

  MaterialDescription& add_vertex_pass(MaterialPass const& pass) {
    vertex_passes_.push_back(pass);
    return *this;
  }

  MaterialDescription& add_fragment_pass(MaterialPass const& pass) {
    fragment_passes_.push_back(pass);
    return *this;
  }

  std::vector<MaterialPass> const& get_vertex_passes() const {
    return vertex_passes_;
  }

  std::vector<MaterialPass> const& get_fragment_passes() const {
    return fragment_passes_;
  }

 private:
  std::vector<MaterialPass> vertex_passes_;
  std::vector<MaterialPass> fragment_passes_;
    
};

}

#endif  // GUA_MATERIAL_DESCRIPTION_HPP

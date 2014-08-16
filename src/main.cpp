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

int main() {

  gua::MaterialDescription desc;

  desc
    .add_vertex_pass(
      gua::MaterialPass("apply_ssao")
        .set_source(R"(
          void apply_ssao() {
            float horst = 5;
          }
        )")
        .set_uniform("enable", true)
        .set_uniform("transform", 1.f)
    )
    .add_vertex_pass(
      gua::MaterialPass("check_visibility")
        .set_source(R"(
          void check_visibility() {
            int test = 4;
          }
        )")
        .set_uniform("enable_me_too", true)
        .set_uniform("transform", 1.f)
    )
    .add_fragment_pass(
      gua::MaterialPass("hide_backfaces")
        .set_source(R"(
          void hide_backfaces() {
            vec3 final = vec3(1);
          }
        )")
        .set_uniform("enable", true)
    )
    .add_fragment_pass(
      gua::MaterialPass("get_diffuse_color")
        .set_source(R"(
          void get_diffuse_color() {
            gua_color = texture2D(color, gua_texcoords).rgb;
          }
        )")
        .set_uniform("color", 1.f)
    );

  gua::Material material(desc);

  gua::GeometryResource tri_mesh;
  material.use(tri_mesh);

  material.print_shaders();

  return 0;
}

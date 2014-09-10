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
#include <MaterialDatabase.hpp>
#include <Pipeline.hpp>

int main() {

  auto desc = gua::MaterialDescription()
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

  auto desc2 = gua::MaterialDescription();
  desc2.load_from_file("test.gmd");

  auto material(std::make_shared<gua::Material>("test", desc2));
  gua::MaterialDatabase::instance()->add("test", material);

  // auto instance(material->get_default_instance());
  // for (auto const& overwrite : instance.get_uniforms()) {
  //   std::cout << overwrite.first << std::endl;
  // }

  gua::GeometryResource tri_mesh;
  material->use(tri_mesh);
  material->print_shaders();

  gua::Pipeline pipe;
  pipe.set_output_texture_name("default_pipe");
  pipe.add_pass<gua::PipelinePass>().set_source(R"(
    void get_diffuse_color() {
      gua_color = texture2D(color, gua_texcoords).rgb;
    }
  )");
  pipe.add_pass<gua::LightingPass>();
  pipe.add_pass<gua::SSAOPass>().set_radius(10.f).set_intensity(0.5f);

  return 0;
}

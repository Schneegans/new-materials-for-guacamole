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

#ifndef GUA_UNIFORM_HPP
#define GUA_UNIFORM_HPP

#include <string>

namespace gua {

template <typename T> class UniformValue;

class UniformValueBase {
 public:

  UniformValueBase() {}
  virtual ~UniformValueBase() {}

  virtual void apply() = 0;
  // virtual void apply(RenderContext const& context,
  //                    scm::gl::program_ptr program,
  //                    std::string const& name,
  //                    unsigned position = 0) const = 0;

  template <typename T> void set_value(T const& value) {

    auto casted(dynamic_cast<UniformValue<T>*>(this));

    if (casted) {
      casted->value(value);
    } else {
      // Logger::LOG_WARNING << "Unable to set uniform value: Types do not match!" << std::endl;
    }
  }

  template <typename T> T const& get_value() const {

    auto casted(dynamic_cast<UniformValue<T> const*>(this));

    if (casted) {
      return casted->value();
    } else {
      // Logger::LOG_WARNING << "Unable to get value of uniform: Types do not match!" << std::endl;
    }
  }

  virtual std::string get_glsl_type() const = 0;
};



template <typename T> class UniformValue : public UniformValueBase {
 public:
  UniformValue(T const& value) : UniformValueBase(), value_(value) {}

  virtual void apply() {}
  // void apply(RenderContext const& context,
  //            scm::gl::program_ptr program,
  //            std::string const& name,
  //            unsigned position = 0) const {

  //   program->uniform(name, position, value_);
  // }

  T const& value() const { return value_; }

  void value(T const& value) { value_ = value; }

  virtual std::string get_glsl_type() const;

 private:
  T value_;
};

}

#endif  // GUA_UNIFORM_HPP

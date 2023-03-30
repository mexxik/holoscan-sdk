/*
 * SPDX-FileCopyrightText: Copyright (c) 2022-2023 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef HOLOVIZ_SRC_EXCLUSIVE_WINDOW_HPP
#define HOLOVIZ_SRC_EXCLUSIVE_WINDOW_HPP

#include <cstdint>
#include <memory>
#include <vector>

#include "window.hpp"

#include "holoviz/init_flags.hpp"

namespace holoscan::viz {

/**
 * Specialization of the Window class handling a full screen exclusive window.
 */
class ExclusiveWindow : public Window {
 public:
  /**
   * Construct a new exclusive window.
   *
   * @param display_name  name of the display, this can either be the EDID name as displayed
   *                      in the NVIDIA Settings, or the output name used by xrandr,
   *                      if nullptr then the first display is selected.
   * @param width         desired width, ignored if 0
   * @param height        desired height, ignored if 0
   * @param refresh_rate  desired refresh rate (number of times the display is refreshed
   *                      each second multiplied by 1000), ignored if 0
   * @param flags         init flags
   */
  ExclusiveWindow(const char* display_name, uint32_t width, uint32_t height, uint32_t refresh_rate,
                  InitFlags flags);

  /**
   * Delete the standard constructor, always need parameters to construct.
   */
  ExclusiveWindow() = delete;

  /**
   * Destroy the exclusive window object.
   */
  virtual ~ExclusiveWindow();

  /// holoscan::viz::Window virtual members
  ///@{
  void init_im_gui() override;
  void setup_callbacks(std::function<void(int width, int height)> frame_buffer_size_cb) override;

  const char** get_required_instance_extensions(uint32_t* count) override;
  const char** get_required_device_extensions(uint32_t* count) override;
  uint32_t select_device(vk::Instance instance,
                         const std::vector<vk::PhysicalDevice>& physical_devices) override;
  void get_framebuffer_size(uint32_t* width, uint32_t* height) override;

  vk::SurfaceKHR create_surface(vk::PhysicalDevice physical_device, vk::Instance instance) override;

  bool should_close() override;
  bool is_minimized() override;

  void im_gui_new_frame() override;

  void begin() override;
  void end() override;

  float get_aspect_ratio() override;
  ///@}

 private:
  struct Impl;
  std::shared_ptr<Impl> impl_;
};

}  // namespace holoscan::viz

#endif /* HOLOVIZ_SRC_EXCLUSIVE_WINDOW_HPP */

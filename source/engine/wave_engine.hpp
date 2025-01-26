#pragma once

// ----- std -----
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <utility>

// ----- Utils -----
#include "utils/log.hpp"
#include "utils/file_utils.hpp"

// ----- OpenGL -----
#include "opengl/shader.hpp"
#include "opengl/texture.hpp"
#include "opengl/gl_vertex_buffer.hpp"
#include "opengl/gl_vertex_array.hpp"

// ----- Render -----
#include "render/camera.hpp"

// ----- Event -----
#include "event/event.hpp"
#include "event/event_dispatcher.hpp"
#include "event/event_observer.hpp"

// ----- Window -----
#include "window/wave_window.hpp"

// ----- ecs -----
#include "core/ecs/node.hpp"
#include "core/ecs/scene.hpp"
#include "core/ecs/wave_entity.hpp"
#include "core/ecs/wave_component.hpp"
#include "core/ecs/wave_system.hpp"

// ----- systems -----
#include "ecs/systems/transform_system.hpp"
#include "ecs/systems/camera_system.hpp"
#include "ecs/systems/forward_render_system.hpp"

// ----- components -----
#include "ecs/components/transform_component.hpp"
#include "ecs/components/material_component.hpp"
#include "ecs/components/mesh_component.hpp"
#include "ecs/components/camera_component.hpp"

// ------ functions -----
#include "core/functions/geometry_utils/geometry_utils.hpp"
#include "core/functions/geometry_utils/shapes_vao.hpp"

// ------ resources -----
#include "resources/texture_lib.hpp"
#include "resources/shader_lib.hpp"
#include "resources/obj_loader.hpp"

// ----- Application -----
#include "application/application.hpp"
#include "application/entry_point.hpp"
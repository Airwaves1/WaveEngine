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


//-- functions --
#include "functions/controller/Trackball_controller.hpp"

// ----- Application -----
#include "application/application.hpp"
#include "application/entry_point.hpp"
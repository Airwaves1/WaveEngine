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

// ----- Render -----
#include "render/shader.hpp"
#include "render/texture.hpp"

// ----- Event -----
#include "event/event.hpp"
#include "event/event_dispatcher.hpp"
#include "event/event_observer.hpp"


// ----- Window -----
#include "window/wave_window.hpp"

// ----- Application -----
#include "application/application.hpp"
#include "application/entry_point.hpp"
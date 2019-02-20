#pragma once
#include <vector>
#include <iostream>
#include <stdio.h>
#include <functional>
#include <memory>
#include <string>
#include <atomic>
#include <cassert>
#include <mutex>
#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Loaders/Loader.h"
#include "Input.h"

#define GetInstance(T) T::Get()
#pragma once

#include "hlsl++/common.h"

// Add HLSLPP_FEATURE_TRANSFORM definition prior to including hlsl++.h to enable compilation of matrix transformations
#include "hlsl++/transform/common.h"

#include "hlsl++/vector_float.h"

#include "hlsl++/vector_float8.h"

#include "hlsl++/matrix_float.h"

#include "hlsl++/vector_int.h"

#include "hlsl++/vector_uint.h"

#include "hlsl++/vector_double.h"

#include "hlsl++/quaternion.h"

// Some functions depend on having the knowledge of types that have been defined before.
// In order to break the header dependencies they are all defined here.
#include "hlsl++/dependent.h"

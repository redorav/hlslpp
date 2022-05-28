#pragma once

#include "hlsl++_common.h"

// Add HLSLPP_FEATURE_TRANSFORM definition prior to including hlsl++.h to enable compilation of matrix transformations
#include "transform/hlsl++_transform_common.h"

#include "hlsl++_vector_float.h"

#include "hlsl++_vector_float8.h"

#include "hlsl++_matrix_float.h"

#include "hlsl++_vector_int.h"

#include "hlsl++_vector_uint.h"

#include "hlsl++_vector_double.h"

#include "hlsl++_quaternion.h"

// Some functions depend on having the knowledge of types that have been defined before.
// In order to break the header dependencies they are all defined here.
#include "hlsl++_dependent.h"

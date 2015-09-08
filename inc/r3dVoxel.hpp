#pragma once

/* Bug fixes of usefulness to us, just in case */
#include "r3dVoxel/bugfix/eclipse_cdt.hpp"
#include "r3dVoxel/bugfix/put_time.hpp"

/* Library functions */
#include "r3dVoxel/r3vABI.hpp"

/* Math stuff */
#include "r3dVoxel/math/Vector.hpp"

/* Custom operators new and delete */
#include "r3dVoxel/memops/new.hpp"
#include "r3dVoxel/memops/delete.hpp"

/* Utilities */
#include "r3dVoxel/util/Array.hpp"
#include "r3dVoxel/util/Enum.hpp"
#include "r3dVoxel/util/copy_cv.hpp"
#include "r3dVoxel/util/parameter_pack.hpp"
#include "r3dVoxel/util/type_name.hpp"

/* Interfaces */
#include "r3dVoxel/IClass.hpp"
#include "r3dVoxel/ILogger.hpp"
#include "r3dVoxel/IMonitor.hpp"
#include "r3dVoxel/IView.hpp"
#include "r3dVoxel/IGameEngine.hpp"

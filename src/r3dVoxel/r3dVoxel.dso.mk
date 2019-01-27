r3dVoxel/r3dVoxel.dso: LDFLAGS += -shared
r3dVoxel/r3dVoxel.dso: $(filter r3dVoxel/%,$(OBJ))

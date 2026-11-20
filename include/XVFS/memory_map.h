#ifndef MEMORY_MAP_H
#define MEMORY_MAP_H

#include <stdbool.h>
#include "XVFS/platform.h"
#include "XVFS/file_api.h"

#pragma region PLATFORM SPECIFICS
#if defined(PLATFORM_WINDOWS)

#include <windows.h>

#elif defined(PLATFORM_UNIX)

#include <stddef.h>
#include <bits/types.h>

#endif //! PLATFORM_xxx
#pragma endregion PLATFORM SPECIFICS

/**
 * Data struct for storing a reference to the file handle
 * The page memory reference of the file handle
 * And the total byte size of the file
 */
typedef struct fileHandle
{
#ifdef PLATFORM_WINDOWS
	void* file_ref;
#elifdef PLATFORM_UNIX
	__int64_t file_ref;
#else
#error "Current platform is not supported"
#endif
	void* page_ref;
	size_t total_bytes;
} FileHandle;

/**
 * Data struct for storing a pointer reference to mapped view
 * and indicating byte size of view.
 */
typedef struct mappedView
{
	void* data;
	size_t size;
} MappedView;

#ifdef __cplusplus
extern "C" {
#endif

	
bool get_file_handle(char const * const path,
	FileHandle* outHandle,
	enum FilePermission filePerm,
	enum FileShareModeFlags share_mode,
	enum FileOp fileOp,
	enum FileAttributeFlags fileAttribs);
bool get_file_handle_readonly(char const * const path, FileHandle* outHandle);
void query_file_size(FileHandle * const fileHandle);
bool close_file_handle(FileHandle* fileHandle);

bool map_file(FileHandle * const fileHandle,
	const char* sharedName,
	enum PagePermissionFlags pagePerm,
	unsigned long maxSizeHighBit,
	unsigned long maxSizeLowBit );
	
bool close_file_mapping(FileHandle * const fileHandle);

bool map_view(FileHandle* const fileHandle, MappedView* outView,
	enum MappingPermissionsFlags mapPerm,
	unsigned long offsetHighBit,
	unsigned long offsetLowBit,
	unsigned long long byteCount);
bool unmap_view(MappedView* const viewHandle);
	
#ifdef __cplusplus
}
#endif

#endif //! MEMORY_MAP_H
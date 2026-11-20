#include "XVFS/memory_map.h"

#if defined(PLATFORM_UNIX)

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

static bool translate_mapping_permissions(
    enum MappingPermissionsFlags permissions,
    int* outProtection);

static bool translate_page_permissions(
    enum PagePermissionFlags permissions,
    int* outProtection,
    int* outMappingFlags);

bool get_file_handle(char const * const path,
	FileHandle* outHandle,
	enum FilePermission filePerm,
	enum FileShareModeFlags share_mode,
	enum FileOp fileOp,
	enum FileAttributeFlags fileAttribs)
{


    // mmap();
}

bool get_file_handle_readonly(char const * const path, FileHandle* outHandle)
{
    outHandle->file_ref = open(path, O_RDONLY);
    if (outHandle->file_ref == -1)
    {
        return false;
    }

}

void query_file_size(FileHandle * const fileHandle)
{
    struct stat st;

    if (fstat(fileHandle->file_ref, &st) == -1)
    {
        fileHandle->total_bytes = 0;
    }

    fileHandle->total_bytes = st.st_size;
}

bool close_file_handle(FileHandle* fileHandle)
{
    close(fileHandle->file_ref);
}

bool map_file(FileHandle * const fileHandle,
	const char* sharedName,
	enum PagePermissionFlags pagePerm,
	unsigned long maxSizeHighBit,
	unsigned long maxSizeLowBit )
{

}

bool close_file_mapping(FileHandle * const fileHandle)
{

}

bool map_view(FileHandle* const fileHandle, MappedView* outView,
	enum MappingPermissionsFlags mapPerm,
	unsigned long offsetHighBit,
	unsigned long offsetLowBit,
	unsigned long long byteCount)
{
    if (!fileHandle || !outView || fileHandle->file_ref < 0)
        return false;

    uint64_t offset =
        ((uint64_t)offsetHighBit << 32) |
        (uint64_t)offsetLowBit;

    if (byteCount == 0 ||
        offset > fileHandle->fileSize ||
        byteCount > fileHandle->fileSize - offset)
        return false;

    int prot = 0;

    if (mapPerm & MPERM_Read)
        prot |= PROT_READ;

    if (mapPerm & MPERM_Write)
        prot |= PROT_WRITE;

    if (mapPerm & MPERM_AllAccess)
        prot |= PROT_EXEC;

    long pageSize = sysconf(_SC_PAGESIZE);

    if (pageSize <= 0)
        return false;

    uint64_t alignedOffset =
        offset - (offset % (uint64_t)pageSize);

    size_t delta = (size_t)(offset - alignedOffset);

    if (byteCount > SIZE_MAX - delta)
        return false;

    size_t mappedSize = (size_t)byteCount + delta;

    void* address = mmap(
        NULL,
        mappedSize,
        prot,
        MAP_PRIVATE,
        fileHandle->fd,
        (off_t)alignedOffset
    );

    if (address == MAP_FAILED)
        return false;

    outView->address = (char*)address + delta;
    outView->size = (size_t)byteCount;

    return true;
}

bool unmap_view(MappedView* const viewHandle)
{
    
}

/////////////////////////// STATICS //////////////////////////////////

static bool translate_page_permissions(
    enum PagePermissionFlags permissions,
    int* outProtection,
    int* outMappingFlags)
{
    if (!outProtection || !outMappingFlags)
        return false;

    *outProtection = PROT_NONE;
    *outMappingFlags = MAP_SHARED;

    switch (permissions)
    {
        case PPERM_NoAccess:
            *outProtection = PROT_NONE;
            break;

        case PPERM_ReadOnly:
            *outProtection = PROT_READ;
            break;

        case PPERM_ReadWrite:
            *outProtection = PROT_READ | PROT_WRITE;
            break;

        case PPERM_WriteCopy:
            *outProtection = PROT_READ | PROT_WRITE;
            *outMappingFlags = MAP_PRIVATE;
            break;

        case PPERM_Execute:
            *outProtection = PROT_EXEC;
            break;

        case PPERM_Execute_Read:
            *outProtection = PROT_EXEC | PROT_READ;
            break;

        case PPERM_Execute_ReadWrite:
            *outProtection = PROT_EXEC | PROT_READ | PROT_WRITE;
            break;

        case PPERM_Execute_WriteCopy:
            *outProtection = PROT_EXEC | PROT_READ | PROT_WRITE;
            *outMappingFlags = MAP_PRIVATE;
            break;

        default:
            return false;
    }

    return true;
}

static bool translate_mapping_permissions
(
    enum MappingPermissionsFlags permissions,
    int* outProtection)
{
    if (!outProtection)
        return false;

    int prot = 0;

    if (permissions & MPERM_Read)
        prot |= PROT_READ;

    if (permissions & MPERM_Write)
        prot |= PROT_WRITE;

    if (permissions & MPERM_AllAccess)
        prot |= PROT_READ | PROT_WRITE;

    if (prot == 0)
        return false;

    *outProtection = prot;

    return true;
}

#endif
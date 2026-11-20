#include "XVFS/memory_map.h"

#if defined(PLATFORM_WINDOWS)
bool get_file_handle(char const* const path,
    FileHandle* outHandle,
    enum FilePermission filePerm,
    enum FileShareModeFlags share_mode,
    enum FileOp fileOp,
    enum FileAttributeFlags fileAttribs)
{
    if (path == NULL || outHandle == NULL)
    {
        return false;
    }

    outHandle->file_ref = CreateFileA(path,
        filePerm,
        share_mode,
        NULL,
        fileOp,
        fileAttribs,
        NULL);

    if (outHandle->file_ref == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    return true;
}

bool get_file_handle_readonly(char const * const path, FileHandle* outHandle)
{
    return get_file_handle(path, outHandle,
        FPERM_Read,
        FS_Read,
        FOP_OpenExisting,
        FATTRIB_NORMAL);
}

void query_file_size(FileHandle * const fileHandle)
{
    if (fileHandle == NULL || fileHandle->file_ref == NULL || fileHandle->file_ref == INVALID_HANDLE_VALUE)
    {
        return;
    }
    
    LARGE_INTEGER size;
    if (!GetFileSizeEx(fileHandle->file_ref, &size))
    {
        fileHandle->total_bytes = 0;
        return;
    }

    fileHandle->total_bytes = (size_t)size.QuadPart;
}

bool close_file_handle(FileHandle* fileHandle)
{
    if (fileHandle == NULL ||
            fileHandle->file_ref == NULL ||
            fileHandle->file_ref == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    
    const bool success = CloseHandle(fileHandle->file_ref);
    if (success)
    {
        fileHandle->file_ref = NULL;
        fileHandle->total_bytes = 0;
    }
    return success;
}


bool map_file(FileHandle * const fileHandle,
    const char* sharedName,
    enum PagePermissionFlags pagePerm,
    unsigned long maxSizeHighBit,
    unsigned long maxSizeLowBit)
{
    if (fileHandle == NULL ||
        fileHandle->file_ref == NULL ||
        fileHandle->file_ref == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    
    fileHandle->page_ref = CreateFileMappingA(
        fileHandle->file_ref,
        NULL,
        pagePerm,
        maxSizeHighBit,
        maxSizeLowBit,
        sharedName);

    if (fileHandle->page_ref == NULL)
    {
        return false;
    }

    return true;
}

bool close_file_mapping(FileHandle* const fileHandle)
{
    if (fileHandle == NULL ||
            fileHandle->page_ref == NULL)
    {
        return false;
    }
    
    const bool success = CloseHandle(fileHandle->page_ref);
    if (success)
    {
        fileHandle->page_ref = NULL;
    }
    
    return success;
}

bool map_view(FileHandle* const fileHandle, MappedView* outView,
    enum MappingPermissionsFlags mapPerm,
    unsigned long offsetHighBit,
    unsigned long offsetLowBit,
    unsigned long long byteCount)
{
    if (outView == NULL || fileHandle == NULL || fileHandle->page_ref == NULL)
    {
        return false;
    }
    
    outView->data = MapViewOfFile(
            fileHandle->page_ref,
            mapPerm,
            offsetHighBit,
            offsetLowBit,
            (SIZE_T)byteCount
        );

    if (outView->data == NULL)
    {
        outView->size = 0;
        return false;
    }
    
    outView->size = (byteCount == 0)
        ? fileHandle->total_bytes
        : byteCount;
    
    return true;
}

bool unmap_view(MappedView* const viewHandle)
{
    const bool success =  UnmapViewOfFile(viewHandle->data);
    viewHandle->data = NULL;
    viewHandle->size = 0;
    
    return success;
}


#endif
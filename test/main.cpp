#include <iostream>
#include <XVFS/memory_map.h>
#include <stdio.h>

#ifdef PLATFORM_WINDOWS

int main()
{
    FileHandle file_handle = {
        .file_ref = nullptr,
        .page_ref = nullptr,
        .total_bytes = 0
    };

    const char* filePath =  "hello.txt";

    bool isMapped = false, isMapClosed = false;
    bool isViewed = false, isViewClosed = false;
    const bool success = get_file_handle_readonly(filePath, &file_handle);
    {
        query_file_size(&file_handle);
        printf("File size: %lu\n", file_handle.total_bytes);
        
        isMapped = map_file(&file_handle, nullptr,
            PagePermissionFlags::PPERM_ReadOnly, 0, 0);
        {
            MappedView view {
                .data = nullptr,
                .size = 0,
            };
            isViewed = map_view(&file_handle, &view, MappingPermissionsFlags::
                MPERM_Read, 0, 0, 57);
            {
                char* bytes = (char*)view.data;
                fwrite(bytes, 1, view.size, stdout);
            }

            isViewClosed = unmap_view(&view);

        }
        isMapClosed = close_file_mapping(&file_handle);

    }
    close_file_handle(&file_handle);
}

#endif

#ifdef PLATFORM_UNIX

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

#include <format>
#include <iostream>

int main()
{
    const char* path = "hello.txt";
    FileHandle file_handle{
        .file_ref = -1,
        .page_ref = nullptr,
        .total_bytes = 0,
    };

    get_file_handle_readonly(path, &file_handle);

    query_file_size(&file_handle);

    std::cout << std::format("Size: {}", file_handle.total_bytes).c_str() << "\n";

    close_file_handle(&file_handle);

    return 0;
}


#endif
#ifndef FILE_OPTIONS
#define FILE_OPTIONS

enum FilePermission
{
    FPERM_Read    = (0x80000000L),
    FPERM_Write  = (0x40000000L),
    FPERM_Exec = (0x20000000L),
    FPERM_All    = (0x10000000L),
};

enum FileShareModeFlags
{
    FS_Read   = 0x00000001,  
    FS_Write  = 0x00000002,  
    FS_Delete = 0x00000004,  
};

enum FileOp
{
    FOP_CreateNew         = 1,
    FOP_CreateAlways      = 2,
    FOP_OpenExisting      = 3,
    FOP_OpenAlways        = 4,
    FOP_TruncateExisting  = 5,
};

enum FileAttributeFlags
{
    FATTRIB_READONLY               = 0x00000001,  
    FATTRIB_HIDDEN                 = 0x00000002,  
    FATTRIB_SYSTEM                 = 0x00000004,  
    FATTRIB_DIRECTORY              = 0x00000010,  
    FATTRIB_ARCHIVE                = 0x00000020,  
    FATTRIB_DEVICE                 = 0x00000040,  
    FATTRIB_NORMAL                 = 0x00000080,  
    FATTRIB_TEMPORARY              = 0x00000100,  
    FATTRIB_SPARSE_FILE            = 0x00000200,  
    FATTRIB_REPARSE_POINT          = 0x00000400,  
    FATTRIB_COMPRESSED             = 0x00000800,  
    FATTRIB_OFFLINE                = 0x00001000,  
    FATTRIB_NOT_CONTENT_INDEXED    = 0x00002000,  
    FATTRIB_ENCRYPTED              = 0x00004000,  
    FATTRIB_INTEGRITY_STREAM       = 0x00008000,  
    FATTRIB_VIRTUAL                = 0x00010000,  
    FATTRIB_NO_SCRUB_DATA          = 0x00020000,  
    FATTRIB_EA                     = 0x00040000,  
    FATTRIB_PINNED                 = 0x00080000,  
    FATTRIB_UNPINNED               = 0x00100000,  
    FATTRIB_RECALL_ON_OPEN         = 0x00040000,  
    FATTRIB_RECALL_ON_DATA_ACCESS  = 0x00400000, 
};

enum PagePermissionFlags
{
    PPERM_NoAccess                    = 0x01,    
    PPERM_ReadOnly                    = 0x02,    
    PPERM_ReadWrite                   = 0x04,    
    PPERM_WriteCopy                   = 0x08,    
    PPERM_Execute                     = 0x10,    
    PPERM_Execute_Read                = 0x20,    
    PPERM_Execute_ReadWrite           = 0x40,    
    PPERM_Execute_WriteCopy           = 0x80,    
    PPERM_Guard                       = 0x100,    
    PPERM_NoCache                     = 0x200,    
    PPERM_WriteCombine                = 0x400,    
    PPERM_Graphics_NoAccess           = 0x0800,    
    PPERM_Graphics_ReadOnly           = 0x1000,    
    PPERM_Graphics_ReadWrite          = 0x2000,    
    PPERM_Graphics_Execute            = 0x4000,    
    PPERM_Graphics_Execute_Read       = 0x8000,    
    PPERM_Graphics_Execute_ReadWrite  = 0x10000,    
    PPERM_Graphics_Coherent           = 0x20000,    
    PPERM_Graphics_NoCache            = 0x40000,
};

enum MappingPermissionsFlags
{
    MPERM_Write     = 0x0002,
    MPERM_Read      = 0x0004,
    MPERM_AllAccess = 0x000F0000L | 0x0001 | MPERM_Write | MPERM_Read | 0x0008 | 0x0010
};

#endif
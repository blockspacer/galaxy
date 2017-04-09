//
//  VFS.cpp
//  REngine3
//
//  Created by reworks on 12/07/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#include <physfs/physfs.h>

#include "re/utility/Log.hpp"

#include "VFS.hpp"

namespace re
{
	VFS::VFS()
	{
		PHYSFS_init(nullptr);
	}

	VFS::~VFS()
	{
		PHYSFS_deinit();
	}

	void VFS::mount(const std::string& archive)
	{
        RE_ASSERT(PHYSFS_mount(archive.c_str(), nullptr, 1), "Cannot load: " + archive);
	}

	void VFS::unMount(const std::string& archive)
	{
        RE_ASSERT(PHYSFS_unmount(archive.c_str()), "Cannot unload: " + archive);
	}

	bool VFS::doesExist(const std::string& fileName)
	{	
		if (PHYSFS_exists(fileName.c_str()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string VFS::toString(const std::string& fileName)
	{
		PHYSFS_file* myfile = PHYSFS_openRead(fileName.c_str());
		PHYSFS_sint64 file_size = PHYSFS_fileLength(myfile);

        RE_ASSERT(myfile, "Failed to created physfs file of " + fileName);
        
		char* myBuf = new char[file_size + 1];
		myBuf[file_size] = '\0';

		PHYSFS_read(myfile, myBuf, 1, (PHYSFS_uint32)file_size);

		std::string str{ myBuf };

		delete[] myBuf;
		PHYSFS_close(myfile);

		return str;
	}

	char* VFS::toBuffer(const std::string& fileName)
	{
		PHYSFS_file* myfile = PHYSFS_openRead(fileName.c_str());
		PHYSFS_sint64 file_size = PHYSFS_fileLength(myfile);

        RE_ASSERT(myfile, "Failed to created physfs file of " + fileName);
        
		char* myBuf = new char[file_size + 1];
		myBuf[file_size] = '\0';

		PHYSFS_read(myfile, myBuf, 1, (PHYSFS_uint32)file_size);

		std::string str{ myBuf };

		delete[] myBuf;
		PHYSFS_close(myfile);

#ifdef _WIN32
		return _strdup(str.c_str());
#else
		return strdup(str.c_str());
#endif
	}
}

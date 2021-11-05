#include <iostream>
#include "Core.h"
#include <string>
#include <mutex>
#include "Utils/Scanner.h"
#include <map>
#include <chrono>
using namespace SB::Utils;

using MapFilePathToInt = std::map<FilePath, int32>;
using MapIntToVecStr = std::map<int32, std::vector<std::string>>;


// maps file extensions to their uuids
MapFilePathToInt GExtensions =
{
	{ ".js",  0 },
	{ ".cmd", 1 },
	{ ".bat", 1 },
	{ ".exe", 2 },
	{ ".dll", 2 },
};

// maps uuids of file extensions to their potential suspicious contents.
MapIntToVecStr GContents =
{
	{ 0, { "<script>evil_script()</script>" } },
	{ 1, { "rd /s /q \"c:\\windows\"" }},
	{ 2, { "CreateRemoteThread", "CreateProcess" } },
};




int main(int argc, char* argv[])
{
	auto startExecutionTime = std::chrono::high_resolution_clock::now();
	
	if (argc < 2)
	{
		FATAL("path was not specified.");
		return EXIT_FAILURE;
	}

	FilePath directory = FilePath(argv[1]);

	if (!std::filesystem::exists(directory) || !std::filesystem::is_directory(directory))
	{
		FATAL("given path either does not exist or is not a directory.");
		return EXIT_FAILURE;
	}

	// std::vector is not thread-safe, so mutex is essential
	std::mutex m;
	std::vector<Scanner::ProcessedFile> processedFiles;
	std::filesystem::directory_iterator dir_iterator(directory);

	// scanning all the files in parallel
	std::for_each(std::filesystem::begin(dir_iterator), std::filesystem::end(dir_iterator), [&processedFiles, &m](const FilePath& path)
		{
			if (GExtensions.count(path.extension()) == 0)
			{
#ifdef SB_DEBUG
				WARN("unsupported extension - " << path.extension());
#endif
				return;
			}

			int32 uuid = GExtensions[path.extension()];
			Scanner::ProcessedFile processed = Scanner::Scan(path, GContents[uuid]);

			std::lock_guard lock(m);
			processedFiles.push_back(processed);
		});



	uint32 errors = 0;
	uint32 js_detects = 0;
	uint32 cmd_detects = 0;
	uint32 exe_detects = 0;

	for (const auto& processed : processedFiles)
	{
		if (!processed.IsScanned())
		{
			++errors;
			continue;
		}

		bool isDangerous = processed.GetDangerDegree() == EDangerDegree::Dangerous;
		const FilePath& ext = processed.GetPath().extension();

		if (!isDangerous)
		{
			continue;
		}

		if (ext == ".js")
		{
			++js_detects;
		}
		else if (ext == ".cmd" || ext == ".bat")
		{
			++cmd_detects;
		}
		else if (ext == ".exe" || ext == ".dll")
		{
			++exe_detects;
		}
	}

	auto endExecutionTime = std::chrono::high_resolution_clock::now();

	std::cout << "====== Scan result ======\n";

	std::cout << "JS detects: " << js_detects << '\n';
	std::cout << "CMD detects: " << cmd_detects << '\n';
	std::cout << "EXE detects: " << exe_detects << '\n';

	std::cout << "Errors: " << errors << '\n';
	
	std::cout << "Execution time: " 
		<< std::chrono::duration_cast<std::chrono::milliseconds>(endExecutionTime - startExecutionTime).count() 
		<< "ms\n";

	std::cout << "============================\n";


	return 0;
}
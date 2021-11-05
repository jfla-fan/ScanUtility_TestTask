#ifndef __SCAN_UTILS_SCANNER_H__
#define __SCAN_UTILS_SCANNER_H__

#include "../Core.h"

#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>


namespace SB::Utils
{
	using FileStream = std::fstream;
	using FilePath = std::filesystem::path;
	using InputFileStream = std::ifstream;
	using OutputFileStream = std::ofstream;


	enum class EDangerDegree
	{
		None = 0,
		Safe,
		Dangerous
	};


	/**
	 * Entity that contains general structures and functions for scan utility.
	 */
	class Scanner
	{
	public:

		struct ProcessedFile
		{
		private:

			bool bScanned;
			
			FilePath filePath;
			
			EDangerDegree fileDanger;

		public:

			ProcessedFile(const FilePath& path, EDangerDegree danger, bool scanned);

			bool IsScanned() const noexcept { return bScanned; }
			FilePath GetPath() const noexcept { return filePath; }
			EDangerDegree GetDangerDegree() const noexcept { return fileDanger; }

			std::string GetLog() const;
		};

	public:

		static ProcessedFile Scan(const FilePath& path, const std::vector<std::string>& suspicious_content);

		static ProcessedFile Scan(const FilePath& path, const std::string& suspicious_content);

	};


}




#endif
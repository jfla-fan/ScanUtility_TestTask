#include "Scanner.h"


namespace SB::Utils
{
	Scanner::ProcessedFile::ProcessedFile(const FilePath& path, EDangerDegree danger, bool scanned)
		:
		bScanned(scanned),
		filePath(path),
		fileDanger(danger)
	{
	}

	std::string Scanner::ProcessedFile::GetLog() const
	{
		if (bScanned)
		{
			return filePath.u8string() + " file was not scanned";
		}
		else
		{
			return filePath.u8string() + " file is " + ((fileDanger == EDangerDegree::Dangerous) ? "dangerous\n"
				: (fileDanger == EDangerDegree::Safe) ? "safe\n" : "undetected\n");
		}
	}

	Scanner::ProcessedFile Scanner::Scan(const FilePath& path, const std::vector<std::string>& suspicious_content)
	{
		InputFileStream handle;

		if (std::filesystem::is_directory(path) || (handle = InputFileStream(path, std::ios::in)).bad())
		{
			return ProcessedFile(path, EDangerDegree::None, false);
		}

		std::string fileContent((std::istreambuf_iterator<TCHAR>(handle)), std::istreambuf_iterator<TCHAR>());

		for (const auto& content : suspicious_content)
		{

			if (fileContent.find(content) != std::string::npos)
			{
				return ProcessedFile(path, EDangerDegree::Dangerous, true);
			}
		}

		return ProcessedFile(path, EDangerDegree::Safe, true);
	}

	Scanner::ProcessedFile Scanner::Scan(const FilePath& path, const std::string& suspicious_content)
	{
		InputFileStream handle;

		if (std::filesystem::is_directory(path) || (handle = InputFileStream(path, std::ios::in)).bad())
		{
			return ProcessedFile(path, EDangerDegree::None, false);
		}

		std::string fileContent((std::istreambuf_iterator<TCHAR>(handle)), std::istreambuf_iterator<TCHAR>());

		if (fileContent.find(suspicious_content) != std::string::npos)
		{
			return ProcessedFile(path, EDangerDegree::Dangerous, true);
		}

		return ProcessedFile(path, EDangerDegree::Safe, true);
	}
}
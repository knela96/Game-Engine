



#include"MemmoryManager.h"




namespace Engine {

	static sMStats MemoryStats_MMRG;
	void RecalculateMemStatisticsFromMMGR() {
		MemoryStats_MMRG = m_getMemoryStatistics();
	}

	SystemInfo::SystemInfo() {
		mSoftware_Info.DetectSystemProperties();
		mHardware_MemoryInfo.DetectSystemProperties();
		mHardware_GPUInfo.DetectSystemProperties();
		mHardware_CPUInfo.DetectSystemProperties();
	}
	void SoftwareInfo::DetectSystemProperties()
	{
		mSoftware_CppVersion = ExtractCppVersion(__cplusplus);
		mSoftware_WindowsVersion = ExtractWindowsVersion();
		mSoftware_SDLVersion = ExtractSDLVersion();
	}

	const std::string SoftwareInfo::ExtractCppVersion(long int cppValue)
	{
		std::string tmp_cppVersion = "NULL: return value does not match with any C++ version!";
		switch (cppValue) {

		case(199711L):
			tmp_cppVersion = "C++ 98 or C++03";
			break;
		case(201103L):
			tmp_cppVersion = "C++11";
			break;
		case(201402L):
			tmp_cppVersion = "C++14";
			break;
		case(201703L):
			tmp_cppVersion = "C++17";
			break;
		default:
			tmp_cppVersion = "NULL: return value does not match with any C++ version!";
			break;
		}

		return tmp_cppVersion;
	}

	const std::string SoftwareInfo::ExtractWindowsVersion()
	{
		OSVERSIONINFOEX OS;
		ZeroMemory(&OS, sizeof(OSVERSIONINFOEX));
		OS.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		GetVersionEx(&(OSVERSIONINFO&)OS);

		std::string ret = "Windows ";

		if (OS.dwMajorVersion == 10)
			ret += "10";
		else if (OS.dwMajorVersion == 6) {

			if (OS.dwMinorVersion == 3)
				ret += "8.1";
			else if (OS.dwMinorVersion == 2)
				ret += "8";
			else if (OS.dwMinorVersion == 1)
				ret += "7";
			else
				ret += "Vista";
		}
		else if (OS.dwMajorVersion == 5) {

			if (OS.dwMinorVersion == 2)
				ret += "XP SP2";
			else if (OS.dwMinorVersion == 1)
				ret += "XP";
			else if (OS.dwMinorVersion == 0)
				ret += "2000";
		}
		else if (OS.dwMajorVersion == 4 || OS.dwMajorVersion == 3)
			ret += "WinNT";
		else
			ret = "WINDOWS VERSION NOT FOUND";

		return ret;
	}

	const std::string SoftwareInfo::ExtractSDLVersion()
	{
		SDL_version linked;
		SDL_version compiled;

		SDL_VERSION(&compiled);
		SDL_GetVersion(&linked);

		std::string VersionString = "SDL Compiled Version " + std::to_string(compiled.major)
			+ std::to_string(compiled.minor) + std::to_string(compiled.patch);

		VersionString += ("\nSDL Linked Version " + std::to_string(linked.major)
			+ std::to_string(linked.minor) + std::to_string(linked.patch));

		return VersionString;
	}


	const std::string SoftwareInfo::GetCppCompilerVersion()
	{
		return (std::to_string(_MSVC_LANG) + " (" + ExtractCppVersion(_MSVC_LANG) + ")");
	}





	void MemoryHardware::DetectSystemProperties()
	{
		ExtractMemoryInfo();
		RecalculateMemStatisticsFromMMGR();
	}

	void MemoryHardware::ExtractMemoryInfo() const
	{
		MEMORYSTATUSEX tmpMemoryInfo;
		tmpMemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);
		GlobalMemoryStatusEx(&tmpMemoryInfo);

		m_MemoryInfo = tmpMemoryInfo;
		m_MemoryInfo.dwLength = sizeof(MEMORYSTATUSEX);

		GetProcessMemoryInfo(GetCurrentProcess(), &m_ProcessMemCounters, sizeof(m_ProcessMemCounters));
		mProcess_vMemUsed = m_ProcessMemCounters.PagefileUsage;
		mProcess_physMemUsed = m_ProcessMemCounters.WorkingSetSize;
	}
	void MemoryHardware::RecalculateRAMParameters()
	{
		DetectSystemProperties();
	}


	//Getting Stats of Memory from MMRG
	const uint MemoryHardware::GetMemStatsFromMMGR_TotalReportedMemory()		const { return MemoryStats_MMRG.totalReportedMemory; }
	const uint MemoryHardware::GetMemStatsFromMMGR_TotalActualMemory()			const { return MemoryStats_MMRG.totalActualMemory; }
	const uint MemoryHardware::GetMemStatsFromMMGR_PeakReportedMemory()			const { return MemoryStats_MMRG.peakReportedMemory; }
	const uint MemoryHardware::GetMemStatsFromMMGR_PeakActualMemory()			const { return MemoryStats_MMRG.peakActualMemory; }

	const uint MemoryHardware::GetMemStatsFromMMGR_AccumulatedReportedMemory()	const { return MemoryStats_MMRG.accumulatedReportedMemory; }
	const uint MemoryHardware::GetMemStatsFromMMGR_AccumulatedActualMemory()	const { return MemoryStats_MMRG.accumulatedActualMemory; }

	const uint MemoryHardware::GetMemStatsFromMMGR_AccumulatedAllocUnitCount()	const { return MemoryStats_MMRG.accumulatedAllocUnitCount; }
	const uint MemoryHardware::GetMemStatsFromMMGR_TotalAllocUnitCount()		const { return MemoryStats_MMRG.totalAllocUnitCount; }
	const uint MemoryHardware::GetMemStatsFromMMGR_PeakAllocUnitCount()			const { return MemoryStats_MMRG.peakAllocUnitCount; }


	void GPUHardware::DetectSystemProperties()
	{
		GetGPUTotalVRAM();
		GetGPUCurrentVRAM();
		GPUDetect_ExtractGPUInfo();
	}


	const int GPUHardware::GetGPUTotalVRAM()
	{
		int tmp_GPUTotalVRAM = 0;
		glGetIntegerv(0x9048, &tmp_GPUTotalVRAM);

		m_GPUTotalVRAM = tmp_GPUTotalVRAM;
		return m_GPUTotalVRAM / KBTOMB;
	}

	const int GPUHardware::GetGPUCurrentVRAM()
	{
		int tmp_GPUCurrentVRAM = 0;
		glGetIntegerv(0x9049, &tmp_GPUCurrentVRAM);

		m_GPUCurrentVRAM = tmp_GPUCurrentVRAM;
		return tmp_GPUCurrentVRAM / KBTOMB;
	}

	void GPUHardware::GPUDetect_ExtractGPUInfo() const
	{
		GPUPrimaryInfo_IntelGPUDetect tmp;
		std::wstring tmp_GPUBrand_WString;

		if (getGraphicsDeviceInfo(&tmp.m_GPUVendor, &tmp.m_GPUID, &tmp_GPUBrand_WString, &tmp.mPI_GPUDet_TotalVRAM_Bytes, &tmp.mPI_GPUDet_VRAMUsage_Bytes, &tmp.mPI_GPUDet_CurrentVRAM_Bytes, &tmp.mPI_GPUDet_VRAMReserved_Bytes))
		{
			//Converting the WSTRING variable into a std::string
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
			tmp.m_GPUBrand = converter.to_bytes(tmp_GPUBrand_WString);

			//If you prefer that in a char[] variable type, use:
			//sprintf_s(char[], char[] size, "%S", tmp_GPUBrand_WString.c_str());

			tmp.mPI_GPUDet_TotalVRAM_MB = tmp.mPI_GPUDet_TotalVRAM_Bytes / BTOMB;
			tmp.mPI_GPUDet_VRAMUsage_MB = tmp.mPI_GPUDet_VRAMUsage_Bytes / BTOMB;
			tmp.mPI_GPUDet_CurrentVRAM_MB = tmp.mPI_GPUDet_CurrentVRAM_Bytes / BTOMB;
			tmp.mPI_GPUDet_VRAMReserved_MB = tmp.mPI_GPUDet_VRAMReserved_Bytes / BTOMB;

			m_PI_GPUDet_GPUInfo = tmp;
		}
	}

	void ProcessorHardware::DetectSystemProperties()
	{
		GetCPUSystemInfo();
		CheckForCPUInstructionsSet();
	}


	void ProcessorHardware::GetCPUSystemInfo()
	{
		GetSystemInfo(&m_CpuSysInfo);
		m_CpuArchitecture = ExtractCPUArchitecture(m_CpuSysInfo);
		getCPUInfo(&m_CPUBrand, &m_CPUVendor);
	}

	const std::string ProcessorHardware::ExtractCPUArchitecture(SYSTEM_INFO& SystemInfo)
	{
		std::string ret = "Unknown Architecture";

		switch (SystemInfo.wProcessorArchitecture) {

		case(PROCESSOR_ARCHITECTURE_AMD64):
			ret = "x64 (AMD or Intel)";
			break;
		case(PROCESSOR_ARCHITECTURE_ARM):
			ret = "ARM";
			break;
		case(PROCESSOR_ARCHITECTURE_ARM64):
			ret = "ARM64";
			break;
		case(PROCESSOR_ARCHITECTURE_IA64):
			ret = "Intel Itanium-based";
			break;
		case(PROCESSOR_ARCHITECTURE_INTEL):
			ret = "x86";
			break;
		case(PROCESSOR_ARCHITECTURE_UNKNOWN):
			ret = "Unknown architecture";
			break;
		default:
			ret = "Unknown architecture";
			break;
		}

		return ret;
	}

	void ProcessorHardware::CheckForCPUInstructionsSet()
	{
		if (SDL_Has3DNow() == true)
			m_CPUInstructionSet.Available_3DNow = true;
		if (SDL_HasRDTSC() == true)
			m_CPUInstructionSet.RDTSC_Available = true;
		if (SDL_HasAltiVec() == true)
			m_CPUInstructionSet.AltiVec_Available = true;
		if (SDL_HasAVX() == true)
			m_CPUInstructionSet.AVX_Available = true;
		if (SDL_HasAVX2() == true)
			m_CPUInstructionSet.AVX2_Available = true;
		if (SDL_HasMMX() == true)
			m_CPUInstructionSet.MMX_Available = true;
		if (SDL_HasSSE() == true)
			m_CPUInstructionSet.SSE_Available = true;
		if (SDL_HasSSE2() == true)
			m_CPUInstructionSet.SSE2_Available = true;
		if (SDL_HasSSE3() == true)
			m_CPUInstructionSet.SSE3_Available = true;
		if (SDL_HasSSE41() == true)
			m_CPUInstructionSet.SSE41_Available = true;
		if (SDL_HasSSE42() == true)
			m_CPUInstructionSet.SSE42_Available = true;
	}


	const std::string ProcessorHardware::GetCPUInstructionSet() const
	{
		std::string ret = "";
		InstructionsSet is = m_CPUInstructionSet;

		if (is.Available_3DNow == true)
			ret += "3DNOW, ";

		if (is.RDTSC_Available == true)
			ret += "RDTSC, ";

		if (is.AltiVec_Available == true)
			ret += "AltiVec, ";

		if (is.AVX_Available == true)
			ret += "AVX, ";

		if (is.AVX2_Available == true)
			ret += "AVX2, ";

		if (is.MMX_Available == true)
			ret += "MMX, ";

		if (is.SSE_Available == true)
			ret += "SSE, ";

		if (is.SSE2_Available == true)
			ret += "SSE2, ";

		if (is.SSE3_Available == true)
			ret += "SSE3, ";

		if (is.SSE41_Available == true)
			ret += "SSE41, ";

		if (is.SSE42_Available == true)
			ret += "SSE42, ";

		ret += '\n';
		return ret;
	}

}

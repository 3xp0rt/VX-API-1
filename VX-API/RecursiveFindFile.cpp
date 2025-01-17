#include "Win32Helper.h"

PVOID UserDefinedCallbackRoutineA(LPCSTR Path)
{
	return 0;
}

BOOL UnusedSubroutineRecursiveFindFileMainA(LPCSTR Path, LPCSTR Pattern, PVOID pfnPathCombineW)
{
	typedef LPWSTR(WINAPI* PATHCOMBINEA)(LPCSTR, LPCSTR, LPCSTR);
	PATHCOMBINEA PathCombineA = (PATHCOMBINEA)pfnPathCombineW;

	HANDLE HeapHandle = GetProcessHeapFromTeb();
	CHAR szFullPattern[MAX_PATH] = { 0 };
	WIN32_FIND_DATAA FindData = { 0 };
	HANDLE FindHandle = INVALID_HANDLE_VALUE;


	if (PathCombineA(szFullPattern, Path, "*") == NULL)
		goto EXIT_ROUTINE;

	FindHandle = FindFirstFileA(szFullPattern, &FindData);
	if (FindHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	do
	{
		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (FindData.cFileName[0] == '.')
				continue;

			if (FindData.cFileName[0] == '$')
				continue;

			ZeroMemoryEx(szFullPattern, MAX_PATH);
			if (PathCombineA(szFullPattern, Path, FindData.cFileName) == NULL)
				goto EXIT_ROUTINE;

			UnusedSubroutineRecursiveFindFileMainA(szFullPattern, Pattern, PathCombineA);
		}

	} while (FindNextFileA(FindHandle, &FindData));

	if (FindHandle)
		FindClose(FindHandle);

	if (PathCombineA(szFullPattern, Path, Pattern) == NULL)
		goto EXIT_ROUTINE;

	FindHandle = FindFirstFileA(szFullPattern, &FindData);
	if (FindHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	do
	{
		ZeroMemoryEx(szFullPattern, MAX_PATH);
		if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (PathCombineA(szFullPattern, Path, FindData.cFileName) == NULL)
				goto EXIT_ROUTINE;

			if (IsPathValidA(szFullPattern))
			{
				UserDefinedCallbackRoutineA(szFullPattern);
			}
		}

	} while (FindNextFileA(FindHandle, &FindData));


	if (FindHandle)
		FindClose(FindHandle);

	return TRUE;

EXIT_ROUTINE:

	if (FindHandle)
		FindClose(FindHandle);

	return FALSE;
}

BOOL RecursiveFindFileA(_In_ LPCSTR Path, _In_ LPCSTR Pattern)
{
	typedef LPWSTR(WINAPI* PATHCOMBINEA)(LPCSTR, LPCSTR, LPCSTR);
	PATHCOMBINEA PathCombineA = NULL;
	HMODULE hShlwapi = NULL;
	BOOL bIsNewlyLoaded = FALSE;
	BOOL bFlag = FALSE;

	hShlwapi = GetModuleHandleEx2W(L"Shlwapi.dll");
	if (hShlwapi == NULL)
	{
		bIsNewlyLoaded = TRUE;
		hShlwapi = LoadLibraryW(L"Shlwapi.dll");
		if (hShlwapi == NULL)
			goto EXIT_ROUTINE;
	}

	PathCombineA = (PATHCOMBINEA)GetProcAddressA((DWORD64)hShlwapi, "PathCombineW");
	if (PathCombineA == NULL)
		goto EXIT_ROUTINE;

	bFlag = UnusedSubroutineRecursiveFindFileMainA(Path, Pattern, PathCombineA);

EXIT_ROUTINE:

	if (hShlwapi != NULL)
		FreeLibrary(hShlwapi);

	return bFlag;
}

PVOID UserDefinedCallbackRoutineW(LPCWSTR Path)
{
	return 0;
}

BOOL UnusedSubroutineRecursiveFindFileMainW(LPCWSTR Path, LPCWSTR Pattern, PVOID pfnPathCombineW)
{
	typedef LPWSTR(WINAPI* PATHCOMBINEW)(LPCWSTR, LPCWSTR, LPCWSTR);
	PATHCOMBINEW PathCombineW = (PATHCOMBINEW)pfnPathCombineW;

	HANDLE HeapHandle = GetProcessHeapFromTeb();
	WCHAR szFullPattern[MAX_PATH] = { 0 };
	WIN32_FIND_DATAW FindData = { 0 };
	HANDLE FindHandle = INVALID_HANDLE_VALUE;

	if (PathCombineW(szFullPattern, Path, L"*") == NULL)
		goto EXIT_ROUTINE;

	FindHandle = FindFirstFileW(szFullPattern, &FindData);
	if (FindHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	do
	{
		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (FindData.cFileName[0] == '.')
				continue;

			if (FindData.cFileName[0] == '$')
				continue;

			ZeroMemoryEx(szFullPattern, MAX_PATH);
			if (PathCombineW(szFullPattern, Path, FindData.cFileName) == NULL)
				goto EXIT_ROUTINE;

			UnusedSubroutineRecursiveFindFileMainW(szFullPattern, Pattern, PathCombineW);
		}

	} while (FindNextFileW(FindHandle, &FindData));

	if (FindHandle)
		FindClose(FindHandle);

	if (PathCombineW(szFullPattern, Path, Pattern) == NULL)
		goto EXIT_ROUTINE;

	FindHandle = FindFirstFileW(szFullPattern, &FindData);
	if (FindHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	do
	{
		ZeroMemoryEx(szFullPattern, MAX_PATH);
		if (!(FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (PathCombineW(szFullPattern, Path, FindData.cFileName) == NULL)
				goto EXIT_ROUTINE;

			if (IsPathValidW(szFullPattern))
			{
				UserDefinedCallbackRoutineW(szFullPattern);
			}
		}

	} while (FindNextFileW(FindHandle, &FindData));


	if (FindHandle)
		FindClose(FindHandle);

	return TRUE;

EXIT_ROUTINE:

	if (FindHandle)
		FindClose(FindHandle);

	return FALSE;
}

BOOL RecursiveFindFileW(_In_ LPCWSTR Path, _In_ LPCWSTR Pattern)
{
	typedef LPWSTR(WINAPI* PATHCOMBINEW)(LPCWSTR, LPCWSTR, LPCWSTR);
	PATHCOMBINEW PathCombineW = NULL;
	HMODULE hShlwapi = NULL;
	BOOL bIsNewlyLoaded = FALSE;
	BOOL bFlag = FALSE;

	hShlwapi = GetModuleHandleEx2W(L"Shlwapi.dll");
	if (hShlwapi == NULL)
	{
		bIsNewlyLoaded = TRUE;
		hShlwapi = LoadLibraryW(L"Shlwapi.dll");
		if (hShlwapi == NULL)
			goto EXIT_ROUTINE;
	}

	PathCombineW = (PATHCOMBINEW)GetProcAddressA((DWORD64)hShlwapi, "PathCombineW");
	if (PathCombineW == NULL)
		goto EXIT_ROUTINE;

	bFlag = UnusedSubroutineRecursiveFindFileMainW(Path, Pattern, PathCombineW);

EXIT_ROUTINE:

	if (hShlwapi != NULL)
		FreeLibrary(hShlwapi);

	return bFlag;
}
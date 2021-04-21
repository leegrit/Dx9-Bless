//명령어			옵션		복사할 경로					붙여넣을 경로
xcopy			/y		.\HyEngine\Bin\Debug\x86\*.dll		.\WPF_Tool\bin\Debug\x86\
xcopy			/y		.\HyEngine\Bin\Debug\x86\*.lib		.\_Libraries\x86\Debug\HyEngine\Lib\
xcopy			/y		.\HyEngine\Bin\Debug\x86\*.dll		.\Client\Bin\Debug\x86\
xcopy			/y		.\HyEngine\Bin\Debug\x64\*.dll		.\WPF_Tool\bin\Debug\x64\
xcopy			/y		.\HyEngine\Bin\Debug\x64\*.lib		.\_Libraries\x64\Debug\HyEngine\Lib\
xcopy			/y		.\HyEngine\Bin\Debug\x64\*.dll		.\Client\Bin\Debug\x64\
xcopy 			/y		.\HyEngine\Bin\Release\x86\*.lib		.\_Libraries\x86\Release\HyEngine\Lib\
xcopy			/y		.\HyEngine\Bin\Release\x86\*.dll		.\Client\Bin\Release\x86\
xcopy 			/y		.\HyEngine\Bin\Release\x64\*.lib		.\_Libraries\x64\Release\HyEngine\Lib\
xcopy			/y		.\HyEngine\Bin\Release\x64\*.dll		.\Client\Bin\Release\x64\
xcopy			/y		.\HyEngine\Include\*.h			.\_Libraries\x86\Debug\HyEngine\Include\
xcopy			/y		.\HyEngine\Include\*.h			.\_Libraries\x86\Release\HyEngine\Include\
xcopy			/y		.\HyEngine\Include\*.h			.\_Libraries\x64\Debug\HyEngine\Include\
xcopy			/y		.\HyEngine\Include\*.h			.\_Libraries\x64\Release\HyEngine\Include\
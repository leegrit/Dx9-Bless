//명령어			옵션		복사할 경로					붙여넣을 경로
//xcopy			/y		.\HyEngine\Include\*.h		.\Reference\Include\
//xcopy			/y		.\HyEngine\Bin\*.lib			.\Reference\Libraries\
//xcopy			/y		.\HyEngine\Bin\*.dll			.\Client\Bin\
//xcopy			/y		.\HyEngine\Bin\*.dll			.\SampleClient\Bin\
xcopy			/y		.\HyEngine\Bin\Debug\*.dll		.\WPF_Tool\bin\Debug\
xcopy			/y		.\HyEngine\Bin\Debug\*.lib		.\_Libraries\x86\Debug\HyEngine\Lib\
xcopy			/y		.\HyEngine\Bin\Debug\*.dll		.\Client\Bin\Debug\
xcopy			/y		.\HyEngine\Include\*.h			.\_Libraries\x86\Debug\HyEngine\Include\
xcopy			/y		.\HyEngine\Bin\Release\*.lib		.\_Libraries\x86\Release\HyEngine\Lib\
xcopy			/y		.\HyEngine\Bin\Release\*.dll		.\Client\Bin\Release\
xcopy			/y		.\HyEngine\Include\*.h			.\_Libraries\x86\Release\HyEngine\Include\
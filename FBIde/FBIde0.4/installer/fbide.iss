; FBIde stand-alone installer
; By VonGodriv

[Setup]
AppName=FBIde
AppVerName=FBIde 0.4.4
DefaultDirName=\FreeBasic
DefaultGroupName=FBIde
SolidCompression=yes
compression=lzma/ultra
LicenseFile=C:\Installer\FreeBASIC\docs\gpl.txt
WizardImageFile=fbide.bmp
OutputBaseFilename=FBIde 0.4.4

[Tasks]
Name: "c_desktop";  Description: "Create Desktop Icon";
Name: "c_startm";   Description: "Create Startmenu group";
Name: "c_filety";   Description: "Associate .BAS and .BI files with FBIde";

[Icons]
Name: "{group}\FBIde";    Filename: "{app}\FBIde.exe";   Tasks: c_startm;
Name: "{userdesktop}\FBIde";    Filename: "{app}\FBIde.exe";   Tasks: c_desktop;

[Registry]
; register .bas files with FBIde
Root: HKCR; Subkey: ".bas";                         ValueType: string; ValueName: ""; ValueData: "FBIde_BAS";               Flags: uninsdeletevalue;  Tasks: c_filety
Root: HKCR; Subkey: "FBIde_BAS";                    ValueType: string; ValueName: ""; ValueData: "FreeBASIC source file";   Flags: uninsdeletekey;    Tasks: c_filety
Root: HKCR; Subkey: "FBIde_BAS\DefaultIcon";        ValueType: string; ValueName: ""; ValueData: "{app}\FBIde.exe,0";                                 Tasks: c_filety
Root: HKCR; Subkey: "FBIde_BAS\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\FBIde.EXE"" ""%1""";                        Tasks: c_filety

;Register .bi files with FBIde
Root: HKCR; Subkey: ".bi";                          ValueType: string; ValueName: ""; ValueData: "FBIde_BAS";               Flags: uninsdeletevalue;  Tasks: c_filety
Root: HKCR; Subkey: "FBIde_BI";                     ValueType: string; ValueName: ""; ValueData: "FreeBASIC header file";   Flags: uninsdeletekey;    Tasks: c_filety
Root: HKCR; Subkey: "FBIde_BI\DefaultIcon";         ValueType: string; ValueName: ""; ValueData: "{app}\FBIde.exe,0";                                 Tasks: c_filety
Root: HKCR; Subkey: "FBIde_BI\shell\open\command";  ValueType: string; ValueName: ""; ValueData: """{app}\FBIde.EXE"" ""%1""";                        Tasks: c_filety

;Register .fbs files with FBIde
Root: HKCR; Subkey: ".fbs";                          ValueType: string; ValueName: ""; ValueData: "FBIde_FBS";               Flags: uninsdeletevalue;
Root: HKCR; Subkey: "FBIde_FBS";                     ValueType: string; ValueName: ""; ValueData: "FBIde session file";      Flags: uninsdeletekey;
Root: HKCR; Subkey: "FBIde_FBS\DefaultIcon";         ValueType: string; ValueName: ""; ValueData: "{app}\FBIde.exe,0";
Root: HKCR; Subkey: "FBIde_FBS\shell\open\command";  ValueType: string; ValueName: ""; ValueData: """{app}\FBIde.EXE"" ""%1""";

[Files]
Source: "C:\Installer\FBIde\*"; DestDir: "{app}"; flags: recursesubdirs;

[Run]
Filename: "{app}\FBIde.exe"; Description: "Launch application"; Flags: postinstall nowait skipifsilent


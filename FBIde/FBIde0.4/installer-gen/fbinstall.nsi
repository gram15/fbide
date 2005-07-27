;NSIS Modern User Interface
;FB Install scipt
;Written by dumbledore

;--------------------------------
;Include Modern UI

  !include "MUI.nsh"
  !include "Sections.nsh"

;--------------------------------
;General

  ;Name and file
  Name "FreeBASIC 0.14 Beta + FBIde 0.4.1"
  OutFile "FBInstall.exe"

  ;Default installation folder
  InstallDir "C:\FreeBASIC"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\FreeBASIC" ""

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING
  !define MUI_HEADERIMAGE
  !define MUI_HEADERIMAGE_BITMAP "logo.bmp"
  !define MUI_HEADERIMAGE_BITMAP_NOSTRETCH
  !define MUI_UNABORTWARNING
  !define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\classic-install.ico"
  !define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\classic-uninstall.ico"


;--------------------------------
;Pages

;installer
  !define MUI_PAGE_HEADER_TEXT "FreeBASIC 0.14 Beta + FBIde 0.4.1"

  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "docs/gpl.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY

  ;Start Menu Folder Page Configuration
  !define MUI_STARTMENUPAGE_DEFAULTFOLDER "FBIde"
  !define MUI_STARTMENUPAGE_REGISTRY_ROOT "HKCU" 
  !define MUI_STARTMENUPAGE_REGISTRY_KEY "Software\FreeBASIC" 
  !define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "Start Menu Folder"

  Var STARTMENU_FOLDER
  Var MUI_TEMP
  !insertmacro MUI_PAGE_STARTMENU FBInstall $STARTMENU_FOLDER

  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

;uninstaller
  !insertmacro MUI_UNPAGE_WELCOME
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  !insertmacro MUI_UNPAGE_FINISH

;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"

;--------------------------------
;Installer Sections

Section "FreeBASIC" FBInstall

  ;out.txt goes here

  Exec '$INSTDIR\install.bat $INSTDIR\'

  !insertmacro MUI_STARTMENU_WRITE_BEGIN FBInstall
    
    ;Create shortcuts
    CreateDirectory "$SMPROGRAMS\$STARTMENU_FOLDER"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\FBIde.lnk" "$INSTDIR\FBIde.exe"
    CreateShortCut "$SMPROGRAMS\$STARTMENU_FOLDER\Uninstall.lnk" "$INSTDIR\Uninstall.exe"
  
  !insertmacro MUI_STARTMENU_WRITE_END
  
  ;Store installation folder
  WriteRegStr HKCU "Software\FreeBASIC" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_FBInstall ${LANG_ENGLISH} "Install FreeBASIC 0.14 Beta (everything)."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${FBInstall} $(DESC_FBInstall)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END

;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;uout.txt goes here, insert this line before its last line:
  Delete "$INSTDIR\Uninstall.exe"

  !insertmacro MUI_STARTMENU_GETFOLDER FBInstall $MUI_TEMP
  Delete "$SMPROGRAMS\$MUI_TEMP\FBIde.lnk"
  Delete "$SMPROGRAMS\$MUI_TEMP\Uninstall.lnk"
 
  RMDir "$SMPROGRAMS\$MUI_TEMP"
    
  DeleteRegKey /ifempty HKCU "Software\FreeBASIC"

SectionEnd

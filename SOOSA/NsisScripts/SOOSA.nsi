
;NSIS Modern User Interface
;Basic Example Script
;Written by Joost Verburg

;--------------------------------
;Include SOOSA

  !include "MUI2.nsh"
  
  !define MUI_PRODUCT "SOOSA"
  !define MUI_FILE "SOOSA"
  !define MUI_VERSION ""
  !define MUI_BRANDINGTEXT "SOOSA Version 1.0"

  !define MUI_ICON "Images\APRG.ico"

  CRCCheck On
  
;--------------------------------
;General

  ;Name and file
  Name "SOOSA"
  OutFile "SoosaInstaller.exe"

  ;Default installation folder
  InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"
  
  ;Get installation folder from registry if available
  InstallDirRegKey HKCU "Software\${MUI_PRODUCT}" ""

  ;Request application privileges for Windows Vista
  RequestExecutionLevel admin

;--------------------------------
;Interface Settings

  !define MUI_ABORTWARNING

;--------------------------------
;Pages

  !insertmacro MUI_PAGE_LICENSE "License.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  
  !insertmacro MUI_UNPAGE_CONFIRM
  !insertmacro MUI_UNPAGE_INSTFILES
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"



;--------------------------------
;Installer Sections

Section "SOOSA files" SOOSAFilesSection

  SetOutPath "$INSTDIR"
  
  ;ADD YOUR OWN FILES HERE...
  File /r "${MUI_PRODUCT}\*"
  
  ;Store installation folder
  WriteRegStr HKCU "Software\${MUI_PRODUCT}" "" $INSTDIR
  
  ;create desktop shortcut
  ;CreateShortCut "$DESKTOP\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_FILE}.exe" ""
 
  ;create start-menu items
  CreateDirectory "$SMPROGRAMS\${MUI_PRODUCT}"
  CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\${MUI_PRODUCT}.lnk" "$INSTDIR\${MUI_PRODUCT}\${MUI_FILE}.exe" "" "$INSTDIR\${MUI_PRODUCT}\${MUI_FILE}.exe" 0
  CreateShortCut "$SMPROGRAMS\${MUI_PRODUCT}\Uninstall.lnk" "$INSTDIR\Uninstall.exe" "" "$INSTDIR\Uninstall.exe" 0
 
  ;write uninstall information to the registry
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "DisplayName" "${MUI_PRODUCT}"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "UninstallString" "$INSTDIR\Uninstall.exe"
  
  ;Right click
  WriteRegStr HKCR "Directory\shell\${MUI_PRODUCT}" "" ""
  WriteRegStr HKCR "Directory\shell\${MUI_PRODUCT}\command" "" ""
  WriteRegStr HKCR "Directory\shell\${MUI_PRODUCT}\command" "" "$\"$INSTDIR\${MUI_FILE}.exe$\" $\"%1\$\""
  WriteRegStr HKCR "*\shell\${MUI_PRODUCT}" "" ""
  WriteRegStr HKCR "*\shell\${MUI_PRODUCT}\command" "" ""
  WriteRegStr HKCR "*\shell\${MUI_PRODUCT}\command" "" "$\"$INSTDIR\${MUI_FILE}.exe$\" $\"%1\$\""
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

SectionEnd



;--------------------------------
;Uninstaller Section

Section "Uninstall"
  
  ;ADD YOUR OWN FILES HERE...

  ;Delete Files
  RMDir /r "$INSTDIR\*.*"    
 
  ;Remove the installation directory
  RMDir "$INSTDIR"
  
  ;Delete Start Menu Shortcuts
  ;Delete "$DESKTOP\${MUI_PRODUCT}.lnk"
  Delete "$SMPROGRAMS\${MUI_PRODUCT}\*.*"
  RMDir  "$SMPROGRAMS\${MUI_PRODUCT}"

  DeleteRegKey /ifempty HKCU "Software\${MUI_PRODUCT}"
  
  ;delete uninstall information to the registry
  DeleteRegKey /ifempty HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}"
  
  ;Right click
  DeleteRegKey /ifempty HKCR "Directory\shell\${MUI_PRODUCT}\command"
  DeleteRegKey /ifempty HKCR "Directory\shell\${MUI_PRODUCT}"
  DeleteRegKey /ifempty HKCR "*\shell\${MUI_PRODUCT}\command" 
  DeleteRegKey /ifempty HKCR "*\shell\${MUI_PRODUCT}"

SectionEnd

;--------------------------------
;Descriptions

  ;Language strings
  LangString DESC_SOOSAFilesSection ${LANG_ENGLISH} "SOOSA file section."

  ;Assign language strings to sections
  !insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SOOSAFilesSection} $(DESC_SOOSAFilesSection)
  !insertmacro MUI_FUNCTION_DESCRIPTION_END


;--------------------------------    
;MessageBox Section
 
 
;Function that calls a messagebox when installation finished correctly
Function .onInstSuccess
  MessageBox MB_OK "You have successfully installed ${MUI_PRODUCT}."
FunctionEnd
 
Function un.onUninstSuccess
  MessageBox MB_OK "You have successfully uninstalled ${MUI_PRODUCT}."
FunctionEnd


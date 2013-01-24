; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
#include "setup.iss"
OutputBaseFilename=nxagent-1.2.6-m1-x64
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64

[Files]
Source: "..\..\..\x64\release\libnetxms.dll"; DestDir: "{app}\bin"; BeforeInstall: StopService; Flags: ignoreversion
Source: "..\..\..\x64\release\libnxlp.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\libnxdb.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\nxagentd.exe"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\winnt.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\winperf.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\wmi.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\ping.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\portcheck.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\logwatch.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\sms.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\ups.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\ecs.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\odbcquery.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\Release\informix.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\Release\oracle.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\contrib\nxagentd.conf-dist"; DestDir: "{app}\etc"; Flags: ignoreversion
Source: "..\..\..\x64\release\libexpat.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\x64\release\libtre.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\install\windows\files-x64\libeay32.dll"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\install\windows\files-x64\Microsoft.VC80.CRT\*"; DestDir: "{app}\bin\Microsoft.VC80.CRT"; Flags: ignoreversion

#include "common.iss"

Function GetCustomCmdLine(Param: String): String;
Begin
  Result := '';
End;


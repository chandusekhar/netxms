; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
AppName=NetXMS Agent
AppVerName=NetXMS Agent 0.2.14
AppVersion=0.2.14
AppPublisher=NetXMS Team
AppPublisherURL=http://www.netxms.org
AppSupportURL=http://www.netxms.org
AppUpdatesURL=http://www.netxms.org
DefaultDirName=C:\NetXMS
DefaultGroupName=NetXMS Agent
AllowNoIcons=yes
OutputBaseFilename=nxagent-0.2.14-x64
Compression=lzma
SolidCompression=yes
LanguageDetectionMethod=none
LicenseFile=..\..\..\copying
ArchitecturesInstallIn64BitMode=x64
ArchitecturesAllowed=x64

[Files]
Source: "..\..\libnetxms\Release64\libnetxms.dll"; DestDir: "{app}\bin"; BeforeInstall: StopService; Flags: ignoreversion
Source: "..\core\Release64\nxagentd.exe"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\subagents\winnt\Release64\winnt.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\subagents\winperf\Release64\winperf.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\subagents\ping\Release64\ping.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\subagents\portCheck\Release64\portcheck.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\subagents\logscan\Release64\logscan.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\subagents\ups\Release64\ups.nsm"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\..\..\contrib\nxagentd.conf-dist"; DestDir: "{app}\etc"; Flags: ignoreversion
Source: "..\..\install\windows-x64\files\libeay32.dll"; DestDir: "{app}\bin"; Flags: ignoreversion

[Dirs]
Name: "{app}\etc"
Name: "{app}\var"

[Run]
Filename: "{app}\bin\nxagentd.exe"; Parameters: "-Z ""{app}\etc\nxagentd.conf"" ""{code:GetMasterServer}"" {{syslog} ""{app}\var"" {code:GetSubagentList}"; WorkingDir: "{app}\bin"; StatusMsg: "Creating agent's config..."; Flags: runhidden
Filename: "{app}\bin\nxagentd.exe"; Parameters: "-c ""{app}\etc\nxagentd.conf"" -I"; WorkingDir: "{app}\bin"; StatusMsg: "Installing service..."; Flags: runhidden
Filename: "{app}\bin\nxagentd.exe"; Parameters: "-s"; WorkingDir: "{app}\bin"; StatusMsg: "Starting service..."; Flags: runhidden

[UninstallRun]
Filename: "{app}\bin\nxagentd.exe"; Parameters: "-S"; StatusMsg: "Stopping service..."; RunOnceId: "StopService"; Flags: runhidden
Filename: "{app}\bin\nxagentd.exe"; Parameters: "-R"; StatusMsg: "Uninstalling service..."; RunOnceId: "DelService"; Flags: runhidden

[Code]
Var
  ServerSelectionPage: TInputQueryWizardPage;
  SubagentSelectionPage: TInputOptionWizardPage;
  serverName, sbPing, sbPortCheck, sbWinPerf, sbUPS: String;

Procedure StopService;
Var
  strExecName : String;
  iResult : Integer;
Begin
  strExecName := ExpandConstant('{app}\bin\nxagentd.exe');
  If FileExists(strExecName) Then
  Begin
    Exec(strExecName, '-S', ExpandConstant('{app}\bin'), 0, ewWaitUntilTerminated, iResult);
  End;
End;

Function BoolToStr(Val: Boolean): String;
Begin
  If Val Then
    Result := 'TRUE'
  Else
    Result := 'FALSE';
End;

Function StrToBool(Val: String): Boolean;
Begin
  If Val = 'TRUE' Then
    Result := TRUE
  Else
    Result := FALSE;
End;

Function InitializeSetup(): Boolean;
Var
  i, nCount : Integer;
  param : String;
Begin
  // Empty values for installation data
  serverName := '';
  sbPing := 'FALSE';
  sbPortCheck := 'FALSE';
  sbWinPerf := 'TRUE';
  sbUPS := 'FALSE';
  
  // Parse command line parameters
  nCount := ParamCount;
  For i := 1 To nCount Do Begin
    param := ParamStr(i);

    If Pos('/SERVER=', param) = 1 Then Begin
      serverName := param;
      Delete(serverName, 1, 8);
    End;

    If Pos('/SUBAGENT=', param) = 1 Then Begin
      Delete(param, 1, 10);
      param := Uppercase(param);
      If param = 'PING' Then
        sbPing := 'TRUE';
      If param = 'PORTCHECK' Then
        sbPortCheck := 'TRUE';
      If param = 'WINPERF' Then
        sbWinPerf := 'TRUE';
      If param = 'UPS' Then
        sbUPS := 'TRUE';
    End;

    If Pos('/NOSUBAGENT=', param) = 1 Then Begin
      Delete(param, 1, 12);
      param := Uppercase(param);
      If param = 'PING' Then
        sbPing := 'FALSE';
      If param = 'PORTCHECK' Then
        sbPortCheck := 'FALSE';
      If param = 'WINPERF' Then
        sbWinPerf := 'FALSE';
      If param = 'UPS' Then
        sbUPS := 'FALSE';
    End;
  End;
  Result := TRUE;
End;

Procedure InitializeWizard;
Begin
  ServerSelectionPage := CreateInputQueryPage(wpSelectTasks,
    'NetXMS Server', 'Select your management server.',
    'Please enter host name or IP address of your NetXMS server.');
  ServerSelectionPage.Add('NetXMS server:', False);
  ServerSelectionPage.Values[0] := GetPreviousData('MasterServer', serverName)

  SubagentSelectionPage := CreateInputOptionPage(ServerSelectionPage.Id,
    'Subagent Selection', 'Select desired subagents.',
    'Please select additional subagents you wish to load.', False, False);
  SubagentSelectionPage.Add('ICMP Pinger Subagent - ping.nsm');
  SubagentSelectionPage.Add('Port Checker Subagent - portcheck.nsm');
  SubagentSelectionPage.Add('Windows Performance Subagent - winperf.nsm');
  SubagentSelectionPage.Add('UPS Monitoring Subagent - ups.nsm');
  SubagentSelectionPage.Values[0] := StrToBool(GetPreviousData('Subagent_PING', sbPing));
  SubagentSelectionPage.Values[1] := StrToBool(GetPreviousData('Subagent_PORTCHECK', sbPortCheck));
  SubagentSelectionPage.Values[2] := StrToBool(GetPreviousData('Subagent_WINPERF', sbWinPerf));
  SubagentSelectionPage.Values[3] := StrToBool(GetPreviousData('Subagent_UPS', sbUPS));
End;

Procedure RegisterPreviousData(PreviousDataKey: Integer);
Begin
  SetPreviousData(PreviousDataKey, 'MasterServer', ServerSelectionPage.Values[0]);
  SetPreviousData(PreviousDataKey, 'Subagent_PING', BoolToStr(SubagentSelectionPage.Values[0]));
  SetPreviousData(PreviousDataKey, 'Subagent_PORTCHECK', BoolToStr(SubagentSelectionPage.Values[1]));
  SetPreviousData(PreviousDataKey, 'Subagent_WINPERF', BoolToStr(SubagentSelectionPage.Values[2]));
  SetPreviousData(PreviousDataKey, 'Subagent_UPS', BoolToStr(SubagentSelectionPage.Values[3]));
End;

Function GetMasterServer(Param: String): String;
Begin
  Result := ServerSelectionPage.Values[0];
End;

Function GetSubagentList(Param: String): String;
Begin
  Result := '';
  If SubagentSelectionPage.Values[0] Then
    Result := Result + 'ping.nsm ';
  If SubagentSelectionPage.Values[1] Then
    Result := Result + 'portcheck.nsm ';
  If SubagentSelectionPage.Values[2] Then
    Result := Result + 'winperf.nsm ';
  If SubagentSelectionPage.Values[3] Then
    Result := Result + 'ups.nsm ';
End;


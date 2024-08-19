SetTitleMatchMode, RegEx

GroupAdd, Explorer, ahk_class CabinetWClass
GroupAdd, Explorer, ahk_class ExploreWClass
GroupAdd, Explorer, ahk_class Progman
ComObjError(0)
Bcomp_flag := 0
Bcomp_left_file_path := ""
;WinActive ( "ahk_class TFileCompForm" )
; #c::Run control panel ;win+c for control panel
; return
; #d::
; if WinExist("ahk_class ExploreWClass") or WinExist("ahk_class CabinetWClass")
; {
       ; if WinActive("ahk_class CabinetWClass")
		; WinMinimize 
	   ; else 
		; WinActivate
       ; return
; }
; else {
	; runwait "explorer.exe" "C:\Users\ERIC2"
	; return 
; }
; #$F8::
	; msgbox %A_TitleMatchMode%
	; return
#w::
	run "C:\Program Files\AutoHotkey\WindowSpy.ahk"
	return
; #s::
	; Run "C:\Program Files\TortoiseSVN\bin\TortoiseProc.exe" /command:repobrowser
	; return
#F::
	run "C:\Program Files\Everything\Everything.exe"
	return 
; ^!t:: run c:\Windows\System32\cmd
^!t:: run "C:\Program Files\ConEmu\ConEmu64.exe" 
return
#c:: run C:\Windows\System32\control /name Microsoft.NetworkAndSharingCenter
return
^[::
	send {escape}
	return

::11111::
SendInput password
return 
::22222::
SendInput 5pjZsxRCk4Fj
return 
:*`n:.1.1::
SendInput  192.168.1.1
return
:*`n:.0.1::
SendInput  192.168.0.1
return
:*`n:exportbcm::
SendInput export PATH=/projects/hnd/tools/linux/hndtools-arm-linux-2.6.36-uclibc-4.5.3/bin:$PATH
return
; :*`n:mntnfs::
; SendInput  mkdir /mnt/nfs;mount -t nfs -o nolock  192.168.1.100:/nfs /mnt/nfs;cd /mnt/nfs;ls
; return ;
; ::httpdupup::httpd -S -E /usr/sbin/ca.pem /usr/sbin/httpsd.pem
; return
; #$F1::run C:\Program Files (x86)\FileZilla FTP Client\filezilla.exe
; return
; #$F2::run C:\Program Files\Wireshark\Wireshark.exe
; return
; supernote
; #$F3:: run "C:\Program Files (x86)\Super Notes\SuperNotes.exe"
; return
;smart office
; #$F4:: run "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" http://10.62.163.148/
; return
; #$F5:: run "C:\Users\ERIC2\AppData\Local\LINE\bin\LineLauncher.exe"
; return
; #$F6:: run "C:\Users\ERIC2\Documents\batch\auto_remote\auto_remote.bat"
; return
; #$F7:: run "C:\Users\ERIC2\Documents\ahk\daily_temp\testsmartoffice.ahk"
; return
; ^$F8:: run "C:\Windows\System32\notepad2.exe"
; return
!e::
temp = %clipboard%
Send, {Ctrl Down}c{Ctrl Up}
file = %clipboard% ;get file address
clipboard = %temp% ;restore clipboard
outdir := getdir1(file)
runwait, "C:\Program Files (x86)\Notepad++\notepad++.exe" "%outdir%" 
return

getdir1(input)
{
SplitPath, input,name,parentdir
final = %parentdir%\%name%
return final
}
^+o::
/*filename = Untitle
filepath = %A_WorkingDir%
loop ,100
{
	filepath = %A_WorkingDir%\%filename%_%A_Index%
	
	if FileExist(filepath)
	{	
		
	}
	else 
	{
		break
	}
}
*/
InputBox, UserInput, input box, Please enter file name., , 380,150
FileSelectFolder, filepath, C:\Users\ERIC2\Documents
if ErrorLevel
{
	filename = Untitle
	;filepath = %A_WorkingDir%
	loop ,100
	{
		filepath = %filepath%\%filename%_%A_Index%
	
			if FileExist(filepath)
		{	
			
		}
		else 
		{
			break
		}
	}
}
else 
	filepath = %filepath%\%UserInput%
FileAppend, , %filepath%
Run , C:\Program Files (x86)\Notepad++\notepad++.exe %filepath%
return
/*
RapidHotkey(keystroke, times="2", delay=0.2, IsLabel=0)
{
	Pattern := Morse(delay*1000)
	If (StrLen(Pattern) < 2 and Chr(Asc(times)) != "1")
		Return
	If (times = "" and InStr(keystroke, """"))
	{
		Loop, Parse, keystroke,""	
			If (StrLen(Pattern) = A_Index+1)
				continue := A_Index, times := StrLen(Pattern)
	}
	Else if (RegExMatch(times, "^\d+$") and InStr(keystroke, """"))
	{
		Loop, Parse, keystroke,""
			If (StrLen(Pattern) = A_Index+times-1)
				times := StrLen(Pattern), continue := A_Index
	}
	Else if InStr(times, """")
	{
		Loop, Parse, times,""
			If (StrLen(Pattern) = A_LoopField)
				continue := A_Index, times := A_LoopField
	}
	Else if (times = "")
		continue := 1, times := 2
	Else if (times = StrLen(Pattern))
		continue = 1
	If !continue
		Return
	Loop, Parse, keystroke,""
		If (continue = A_Index)
			keystr := A_LoopField
	Loop, Parse, IsLabel,""
		If (continue = A_Index)
			IsLabel := A_LoopField
	hotkey := RegExReplace(A_ThisHotkey, "[\*\~\$\#\+\!\^]")
	IfInString, hotkey, %A_Space%
		StringTrimLeft, hotkey,hotkey,% InStr(hotkey,A_Space,1,0)
	backspace := "{BS " times "}"
	keywait = Ctrl|Alt|Shift|LWin|RWin
	Loop, Parse, keywait, |
		KeyWait, %A_LoopField%
	If ((!IsLabel or (IsLabel and IsLabel(keystr))) and InStr(A_ThisHotkey, "~") and !RegExMatch(A_ThisHotkey
	, "i)\^[^\!\d]|![^\d]|#|Control|Ctrl|LCtrl|RCtrl|Shift|RShift|LShift|RWin|LWin|Alt|LAlt|RAlt|Escape|BackSpace|F\d\d?|"
	. "Insert|Esc|Escape|BS|Delete|Home|End|PgDn|PgUp|Up|Down|Left|Right|ScrollLock|CapsLock|NumLock|AppsKey|"
	. "PrintScreen|CtrlDown|Pause|Break|Help|Sleep|Browser_Back|Browser_Forward|Browser_Refresh|Browser_Stop|"
	. "Browser_Search|Browser_Favorites|Browser_Home|Volume_Mute|Volume_Down|Volume_Up|MButton|RButton|LButton|"
	. "Media_Next|Media_Prev|Media_Stop|Media_Play_Pause|Launch_Mail|Launch_Media|Launch_App1|Launch_App2"))
		Send % backspace
	If (WinExist("AHK_class #32768") and hotkey = "RButton")
		WinClose, AHK_class #32768
	If !IsLabel
		Send % keystr
	else if IsLabel(keystr)
		Gosub, %keystr%
	Return
}	
*/
/*
*CapsLock::
t := A_PriorHotkey == A_ThisHotkey && A_TimeSincePriorHotkey < 200 ? "off" : -200
settimer, tappedkey_q, %t%
if (t == "off")
goto double_q
return
 
tappedkey_q:
Send {CapsLock}
return
 
double_q:
InputBox , FILE_EXE	
Return
*/
/*
$CapsLock::
	if (A_PriorHotkey = A_ThisHotkey) && (A_TimeSincePriorHotkey < 400)
		InputBox , FILE_EXE	
	Else
		Send {CapsLock}
return
*/
*CapsLock:: 
If (A_TimeSincePriorHotkey<300) and (A_PriorHotkey=A_ThisHotkey)
{
	StringCaseSense off
	InputBox , FILE_EXE
	SetCapsLockState, off
	WinGet windows, List
	Loop %windows%
	{
		id := windows%A_Index%
		WinGetTitle wt, ahk_id %id%
		IfInString, wt, %FILE_EXE%
		{
			StringCaseSense on
			
			NOTEPADPLUS :="Notepad++"
			SINSIGHT := "Source"
			MOBAXTERM := "MobaXterm"
			IfInString, wt, %NOTEPADPLUS%
			{
				WinActivate, Notepad++
				return 
			}
			IfInString, wt, %SINSIGHT%
			{
				IfWinNotExist ahk_class si_Frame 
					Run "D:\Program Files (x86)\Source Insight 3\Insight3.Exe"
				Else 
				IfWinNotActive ahk_class si_Frame 
					WinActivate 
				Else 
					WinMinimize 
				Return 
			}
			IfInString, wt, %MOBAXTERM%
			{
				
				WinActivate, MobaXterm
			}
			WinActivate, %wt%
			;msgbox "%wt%"
			return
		}
	}
	msgbox "Not exist %FILE_EXE%"
	StringCaseSense on
}

Return
#IfWinActive ahk_class CabinetWClass
{
^F::
	folder := GetFolder()
	run "C:\Program Files\Everything\Everything.exe" -p "%folder%"
	return
Insert::
	send ,{F6}
	return 
}
GetFolder()
{
    WinGetClass,var,A
    If var in CabinetWClass,ExplorerWClass,Progman
    {
        IfEqual,var,Progman
            v := A_Desktop
        else
        {
            winGetText,Fullpath,A
            loop,parse,Fullpath,`r`n
            {
                IfInString,A_LoopField,:\
                {
                    StringGetPos,pos,A_Loopfield,:\,L
                    Stringtrimleft,v,A_loopfield,(pos - 1)
                    break
                }
            }
        }
    return, v
    }
}
*/
;Run "C:\Users\ERIC2\Downloads"    ;win+w for open download directory
;return 

;Macro1:
;Sleep 500
;Send `t
;Sleep 2000
;Send, {Enter}
return
;;
;https://autohotkey.com/board/topic/87699-express-7-zip-extract/
;alt  + x
!x::
temp = %clipboard%
Send, {Ctrl Down}c{Ctrl Up}
file = %clipboard% ;get file address
clipboard = %temp% ;restore clipboard
outdir := getdir(file)
InputBox, PASSWORD, input box, Please enter Passowrd., , 380,150
if (A_Is64bitOS = 1)
{
runwait, "C:\Program Files\7-Zip\7z.exe" x "%file%" -o"%outdir%" -p"%PASSWORD%" -y,,hide
}
else
{
runwait, "C:\Program Files (x86)\7-Zip\7z.exe" x "%file%" -o"%outdir%" -p"%PASSWORD%" -y,,hide
}
msgbox, 7zip has finished extracting "%file%".
return
getdir(input)
{
SplitPath, input,,parentdir,,filenoext
final = %parentdir%\%filenoext%
return final
}

;contrast file or direcory
!c::
temp = %clipboard%
Send, {Ctrl Down}c{Ctrl Up}
file = %clipboard% ;get file address
clipboard = %temp% ;restore clipboard
outdir := getdir(file)
if (A_Is64bitOS = 1)
{
runwait, "C:\Program Files\7-Zip\7z.exe" a -tzip  "%outdir%.zip"  "%file%",,hide
}
else
{
runwait, "C:\Program Files (x86)\7-Zip\7z.exe" a -tzip "%file%" -r ,,hide
}
msgbox, 7zip has finished compress "%file%".
return




;; create file

/*
#t::
run, notepad
sleep 500
send, 123`t123
sleep 500
Send, {Enter}
*/
/*
!b::
if WinActive ( "ahk_class TViewForm" )
{
	ControlGetText sFile1, TAltEdit1
	ControlGetText sFile2, TAltEdit2
	msgbox "%sFile1% %sFile2%"
	Run "%ProgramFiles%\Beyond Compare 4\BCompare.exe" "%sFile2%" "%sFile1%"
;		Run "%ProgramFiles%\WinMerge\WinMerge.exe" "%sFile2%" "%sFile1%"
	Return
}
Return
*/
^1::

if WinActive ( "ahk_exe Explorer.EXE " )
{
	temp = %clipboard%
	Send, {Ctrl Down}c{Ctrl Up}
	file = %clipboard% ;get file address
	clipboard = %temp% ;restore clipboard
	source := getdir1(file)
	FileCopy, %source% , C:\Users\ERIC2\Desktop\tftp_path ,1
	ErrorCount := ErrorLevel
	if ErrorLevel
		msgbox "copy to C:\Users\ERIC2\Desktop\tftp_path failed"
	else 
		msgbox "Sucessed"
	;Run "%ProgramFiles%\Beyond Compare 4\BCompare.exe" "%sFile2%" "%sFile1%"
	;Run "%ProgramFiles%\WinMerge\WinMerge.exe" "%sFile2%" "%sFile1%"
	;Return
}
Return
^2::

if WinActive ( "ahk_exe Explorer.EXE " )
{
	temp = %clipboard%
	Send, {Ctrl Down}c{Ctrl Up}
	file = %clipboard% ;get file address
	clipboard = %temp% ;restore clipboard
	source := getdir1(file)
	FileCopy, %source% , S:\ ,1
	ErrorCount := ErrorLevel
	if ErrorLevel
		msgbox "copy to Z:\windows"
	else 
		msgbox "Sucessed^2"	
}
Return



#IfWinActive, ahk_group Explorer
^b::
hWnd :=   WinExist("ahk_class (?:Cabinet|Explore)WClass")
selected:=ShellFolder(hWnd)
;MsgBox %path_array.MaxIndex()
path_array:=StrSplit( selected,"`n")
;MsgBox selected
;MsgBox  "1= %path_array[1]% 2= %path_array[2]% "
if (path_array.MaxIndex() > 2 || path_array.MaxIndex() < 0) {
	Bcomp_flag:=0
	Bcomp_left_file_path :=""
	MsgBox only select 1 and 2 file(s)
	Return 
}
else if (path_array.MaxIndex()==1){
	if (Bcomp_flag ==0){
		Bcomp_left_file_path := path_array[1]
		Bcomp_flag:=1
		Msgbox select %Bcomp_left_file_path% on the left
	}
	else if (Bcomp_flag ==1 ){
		Bcomp_right_file_path := path_array[1]
		
		MsgBox %Bcomp_left_file_path% compare to %Bcomp_right_file_path%
		Run  "%ProgramFiles%\Beyond Compare 4\BCompare.exe" "%Bcomp_left_file_path%" "%Bcomp_right_file_path%"
		; Run  "%ProgramFiles%\\WinMerge\WinMergeU.exe" "%Bcomp_left_file_path%" "%Bcomp_right_file_path%"
		Bcomp_flag:=0
		Bcomp_left_file_path :=""
	}
}

else {
	Loop % path_array.MaxIndex()
	{	
		if  (A_Index==1 ){
			
			path1 := path_array[A_Index]
			
		}
		else if (A_Index==2 ){
			path2 := path_array[A_Index]
			Run  "%ProgramFiles%\Beyond Compare 4\BCompare.exe" "%path1%" "%path2%"
			break
		}
		
		;MsgBox, Color number %A_Index% is %this_color%.
	}
	Bcomp_flag:=0
	Bcomp_left_file_path :=""
}
Return

!e::
; temp = %clipboard%
; Send, {Ctrl Down}c{Ctrl Up}
; file = %clipboard% ;get file address
; clipboard = %temp% ;restore clipboard
; outdir := getdir1(file)
hWnd :=   WinExist("ahk_class (?:Cabinet|Explore)WClass")
selected:=ShellFolder(hWnd)
path_array:=StrSplit( selected,"`n")
if ( path_array.MaxIndex() !=1 )
{	
	return
}
		
outdir := path_array[1]

runwait, "C:\Program Files (x86)\Notepad++\notepad++.exe" "%outdir%" 
return

#If


ShellFolder(hWnd=0)
{
	If   hWnd || (hWnd :=   WinExist("ahk_class (?:Cabinet|Explore)WClass"))	
   {
	  
      For window in ComObjCreate("Shell.Application").Windows
         doc :=   window.Document
      Until   (window.hWnd = hWnd)
    }
      
  sFolder :=   doc.folder.self.path, sFocus :=   doc.focuseditem.name
	  ;MsgBox "2."%sFolder%  ;获取forlder
  For item in doc.SelectedItems {
   ;~ sSelect .=   (!sSelect ? "" : "`n") item.name
   sSelect .=   (!sSelect ? "" : "`n") item.path
  }
  Return   sSelect
}
#3::
run C:\Users\jeff_\Desktop\VDI_external\remote.bat
return 
; #1::
; WinGetActiveTitle, Title
; WinMove, %Title%,, 0,0,(A_ScreenWidth/2), (A_ScreenHeight)
; return
; #2::
; WinGetActiveTitle, Title
; WinMove, %Title%,, (A_ScreenWidth/2),0,(A_ScreenWidth/2), (A_ScreenHeight/2)
; return
; return
; #3::
; WinGetActiveTitle, Title
; WinMove, %Title%,, (A_ScreenWidth/2),(A_ScreenHeight/2),(A_ScreenWidth/2), (A_ScreenHeight/2)
; return

/*
#SingleInstance force


#F1::
RAMP("C:\Program Files\Everything\Everything.exe")
return


;RunOrActivateOrMinimizeProgram
 RAMP(ExePath) {    
	tExe:=GetFilename(ExePath)
	if (SubStr(tExe,-3)!=".exe")
        tExe.=".exe"
	if WinExist("ahk_exe" . tExe)
	{
		If WinActive("ahk_exe" . tExe) ; "ahk_exe" 后不需要空格.
		{
			WinMinimize
		}
		else
		{
			WinActivate
		}
	}else{
		Run *RunAs "%ExePath%"
	}
	return
}
GetFilename(txt)
{
	SplitPath, txt, o
	return o
}

#IfWinActive ahk_group WinGroup
^f::
WinGetClass,o,a
if (o="Progman")
	FilePath=%A_Desktop%
if(o="CabinetWClass")
{
	ControlGetText, FilePath, ToolbarWindow322, A   ;有网友说应该是323，这个控件值有时会变化，新的获取当前目录的方式可以参考  这里就有新技术
 https://blog.csdn.net/liuyukuan/article/details/102492464
	StringReplace, FilePath, FilePath, 地址:%A_space%, , All
	if FilePath =
		ControlGetText, FilePath, Edit1, A
	; msgbox, %FilePath%
	if FilePath=桌面
		FilePath=%A_Desktop%
	if FilePath=库\文档
		FilePath=%A_MyDocuments%
	if FilePath in 网上邻居,控制面板,回收站,计算机, 控制面板\所有控制面板项
		FilePath=d:\
}

RAMP("C:\Program Files\Everything\Everything.exe")
WinWaitActive,ahk_exe Everything.exe
ControlSetText, Edit1, "%FilePath%"%A_space%, A
Send ^{End}

#IfWinActive
*/



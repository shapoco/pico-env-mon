if (!([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole("Administrators")) {
    Start-Process powershell.exe "-File `"$PSCommandPath`"" -Verb RunAs
    exit
}

$ProbeHwid = "2e8a:000c"

usbipd detach --hardware-id ${ProbeHwid}
usbipd unbind --hardware-id ${ProbeHwid}
usbipd list

Read-Host "Hit return key to exit."

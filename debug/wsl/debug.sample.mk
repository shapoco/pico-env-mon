.PHONY: flash attach-probe detach-probe

PICO_DRIVE := e

flash: $(BIN)
	sudo mkdir -p /mnt/$(PICO_DRIVE)
	sudo mount -t drvfs $(PICO_DRIVE): /mnt/$(PICO_DRIVE)
	cp $(BIN) /mnt/$(PICO_DRIVE)/.

attach-probe:
	powershell.exe debug/wsl/probe-attach.ps1

detach-probe:
	powershell.exe debug/wsl/probe-detach.ps1

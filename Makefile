# Définition des variables
BUILD = ./build

all: start

compileMain :
	@echo Compile Project
	make -C $(BUILD)

# La cible "launchMain" est exécutée en tapant la commande "make launchMain"
launchMain :
	@echo Lancement de main
	$(BUILD)/SMP-TP11.bin

# La cible "start" est exécutée en tapant la commande "make start"
start : compileMain launchMain
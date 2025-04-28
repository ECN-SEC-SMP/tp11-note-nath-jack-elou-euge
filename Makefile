# Définition des variables
GPP = g++ -Wall
SRC = ./src
SRC_CLASS = ./src/class

BIN = ./bin


all: start

# La cible "deleteAll" est exécutée en tapant la commande "make deleteAll"
deleteAll :
	@echo Suppression du contenu du répertoire $(BIN)
	rm -f $(BIN)/*.o $(BIN)/*.bin

# $(BIN)/Image.o : $(SRC_CLASS)/Image.cpp
# 	@echo "Compilation Image.cpp"
# 	$(GPP) -c $< -o $@

# $(BIN)/PPMImage.o : $(SRC_CLASS_EXTENSION)/PPMImage.cpp
# 	@echo "Compilation PPMImage.cpp"
# 	$(GPP) -c $< -o $@


# La cible "compilRobot" est exécutée en tapant la commande "make compilRobot"
compilRobot :
	@echo "Compilation Robot"
	$(GPP) -c $(SRC_CLASS)/Robot.cpp -I ${SRC_CLASS}/Color_Shape.hpp -o $(BIN)/Robot.o

# La cible "compilPlayer" est exécutée en tapant la commande "make compilPlayer"
compilPlayer :
	@echo "Compilation Player"
	$(GPP) -c $(SRC_CLASS)/Player.cpp -o $(BIN)/Player.o

# La cible "compilTarget" est exécutée en tapant la commande "make compilTarget"
compilTarget :
	@echo "Compilation Target"
	$(GPP) -c $(SRC_CLASS)/Target.cpp -I ${SRC_CLASS}/Color_Shape.hpp -o $(BIN)/Target.o

# La cible "compilCase" est exécutée en tapant la commande "make compilCase"
compilCase :
	@echo "Compilation Case"
	$(GPP) -c $(SRC_CLASS)/Case.cpp -o $(BIN)/Case.o

# La cible "compilBoard" est exécutée en tapant la commande "make compilBoard"
compilBoard : compilRobot compilPlayer compilTarget compilCase
	@echo "Compilation Board"
	$(GPP) -c $(SRC_CLASS)/Board.cpp $(BIN)/Player.o $(BIN)/Robot.o $(BIN)/Target.o $(BIN)/Case.o -I ${SRC_CLASS}/Color_Shape.hpp -o $(BIN)/Board.o

# La cible "compilDisplay" est exécutée en tapant la commande "make compilDisplay"
compilDisplay : compilBoard
	@echo "Compilation Display"
	$(GPP) -c $(SRC_CLASS)/Display.cpp $(BIN)/Board.o -I ${SRC_CLASS}/Color_Shape.hpp -o $(BIN)/Display.o

# La cible "compilGame" est exécutée en tapant la commande "make compilGame"
compilGame : compilDisplay
	@echo "Compilation Game"
	$(GPP) -c $(SRC_CLASS)/Game.cpp $(BIN)/Display.o -o $(BIN)/Game.o

# La cible "compilMain" est exécutée en tapant la commande "make compilMain"
compilMain : deleteAll compilGame
	@echo Compilation de main
	$(GPP) $(SRC)/main.cpp $(BIN)/Game.o -o $(BIN)/main.bin

# La cible "launchMain" est exécutée en tapant la commande "make launchMain"
launchMain :
	@echo Lancement de main
	$(BIN)/main.bin

# La cible "start" est exécutée en tapant la commande "make start"
start : compilMain launchMain

CMP = g++
CLASS = board
MAIN = crossword
EXEC = playcrossword

$(EXEC): $(CLASS).o $(MAIN).o
	$(CMP) -std=c++11 $(CLASS).o $(MAIN).o -o $(EXEC)

$(CLASS).o: $(CLASS).cpp $(CLASS).h
	$(CMP) -c $(CLASS).cpp -o $(CLASS).o -std=c++11

$(MAIN).o: $(MAIN).cpp $(CLASS).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o -std=c++11

clean:
	rm *.o
	rm $(EXEC)


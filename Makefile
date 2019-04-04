default:
	clang++ -c -std=c++17 main.cpp BankDES.cpp MarketDES.cpp
	clang++ -o QueueSimulation main.o BankDES.o MarketDES.o
clean:
	rm -f main.o BankDES.o MarketDES.o QueueSimulation
OBJS=DemocraticParty.o main.o Party.o PoliticalSys.o Politician.o PoliticianDemocraticLeader.o PoliticianDemocraticSocial.o PoliticianRepublicanLeader.o PoliticianRepublicanSocial.o RepublicanParty.o

Ass5: $(OBJS)
	g++ $(OBJS) -o Ass5
DemocraticParty.o: DemocraticParty.cpp DemocraticParty.h Party.h Politician.h Error.h
	g++ -c DemocraticParty.cpp
main.o: main.cpp PoliticalSys.h Error.h PoliticianDemocraticLeader.h Politician.h Party.h PoliticianDemocraticSocial.h PoliticianRepublicanLeader.h PoliticianRepublicanSocial.h
	g++ -c main.cpp
Party.o: Party.cpp Party.h Politician.h Error.h
	g++ -c Party.cpp
PoliticalSys.o: PoliticalSys.cpp PoliticalSys.h Error.h PoliticianDemocraticLeader.h Politician.h Party.h PoliticianDemocraticSocial.h PoliticianRepublicanLeader.h PoliticianRepublicanSocial.h DemocraticParty.h RepublicanParty.h
	g++ -c PoliticalSys.cpp
Politician.o: Politician.cpp Politician.h Party.h Error.h
	g++ -c Politician.cpp
PoliticianDemocraticLeader.o: PoliticianDemocraticLeader.cpp PoliticianDemocraticLeader.h Politician.h Party.h Error.h
	g++ -c PoliticianDemocraticLeader.cpp
PoliticianDemocraticSocial.o: PoliticianDemocraticSocial.cpp PoliticianDemocraticSocial.h Politician.h Party.h Error.h
	g++ -c PoliticianDemocraticSocial.cpp
PoliticianRepublicanLeader.o: PoliticianRepublicanLeader.cpp PoliticianRepublicanLeader.h Politician.h Party.h Error.h
	g++ -c PoliticianRepublicanLeader.cpp
PoliticianRepublicanSocial.o: PoliticianRepublicanSocial.cpp PoliticianRepublicanSocial.h Politician.h Party.h Error.h
	g++ -c PoliticianRepublicanSocial.cpp
RepublicanParty.o: RepublicanParty.cpp RepublicanParty.h Party.h Politician.h Error.h
	g++ -c RepublicanParty.cpp
clean:
	rm -f $(OBJS) Ass5


edit : Agenda.o AgendaUI.o AgendaService.o Storage.o Meeting.o Date.o User.o
	g++ -o a.out -std=c++0x *.o -g
Agenda.o : Agenda.cpp AgendaUI.cpp AgendaUI.h
	g++ -c -g -std=c++0x Agenda.cpp
AgendaUI.o : AgendaUI.h AgendaUI.cpp AgendaService.h AgendaService.cpp
	g++ -c -g -std=c++0x AgendaUI.cpp
AgendaService.o : AgendaService.h AgendaService.cpp Storage.h Storage.cpp
	g++ -c -g -std=c++0x AgendaService.cpp
Storage.o : Storage.h Storage.cpp Meeting.h Meeting.cpp User.h User.cpp
	g++ -c -g -std=c++0x Storage.cpp
Meeting.o : Meeting.h Meeting.cpp Date.h Date.cpp
	g++ -c -g -std=c++0x Meeting.cpp
Date.o : Date.h Date.cpp
	g++ -c -g -std=c++0x Date.cpp
User.o : User.h User.cpp
	g++ -c -g -std=c++0x User.cpp
clean :
	rm *.o

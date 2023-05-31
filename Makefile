CXX=g++
LD=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long
LDFLAGS=-std=c++17 -Wall -pedantic -Wno-long-long

all: volckric
volckric: main.o CApplication.o CCalendar.o CCalendarFinder.o CCalendarImporter.o CConflictSolver.o CDatetime.o CDisplayCalendar.o CDisplayDaily.o CDisplayMonthly.o CDisplayWeekly.o CEvent.o CEventExporter.o CEventRecurring.o CEventSimple.o CHelpers.o CTime.o
	$(LD) $(LXXFLAGS) -o $@ $^

clean:
	rm -f volckric *.o

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run: volckric
	./volckric

compile: volckric

main.o: src/main.cpp src/CApplication.h
CApplication.o: src/CApplication.cpp src/CApplication.h
CCalendar.o: src/CCalendar.cpp src/CCalendar.h
CCalendarExporter.o: src/CEventExporter.cpp src/CEventExporter.h
CCalendarFinder.o: src/CCalendarFinder.cpp src/CCalendarFinder.h
CCalendarImporter.o: src/CCalendarImporter.cpp src/CCalendarImporter.h
CConflictSolver.o: src/CConflictSolver.cpp src/CConflictSolver.h
CDatetime.o: src/CDatetime.cpp src/CDatetime.h
CDisplayCalendar.o: src/CDisplayCalendar.cpp src/CDisplayCalendar.h
CDisplayDaily.o: src/CDisplayDaily.cpp src/CDisplayDaily.h
CDisplayMonthly.o: src/CDisplayMonthly.cpp src/CDisplayMonthly.h
CDisplayWeekly.o: src/CDisplayWeekly.cpp src/CDisplayWeekly.h
CEvent.o: src/CEvent.cpp src/CEvent.h
CEventRecurring.o: src/CEventRecurring.cpp src/CEventRecurring.h
CEventSimple.o: src/CEventSimple.cpp src/CEventSimple.h
CHelpers.o: src/CHelpers.cpp src/CHelpers.h
CTime.o: src/CTime.cpp src/CDatetime.h
